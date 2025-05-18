#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QDebug>
#include <QString>

namespace Utils {

namespace OpenGL {

// ��鲢��ӡ OpenGL ����
void checkGLError(const char* context = "");

// ��� Shader Program ����־��Ϣ������/������־��
void printProgramLog(QOpenGLShaderProgram* program);

// ���ó�����Ⱦ״̬����Ȳ��ԡ���ϵȣ�
void setupDefaultRenderState(QOpenGLFunctions* gl);

} // namespace OpenGL

} // namespace Utils
