#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QDebug>
#include <QString>

namespace Utils {

namespace OpenGL {

// 检查并打印 OpenGL 错误
void checkGLError(const char* context = "");

// 输出 Shader Program 的日志信息（编译/链接日志）
void printProgramLog(QOpenGLShaderProgram* program);

// 启用常见渲染状态（深度测试、混合等）
void setupDefaultRenderState(QOpenGLFunctions* gl);

} // namespace OpenGL

} // namespace Utils
