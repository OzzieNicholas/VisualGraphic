#include "../../include/Widgets/SceneViewport.h"

SceneViewport::SceneViewport(QWidget* parent) : QOpenGLWidget(parent) {
    QSurfaceFormat format;
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(8);
    setFormat(format);
}

SceneViewport::~SceneViewport() {
    makeCurrent();
    delete m_shaderProgram;
    doneCurrent();
}

void SceneViewport::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.15f, 0.2f, 0.25f, 1.0f);

    // 初始化并编译着色器
    m_shaderProgram = new QOpenGLShaderProgram(this);
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/tri_mesh.vert");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/tri_mesh.frag");
    if (!m_shaderProgram->link()) {
        qDebug() << "Shader link error:" << m_shaderProgram->log();
    }

    // 构建地面网格并上传
    m_groundMesh = TriMeshBuilder::buildGroundPlaneMesh(40.0f, 100);
    m_groundRenderer.setMesh(m_groundMesh);

    // 构建坐标轴（使用 LineMesh）
    m_axisLineMesh = LineMeshBuilder::buildAxisLines(5.0f);
    m_axisRenderer.setMesh(m_axisLineMesh);

    // 初始化空折线
    m_polylinePoints.clear();
    m_polylineMesh.clearGeometryData();
    m_polylineRenderer.setMesh(m_polylineMesh);
}

void SceneViewport::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void SceneViewport::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 投影矩阵
    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / height(), 0.1f, 100.0f);

    // 视图矩阵
    QMatrix4x4 view;
    view.translate(m_panX, m_panY, -m_zoom);
    view.rotate(m_rotationX, 1.0f, 0.0f, 0.0f);
    view.rotate(m_rotationY, 0.0f, 1.0f, 0.0f);

    // 模型矩阵
    QMatrix4x4 model;
    model.setToIdentity();

    // 合成变换矩阵
    QMatrix4x4 mvp = projection * view * model;

    if (m_shaderProgram) {
        m_shaderProgram->bind();
        m_shaderProgram->setUniformValue("mvp", mvp);

        // 绘制地面
        m_groundRenderer.renderMesh(m_shaderProgram);

        // 绘制坐标轴
        m_axisRenderer.renderMesh(m_shaderProgram);

        // 绘制折线
        if (!m_polylinePoints.empty()) {
            m_polylineRenderer.renderMesh(m_shaderProgram);
        }

        m_shaderProgram->release();
    }
}

void SceneViewport::mousePressEvent(QMouseEvent* event) {
    m_lastMousePos = event->pos();

    if (event->button() == Qt::LeftButton) {
        // 将点击位置映射到 Z=0 平面
        QVector3D worldCoord = mapClickToPlane(event->position().x(), event->position().y());
        qDebug() << "Z=0 Click:" << worldCoord;

        // 添加点到折线集合
        m_polylinePoints.push_back(worldCoord);

        // 更新折线网格
        m_polylineMesh = LineMeshBuilder::buildPolylineMesh(m_polylinePoints, QVector3D(1.0f, 0.0f, 0.0f));
        m_polylineRenderer.setMesh(m_polylineMesh);

        // 请求重绘
        update();
    }
}

void SceneViewport::mouseMoveEvent(QMouseEvent* event) {
    int dx = int(event->position().x() - m_lastMousePos.x());
    int dy = int(event->position().y() - m_lastMousePos.y());

    if (event->buttons() & Qt::MiddleButton) {
        m_rotationX += dy * 0.5f;
        m_rotationY += dx * 0.5f;
    }
    else if (event->buttons() & Qt::RightButton) {
        m_panX += dx * 0.01f;
        m_panY -= dy * 0.01f;
    }

    m_lastMousePos = event->pos();
    update();
}

void SceneViewport::wheelEvent(QWheelEvent* event) {
    m_zoom -= event->angleDelta().y() / 120.0f;
    if (m_zoom < 2.0f) m_zoom = 2.0f;
    if (m_zoom > 100.0f) m_zoom = 100.0f;
    update();
}

QVector3D SceneViewport::mapClickToPlane(float screenX, float screenY) {
	// 屏幕坐标 → NDC
	float ndcX = (2.0f * screenX) / width() - 1.0f;
	float ndcY = 1.0f - (2.0f * screenY) / height();
	
	// 构造与 paintGL 一致的投影视图矩阵
	QMatrix4x4 projection;
	projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);
	QMatrix4x4 view;
	view.translate(m_panX, m_panY, -m_zoom);
	view.rotate(m_rotationX, 1.0f, 0.0f);
	view.rotate(m_rotationY, 0.0f, 1.0f);
	QMatrix4x4 invPV = (projection * view).inverted();

	// 将 NDC 转换为世界坐标
    QVector4D nearPointNDC(ndcX, ndcY, -1.0f, 1.0f); // 近平面
    QVector4D farPointNDC(ndcX, ndcY, 1.0f, 1.0f);   // 远平面
	QVector4D nearWorld = invPV * nearPointNDC;
	QVector4D farWorld = invPV * farPointNDC;
	nearWorld /= nearWorld.w();
	farWorld /= farWorld.w();
	QVector3D rayOrigin = nearWorld.toVector3D();
	QVector3D rayDir = (farWorld - nearWorld).toVector3D().normalized();

	// 与 Z=0 平面求交
	if (qAbs(rayDir.z()) < 1e-6f) {
		// 射线与平面平行
		return QVector3D(
            std::numeric_limits<float>::quiet_NaN(),
			std::numeric_limits<float>::quiet_NaN(),
			std::numeric_limits<float>::quiet_NaN()
        );
	}

	float t = -rayOrigin.z() / rayDir.z();
	QVector3D intersection = rayOrigin + t * rayDir;
	return intersection;
}

void SceneViewport::clearPolyline() {
    m_polylinePoints.clear();
    m_polylineMesh.clearGeometryData();
    m_polylineRenderer.setMesh(m_polylineMesh);
	update();
}

void SceneViewport::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
        clearPolyline();
	}
    else {
		QOpenGLWidget::keyPressEvent(event);
    }
}