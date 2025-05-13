#include "../../include/Widgets/SceneViewport.h"
#include "../../include/Geometry/TriMeshBuilder.h"

SceneViewport::SceneViewport(QWidget* parent) : QOpenGLWidget(parent) {
    QSurfaceFormat format;
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(8);
    setFormat(format);
}

SceneViewport::~SceneViewport() {
    makeCurrent();
    delete shader;
    doneCurrent();
}

void SceneViewport::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.15f, 0.2f, 0.25f, 1.0f);

    shader = new QOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/tri_mesh.vert");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/tri_mesh.frag");
    if (!shader->link()) {
        qDebug() << "Shader link error:" << shader->log();
    }

    groundMesh = TriMeshBuilder::createGroundPlane(40.0f, 100);
    axisMesh = TriMeshBuilder::createAxisLines(5.0f);

    renderer.setMesh(groundMesh);
    renderer.setMesh(axisMesh); // 后面可以扩展 set多个 renderer
}

void SceneViewport::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void SceneViewport::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / height(), 0.1f, 100.0f);

    QMatrix4x4 view;
    view.translate(panX, panY, -zoom);
    view.rotate(rotationX, 1.0f, 0.0f, 0.0f);
    view.rotate(rotationY, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 model;
    model.setToIdentity();

    QMatrix4x4 mvp = projection * view * model;

    if (shader) {
        shader->bind();
        shader->setUniformValue("mvp", mvp);

        // 地面
        renderer.setMesh(groundMesh);
        renderer.drawMesh(shader);

        // 坐标轴
        renderer.setMesh(axisMesh);
        renderer.drawMesh(shader);

		// 折线
        if (!polylinePoints.empty()) {
            polylineRenderer.setMesh(polylineMesh);
            polylineRenderer.drawMesh(shader);
        }

        shader->release();
    }
}

void SceneViewport::mousePressEvent(QMouseEvent* event) {
    lastMousePos = event->pos();

	if (event->button() == Qt::LeftButton) {
		QVector3D worldCoord = mapClickToPlane(event->position().x(), event->position().y());
		qDebug() << "Z=0:" << worldCoord;
        polylinePoints.push_back(worldCoord);
		polylineMesh = TriMeshBuilder::createPolyline(polylinePoints, QVector3D(1.0f, 0.0f, 0.0f));
		polylineRenderer.setMesh(polylineMesh);
		update();
	}
}

void SceneViewport::mouseMoveEvent(QMouseEvent* event) {
    int dx = int(event->position().x() - lastMousePos.x());
    int dy = int(event->position().y() - lastMousePos.y());

    if (event->buttons() & Qt::MiddleButton) {
        rotationX += dy * 0.5f;
        rotationY += dx * 0.5f;
    }
    else if (event->buttons() & Qt::RightButton) {
        panX += dx * 0.01f;
        panY -= dy * 0.01f;
    }

    lastMousePos = event->pos();
    update();
}

void SceneViewport::wheelEvent(QWheelEvent* event) {
    zoom -= event->angleDelta().y() / 120.0f;
    if (zoom < 2.0f) zoom = 2.0f;
    if (zoom > 100.0f) zoom = 100.0f;
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
	view.translate(panX, panY, -zoom);
	view.rotate(rotationX, 1.0f, 0.0f);
	view.rotate(rotationY, 0.0f, 1.0f);
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

void SceneViewport::polylineClear() {
	polylinePoints.clear();
	polylineMesh.clear();
	polylineRenderer.setMesh(polylineMesh);
	update();
}

void SceneViewport::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
		polylineClear();
	}
    else {
		QOpenGLWidget::keyPressEvent(event);
    }
}