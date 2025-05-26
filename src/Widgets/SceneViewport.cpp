#include "../../include/Widgets/SceneViewport.h"

SceneViewport::SceneViewport(QWidget* parent)
    : QOpenGLWidget(parent),
    m_interactorManager(new InteractorManager) {
    QSurfaceFormat format;
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(8);
    setFormat(format);
}

SceneViewport::~SceneViewport() {
    makeCurrent();
    delete m_shaderProgram;
    delete m_interactorManager;
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
    m_groundMesh = MeshTriBuilder::buildGroundPlaneMesh(40.0f, 100);
    m_groundRenderer.setMesh(m_groundMesh);

    // 构建坐标轴线
    m_axisLineMesh = MeshLineBuilder::buildAxisLines(5.0f);
    m_axisRenderer.setMesh(m_axisLineMesh);

    // 初始化空折线
    m_polylineMesh.clearGeometryData();
    m_polylineRenderer.setMesh(m_polylineMesh);
}

void SceneViewport::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void SceneViewport::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mvp = getProjectionMatrix() * getViewMatrix();

    if (m_shaderProgram) {
        m_shaderProgram->bind();
        m_shaderProgram->setUniformValue("mvp", mvp);

        m_groundRenderer.renderMesh(m_shaderProgram);
        m_axisRenderer.renderMesh(m_shaderProgram);
        m_polylineRenderer.renderMesh(m_shaderProgram);

        m_shaderProgram->release();
    }
}

// ========== Qt 事件分发 ========== //

void SceneViewport::mousePressEvent(QMouseEvent* event) {
    m_lastMousePos = event->pos();
    if (m_interactorManager) {
        m_interactorManager->onMousePress(event, this);
    }
}

void SceneViewport::mouseMoveEvent(QMouseEvent* event) {
    if (m_interactorManager) {
        m_interactorManager->onMouseMove(event, this);
    }
    m_lastMousePos = event->pos();
}

void SceneViewport::wheelEvent(QWheelEvent* event) {
    if (m_interactorManager) {
        m_interactorManager->onWheel(event, this);
    }
}

void SceneViewport::keyPressEvent(QKeyEvent* event) {
    if (m_interactorManager) {
        m_interactorManager->onKeyPress(event, this);
    }
    else {
        QOpenGLWidget::keyPressEvent(event);
    }
}

// ========== 渲染与状态接口 ========== //

QMatrix4x4 SceneViewport::getViewMatrix() const {
    QMatrix4x4 view;
    view.translate(m_panX, m_panY, -m_zoom);
    view.rotate(m_rotationX, 1.0f, 0.0f, 0.0f);
    view.rotate(m_rotationY, 0.0f, 1.0f, 0.0f);
    return view;
}

QMatrix4x4 SceneViewport::getProjectionMatrix() const {
    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / height(), 0.1f, 100.0f);
    return projection;
}

QSize SceneViewport::getViewportSize() const {
    return size();
}

void SceneViewport::requestViewportUpdate() {
    update();
}

float SceneViewport::getCameraZoom() const {
    return m_zoom;
}

// ========== 折线更新接口 ========== //

void SceneViewport::setPolylineMesh(const MeshLine& mesh) {
    m_polylineMesh = mesh;
    m_polylineRenderer.setMesh(m_polylineMesh);
    update();
}

void SceneViewport::clearPolyline() {
    m_polylineMesh.clearGeometryData();
    m_polylineRenderer.setMesh(m_polylineMesh);
    update();
}

// ========== 可迁移辅助函数 ========== //

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