#include "BasicAxis.h"

BasicAxis::BasicAxis(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // ������ɫ������
    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    shaderProgram->link();

    // �������ݣ�ÿ�����������㣨�����յ㣩
    float vertices[] = {
        // X�ᣨ��ɫ��
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        // Y�ᣨ��ɫ��
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

        // Z�ᣨ��ɫ��
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f
    };

    // ����VAO/VBO
    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    // ���ö�������ָ��
    shaderProgram->bind();

    // λ�����ԣ�location=0��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ��ɫ���ԣ�location=1��
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

    // ����ģ����ͼͶӰ����
    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

    QMatrix4x4 view;
    view.lookAt(
        QVector3D(3, 3, 3), // ���λ��
        QVector3D(0, 0, 0), // �۲�Ŀ��
        QVector3D(0, 1, 0) // �Ϸ���
    );

    QMatrix4x4 model;
    model.setToIdentity();

    QMatrix4x4 mvp = projection * view * model;

    // ����������
    shaderProgram->bind();
    shaderProgram->setUniformValue("mvp", mvp);

    vao.bind();
    glDrawArrays(GL_LINES, 0, 6); // 6�����㣨3���ߣ�
    vao.release();

    shaderProgram->release();
}
