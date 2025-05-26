/*
 * MeshTriRenderer.h：三角网格渲染器
 *
 * 功能概述：
 *  - 将 MeshTri 顶点/索引数据上传到 GPU
 *  - 绑定并配置 VAO/VBO/EBO
 *  - 使用指定着色器程序进行渲染
 *
 * 使用场景：
 *  - 渲染法线线段、坐标轴、路径折线等辅助图元
 *  - 可视化几何边界、调试结构分析
 *  - 图形系统中非面状图元的快速渲染
 */

#pragma once

#include "../Geometry/MeshTri.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class MeshTriRenderer {
public:
    // ========== 构造与析构 ========== //

    MeshTriRenderer();
    ~MeshTriRenderer();

    // ========== 数据上传与渲染 ========== //

    // 设置网格
    void setMesh(const MeshTri& mesh);

    // 绘制网格
    void renderMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject m_meshVAO;   // 顶点数组对象
    QOpenGLBuffer m_meshVBO;              // 顶点缓冲对象
    QOpenGLBuffer m_meshEBO;              // 索引缓冲对象

    int m_meshIndexCount = 0;             // 索引数
    bool m_meshInitialized = false;       // 是否已初始化
    GLenum m_meshDrawMode = GL_TRIANGLES; // 图元类型
};
