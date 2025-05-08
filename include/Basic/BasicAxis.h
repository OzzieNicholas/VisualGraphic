#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <QMouseEvent>

class BasicAxis : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    BasicAxis(QWidget* parent = nullptr);
    ~BasicAxis();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
    QOpenGLShaderProgram* shaderProgram = nullptr;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;

    QPoint lastMousePos;

	float panX = 0.0f;
	float panY = 0.0f;
    float zoom = 15.0f;
    float rotationX = 45.0f;
    float rotationY = -45.0f;
	
};
