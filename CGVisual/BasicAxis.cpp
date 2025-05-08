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

    // 创建着色器程序
    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    shaderProgram->link();

    // 顶点数据：每个轴两个顶点（起点和终点）
    float vertices[] = {
        // X轴（红色）
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        // Y轴（绿色）
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

        // Z轴（蓝色）
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f
    };

    // 配置VAO/VBO
    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    // 设置顶点属性指针
    shaderProgram->bind();

    // 位置属性（location=0）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性（location=1）
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

    // 设置模型视图投影矩阵
    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

    QMatrix4x4 view;
    view.lookAt(
        QVector3D(3, 3, 3), // 相机位置
        QVector3D(0, 0, 0), // 观察目标
        QVector3D(0, 1, 0) // 上方向
    );

    QMatrix4x4 model;
    model.setToIdentity();

    QMatrix4x4 mvp = projection * view * model;

    // 绘制坐标轴
    shaderProgram->bind();
    shaderProgram->setUniformValue("mvp", mvp);

    vao.bind();
    glDrawArrays(GL_LINES, 0, 6); // 6个顶点（3条线）
    vao.release();

    shaderProgram->release();
}
