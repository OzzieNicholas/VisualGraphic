#pragma once

#include <QVector>
#include <QMatrix4x4>

namespace Utils{

namespace Math {

	// 弧度转换为角度
	float radiansToDegrees(float radians);

	// 角度转换为弧度
	float degreesToRadians(float degrees);

	// 计算两个向量的叉积
	QVector3D crossProduct(const QVector3D& vectorA, const QVector3D& vectorB);

	// 计算两个向量的点积
	float dotProduct(const QVector3D& vectorA, const QVector3D& vectorB);

	// 创建平移矩阵
	QMatrix4x4 makeTranslationMatrix(const QVector3D& translation);

	// 创建旋转矩阵
	QMatrix4x4 makeRotationMatrix(float angle, const QVector3D& axis);

	// 创建缩放矩阵
	QMatrix4x4 makeScaleMatrix(const QVector3D& scale);

	// 组合平移旋转缩放矩阵
	QMatrix4x4 makeTransformMatrix(const QVector3D& translation, float angle, const QVector3D& axis, const QVector3D& scale);

	// 创建正交投影矩阵
	QMatrix4x4 makeOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane);

	// 创建透视投影矩阵
	QMatrix4x4 makePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

} // namespace Math

} // namespace Utils