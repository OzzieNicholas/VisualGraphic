#include "../../include/Widgets/BasicAxis.h"

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
	// ��ʼ��OpenGL
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.2f, 0.25f, 1.0f);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	// �����������ɫ��
    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/axis.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/axis.frag");
	if (!shaderProgram->link()) {
		qDebug() << "Shader program link error:" << shaderProgram->log();
	}

	// ���������Ἰ����
	float axisLength = 5.0f;
    float vertices[] = {
		// x-��ɫ
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        axisLength, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		// y-��ɫ
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, axisLength, 0.0f,  0.0f, 1.0f, 0.0f,
		// z-��ɫ
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, axisLength,  0.0f, 0.0f, 1.0f
    };
    vao.create();
    vao.bind();
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

	// ��������
    shaderProgram->bind();
	// ����λ�� attribute 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	// ������ɫ attribute 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    vao.release();
    shaderProgram->release();

    // ���ɲ���Բ׶��ͷ�����壨��λ�ã�������ɫ��
	std::vector<float> coneArrowVertices = generateConeArrow(0.1f, 0.3f, 24);
	coneArrowVertexCount = coneArrowVertices.size() / 3;
	coneArrowVao.create();
	coneArrowVao.bind();
	coneArrowVbo.create();
	coneArrowVbo.bind();
	coneArrowVbo.allocate(coneArrowVertices.data(), coneArrowVertices.size() * sizeof(float));
	// ������λ������ attribute 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// δ�� attribute 1����ɫ���ڻ���ʱʹ�� glVertexAttrib3f ���ó�����ɫ
	coneArrowVao.release();

    // TriMesh
    // 1. ���� shader program
    triMeshShader = new QOpenGLShaderProgram(this);
    triMeshShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/tri_mesh.vert");
    triMeshShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/tri_mesh.frag");
    if (!triMeshShader->link()) {
        qDebug() << "TriMesh shader link error:" << triMeshShader->log();
    }
    // 2. ���������������� 20x20��
    triMesh = TriMeshBuilder::createGrid(20, 20, 10.0f);
    // 3. ���õ���Ⱦ��
    triMeshRenderer.setMesh(triMesh);
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

	// ����Բ׶��ͷ
	coneArrowVao.bind();
	shaderProgram->bind();
	// x���ͷ
	model.setToIdentity();
	model.translate(5.0f, 0.0f, 0.0f);
	model.rotate(90.0f, 0.0f, 1.0f, 0.0f);
	mvp = projection * view * model;
	shaderProgram->setUniformValue("mvp", mvp);
	glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, coneArrowVertexCount);
	// y���ͷ
	model.setToIdentity();
	model.translate(0.0f, 5.0f, 0.0f);
	model.rotate(-90.0f, 1.0f, 0.0f, 0.0f);
	mvp = projection * view * model;
	shaderProgram->setUniformValue("mvp", mvp);
	glVertexAttrib3f(1, 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, coneArrowVertexCount);
	// z���ͷ
	model.setToIdentity();
	model.translate(0.0f, 0.0f, 5.0f);
	mvp = projection * view * model;
	shaderProgram->setUniformValue("mvp", mvp);
	glVertexAttrib3f(1, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, coneArrowVertexCount);
	coneArrowVao.release();

    shaderProgram->release();

    // TriMesh
    if (triMeshShader) {
        QMatrix4x4 projection;
        projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

        QMatrix4x4 view;
        view.translate(panX, panY, -zoom);
        view.rotate(rotationX, 1.0f, 0.0f);
        view.rotate(rotationY, 0.0f, 1.0f);

        QMatrix4x4 model;
        model.setToIdentity();

        QMatrix4x4 mvp = projection * view * model;

        triMeshShader->bind();
        triMeshShader->setUniformValue("mvp", mvp);
        triMeshRenderer.drawMesh(triMeshShader);
        triMeshShader->release();
    }
}

void BasicAxis::mousePressEvent(QMouseEvent* event) {
	lastMousePos = event->pos();
    if (event->button() == Qt::MiddleButton) {  // ���Ϊ Ctrl+���
        QVector3D worldCoord = mapClickToPlane(event->position().x(), event->position().y());
        qDebug() << "Clicked 3D Coord (Z=0 Plane):" << worldCoord;
    }
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

QVector3D BasicAxis::mapClickToPlane(float screenX, float screenY) {
    // 1. ��Ļ���� �� NDC
    float ndcX = (2.0f * screenX) / width() - 1.0f;
    float ndcY = 1.0f - (2.0f * screenY) / height();

    QVector4D nearPointNDC(ndcX, ndcY, -1.0f, 1.0f); // ��ƽ��
    QVector4D farPointNDC(ndcX, ndcY, 1.0f, 1.0f);   // Զƽ��

    // 2. ������ paintGL һ�µ�ͶӰ��ͼ����
    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

    QMatrix4x4 view;
    view.translate(panX, panY, -zoom);
    view.rotate(rotationX, 1.0f, 0.0f);
    view.rotate(rotationY, 0.0f, 1.0f);

    QMatrix4x4 invPV = (projection * view).inverted();

    // 3. �� NDC ת��Ϊ��������
    QVector4D nearWorld = invPV * nearPointNDC;
    QVector4D farWorld = invPV * farPointNDC;
    nearWorld /= nearWorld.w();
    farWorld /= farWorld.w();

    QVector3D rayOrigin = nearWorld.toVector3D();
    QVector3D rayDir = (farWorld - nearWorld).toVector3D().normalized();

    // 4. �� Z=0 ƽ����
    if (qAbs(rayDir.z()) < 1e-6f) {
        // ������ƽ��ƽ��
        return QVector3D(std::numeric_limits<float>::quiet_NaN(),
            std::numeric_limits<float>::quiet_NaN(),
            std::numeric_limits<float>::quiet_NaN());
    }

    float t = -rayOrigin.z() / rayDir.z();
    QVector3D intersection = rayOrigin + t * rayDir;
    return intersection;
}
