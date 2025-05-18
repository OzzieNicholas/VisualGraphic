#include "../../include/Utils/UtilsOpenGL.h"

namespace Utils {

namespace OpenGL {

// ��鲢��ӡ OpenGL ����
void checkGLError(const char* context) {
    GLenum err;
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    while ((err = f->glGetError()) != GL_NO_ERROR) {
        qWarning() << "[OpenGL Error]" << context << ":" << QString::number(err, 16);
    }
}

// ��� Shader Program ����־��Ϣ������/������־��
void printProgramLog(QOpenGLShaderProgram* program) {
    if (!program) return;

    if (!program->log().isEmpty()) {
        qDebug() << "[Shader Program Log]\n" << program->log();
    }
}

// ���ó�����Ⱦ״̬����Ȳ��ԡ���ϵȣ�
void setupDefaultRenderState(QOpenGLFunctions* gl) {
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthFunc(GL_LESS);

    gl->glEnable(GL_BLEND);
    gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

} // namespace OpenGL

} // namespace Utils
