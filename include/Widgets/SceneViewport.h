#pragma once

#include "../Geometry/TriMesh.h"
#include "../Renderer/TriMeshRenderer.h"

class SceneViewport  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	SceneViewport(QWidget *parent = nullptr);
	~SceneViewport();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private:
    TriMesh axisMesh;
    TriMesh groundMesh;
    TriMeshRenderer renderer;
    QOpenGLShaderProgram* shader = nullptr;

    float rotationX = 45.0f;
    float rotationY = -45.0f;
    float zoom = 20.0f;
    float panX = 0.0f;
    float panY = 0.0f;
    QPoint lastMousePos;

	QVector3D mapClickToPlane(float screenX, float screenY);

    std::vector<QVector3D> polylinePoints;
	TriMesh polylineMesh;
	TriMeshRenderer polylineRenderer;
    void polylineClear();
};
