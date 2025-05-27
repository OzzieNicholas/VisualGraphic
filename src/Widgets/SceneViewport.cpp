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

// ========== InteractorHost 接口 ========== //

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

void SceneViewport::rotateView(float deltaX, float deltaY) {
    m_rotationX += deltaY;
    m_rotationY += deltaX;
    update();
}

void SceneViewport::panView(float offsetX, float offsetY) {
    m_panX += offsetX;
    m_panY += offsetY;
    update();
}

void SceneViewport::zoomView(float zoomDelta) {
    m_zoom += zoomDelta;
    if (m_zoom < 2.0f) m_zoom = 2.0f;
    if (m_zoom > 100.0f) m_zoom = 100.0f;
    update();
}

// ========== 渲染辅助 ========== //

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
