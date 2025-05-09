#include "../../include/Basic/BasicAxis.h"

BasicAxis::BasicAxis(QWidget* parent)
    : QOpenGLWidget(parent) {
    QSurfaceFormat format;
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
	format.setSamples(8);
    setFormat(format);
}

BasicAxis::~BasicAxis() {
    makeCurrent();
    vao.destroy();
    vbo.destroy();
    delete shaderProgram;
    doneCurrent();
}

void BasicAxis::initializeGL() {
	// 初始化OpenGL
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.2f, 0.25f, 1.0f);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	// 编译和链接着色器
    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/axis.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/axis.frag");
	if (!shaderProgram->link()) {
		qDebug() << "Shader program link error:" << shaderProgram->log();
	}

	// 创建坐标轴几何体
	float axisLength = 5.0f;
    float vertices[] = {
		// x-红色
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        axisLength, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		// y-绿色
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, axisLength, 0.0f,  0.0f, 1.0f, 0.0f,
		// z-蓝色
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, axisLength,  0.0f, 0.0f, 1.0f
    };
    vao.create();
    vao.bind();
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

	// 顶点属性
    shaderProgram->bind();
	// 顶点位置 attribute 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	// 顶点颜色 attribute 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    vao.release();
    shaderProgram->release();

    // 生成并绑定圆锥箭头几何体（仅位置，不含颜色）
	std::vector<float> coneArrowVertices = generateConeArrow(0.1f, 0.3f, 24);
	coneArrowVertexCount = coneArrowVertices.size() / 3;
	coneArrowVao.create();
	coneArrowVao.bind();
	coneArrowVbo.create();
	coneArrowVbo.bind();
	coneArrowVbo.allocate(coneArrowVertices.data(), coneArrowVertices.size() * sizeof(float));
	// 仅配置位置属性 attribute 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 未绑定 attribute 1，颜色将在绘制时使用 glVertexAttrib3f 设置常量颜色
	coneArrowVao.release();
}

void BasicAxis::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void BasicAxis::paintGL() {
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

	// 绘制圆锥箭头
	coneArrowVao.bind();
	shaderProgram->bind();
	// x轴箭头
	model.setToIdentity();
	model.translate(5.0f, 0.0f, 0.0f);
	model.rotate(rotationX, 1.0f, 0.0f, 0.0f);
	mvp = projection * view * model;
	shaderProgram->setUniformValue("mvp", mvp);
	glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, coneArrowVertexCount);
	// y轴箭头
	model.setToIdentity();
	model.translate(0.0f, 5.0f, 0.0f);
	model.rotate(rotationX, 1.0f, 0.0f, 0.0f);
	mvp = projection * view * model;
	shaderProgram->setUniformValue("mvp", mvp);
	glVertexAttrib3f(1, 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, coneArrowVertexCount);
	// z轴箭头
	model.setToIdentity();
	model.translate(0.0f, 0.0f, 5.0f);
	mvp = projection * view * model;
	shaderProgram->setUniformValue("mvp", mvp);
	glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, coneArrowVertexCount);
	coneArrowVao.release();

    shaderProgram->release();
}

void BasicAxis::mousePressEvent(QMouseEvent* event) {
	lastMousePos = event->pos();
}

void BasicAxis::mouseMoveEvent(QMouseEvent* event) {
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

void BasicAxis::wheelEvent(QWheelEvent* event) {
	zoom -= event->angleDelta().y() / 120.0f;
	if (zoom < 2.0f) zoom = 2.0f;
	if (zoom > 100.0f) zoom = 100.0f;
	update();
}

std::vector<float> BasicAxis::generateConeArrow(float radius, float height, int segments) {
    std::vector<float> vertices;
	float tipX = 0.0f, tipY = 0.0f, tipZ = height;

    for (int i = 0; i < segments; ++i) {
		float theta1 = (float)i / segments * 2.0f * M_PI;
		float theta2 = (float)(i + 1) / segments * 2.0f * M_PI;
		float x1 = radius * cos(theta1);
		float z1 = radius * sin(theta1);
		float x2 = radius * cos(theta2);
		float z2 = radius * sin(theta2);
		vertices.insert(vertices.end(), {
            tipX, tipY, tipZ,
			x1, 0.0f, z1,
			x2, 0.0f, z2,
			}
        );
    }

	return vertices;
}
