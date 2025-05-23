/*
 * QuadMeshRenderer.h：四边形网格渲染器
 *
 * 功能概述：
 *  - 将 QuadMesh 顶点与索引数据上传到 GPU
 *  - 管理 VAO/VBO/EBO 缓冲对象
 *  - 使用指定着色器进行四边形图元绘制
 *
 * 使用场景：
 *  - 渲染平面结构（如地面、墙体、立方体面）
 *  - 可视化基于四边面的建模结果
 *  - 几何离散网格、纹理贴图面等图形结构展示
 */

#pragma once

#include "../Geometry/QuadMesh.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class QuadMeshRenderer {
public:
    // ========== 构造与析构 ========== //

    QuadMeshRenderer();
    ~QuadMeshRenderer();

    // ========== 数据上传与渲染 ========== //

    // 设置网格
    void setMesh(const QuadMesh& mesh);

    // 绘制网格
    void renderMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject m_meshVAO;   // 顶点数组对象
    QOpenGLBuffer m_meshVBO;              // 顶点缓冲对象
    QOpenGLBuffer m_meshEBO;              // 索引缓冲对象

    int m_meshIndexCount = 0;             // 索引数
    bool m_meshInitialized = false;       // 是否已初始化
    GLenum m_meshDrawMode = GL_QUADS;     // 图元类型
};
