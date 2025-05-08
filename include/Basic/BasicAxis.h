#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

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

private:
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;

    const char* vertexShader = R"(
        #version 460 core
        layout(location=0) in vec3 position;
        layout(location=1) in vec3 color;
        uniform mat4 mvp;
        out vec3 vColor;
        void main(){
            gl_Position = mvp * vec4(position, 1.0);
            vColor = color;
        })";

    const char* fragmentShader = R"(
        #version 460 core
        in vec3 vColor;
        out vec4 fragColor;
        void main(){
            fragColor = vec4(vColor, 1.0);
        })";
};
