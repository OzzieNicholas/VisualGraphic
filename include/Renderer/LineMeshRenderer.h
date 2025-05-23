/*
 * LineMeshRenderer.h：线段网格渲染器
 *
 * 功能概述：
 *  - 将 LineMesh 中的顶点和索引数据上传至 GPU
 *  - 管理 OpenGL 缓冲对象（VAO/VBO/EBO）
 *  - 使用指定着色器绘制线段图元
 *
 * 使用场景：
 *  - 渲染三角网格模型
 *  - 展示曲面建模、光照、纹理效果等可视化结果
 *  - 图形学教学与算法演示平台中的三角形图元渲染任务
 */

#pragma once

#include "../Geometry/LineMesh.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class LineMeshRenderer {
public:
    // ========== 构造与析构 ========== //

    LineMeshRenderer();
    ~LineMeshRenderer();

    // ========== 数据上传与渲染 ========== //

    // 设置线段网格
    void setMesh(const LineMesh& mesh);

    // 绘制线段网格
    void renderMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject m_meshVAO;   // 顶点数组对象
    QOpenGLBuffer m_meshVBO;              // 顶点缓冲对象
    QOpenGLBuffer m_meshEBO;              // 索引缓冲对象

    int m_meshIndexCount = 0;             // 索引数
    bool m_meshInitialized = false;       // 是否已初始化
    GLenum m_meshDrawMode = GL_LINES;     // 图元类型
};
