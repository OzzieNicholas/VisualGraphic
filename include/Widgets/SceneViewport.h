/*
 * SceneViewport.h：三维场景视图窗口（主渲染控件）
 *
 * 功能概述：
 *  - 提供基于 OpenGL 的交互式三维可视化界面
 *  - 管理并渲染多个网格（如坐标轴、地面、折线等）
 *  - 支持视角旋转、缩放、平移等交互功能
 *  - 支持点击拾取、添加折线点等用户操作
 *
 * 使用场景：
 *  - 几何数据和图形算法的动态展示
 *  - 图形学教学、HMI 可视化与交互实验
 */

#pragma once

#include "../Geometry/TriMesh.h"
#include "../Geometry/LineMesh.h"
#include "../Geometry/TriMeshBuilder.h"
#include "../Geometry/LineMeshBuilder.h"

#include "../Renderer/TriMeshRenderer.h"
#include "../Renderer/LineMeshRenderer.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class SceneViewport : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    // ========== 构造与析构 ========== //

    explicit SceneViewport(QWidget* parent = nullptr);
    ~SceneViewport();

protected:
    // ========== Qt 事件重载 ========== //

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    // ========== 渲染资源 ========== //

    TriMesh m_groundMesh; // 地面网格
    LineMesh m_polylineMesh; // 折线构成的三角线段
    LineMesh m_axisLineMesh; // 坐标轴线段

    TriMeshRenderer m_groundRenderer;   // 地面网格渲染器
    LineMeshRenderer m_polylineRenderer; // 折线网格渲染器
    LineMeshRenderer m_axisRenderer;    // 坐标轴渲染器

    QOpenGLShaderProgram* m_shaderProgram = nullptr; // 着色器

    // ========== 相机控制参数 ========== //

    float m_rotationX = 45.0f;  // 绕 X 轴的旋转角度
    float m_rotationY = -45.0f; // 绕 Y 轴的旋转角度
    float m_zoom = 20.0f;       // 缩放因子（视距）
    float m_panX = 0.0f;        // 水平平移量
    float m_panY = 0.0f;        // 垂直平移量
    QPoint m_lastMousePos;      // 上一次鼠标位置

    // ========== 交互状态 ========== //

    std::vector<QVector3D> m_polylinePoints; // 点击添加的折线点

    // ========== 内部辅助 ========== //

	// 将屏幕坐标转换为世界坐标
    QVector3D mapClickToPlane(float screenX, float screenY);

	// 更新折线网格
    void updatePolylineMesh();

	// 清除折线网格
    void clearPolyline();
};
