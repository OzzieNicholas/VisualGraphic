#include "../../include/Basic/BasicAxis.h"

BasicAxis::BasicAxis(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
	format.setSamples(8);
    setFormat(format);
}

BasicAxis::~BasicAxis()
{
    makeCurrent();
    vao.destroy();
    vbo.destroy();
    delete shaderProgram;
    doneCurrent();
}

void BasicAxis::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.2f, 0.25f, 1.0f);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/axis.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/axis.frag");
    shaderProgram->link();

	float axisLength = 5.0f;
    float vertices[] = {
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        axisLength, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, axisLength, 0.0f,  0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, axisLength,  0.0f, 0.0f, 1.0f
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    shaderProgram->bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao.release();
}

void BasicAxis::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void BasicAxis::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

    QMatrix4x4 view;
	view.translate(panX, panY, -zoom);
	view.rotate(rotationX, 1.0f, 0.0f, 0.0f);
	view.rotate(rotationY, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 model;
    model.setToIdentity();

    QMatrix4x4 mvp = projection * view * model;
    shaderProgram->bind();
    shaderProgram->setUniformValue("mvp", mvp);

    vao.bind();
    glDrawArrays(GL_LINES, 0, 6);
    vao.release();

    shaderProgram->release();
}

void BasicAxis::mousePressEvent(QMouseEvent* event)
{
	lastMousePos = event->pos();
}

void BasicAxis::mouseMoveEvent(QMouseEvent* event)
{
	int dx = int(event->position().x() - lastMousePos.x());
    int dy = int(event->position().y() - lastMousePos.y());

	if (event->buttons() & Qt::LeftButton) {
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

void BasicAxis::wheelEvent(QWheelEvent* event)
{
	zoom -= event->angleDelta().y() / 120.0f;
	if (zoom < 2.0f) zoom = 2.0f;
	if (zoom > 100.0f) zoom = 100.0f;
	update();
}