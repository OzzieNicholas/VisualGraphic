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

        renderer.setMesh(groundMesh);
        renderer.drawMesh(shader);

        renderer.setMesh(axisMesh);
        renderer.drawMesh(shader);

        shader->release();
    }
}

void SceneViewport::mousePressEvent(QMouseEvent* event) {
    lastMousePos = event->pos();
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
