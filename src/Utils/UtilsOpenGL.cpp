#include "../../include/Utils/UtilsOpenGL.h"

namespace Utils {

namespace OpenGL {

// 检查并打印 OpenGL 错误
void checkGLError(const char* context) {
    GLenum err;
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    while ((err = f->glGetError()) != GL_NO_ERROR) {
        qWarning() << "[OpenGL Error]" << context << ":" << QString::number(err, 16);
    }
}

// 输出 Shader Program 的日志信息（编译/链接日志）
void printProgramLog(QOpenGLShaderProgram* program) {
    if (!program) return;

    if (!program->log().isEmpty()) {
        qDebug() << "[Shader Program Log]\n" << program->log();
    }
}

// 启用常见渲染状态（深度测试、混合等）
void setupDefaultRenderState(QOpenGLFunctions* gl) {
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthFunc(GL_LESS);

    gl->glEnable(GL_BLEND);
    gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

} // namespace OpenGL

} // namespace Utils
