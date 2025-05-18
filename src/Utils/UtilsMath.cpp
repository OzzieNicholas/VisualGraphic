#include "../../include/Utils/UtilsMath.h"

namespace Utils {

namespace Math {

// 弧度转换为角度
float radiansToDegrees(float radians) {
	return radians * 180.0f / M_PI;
}

// 角度转换为弧度
float degreesToRadians(float degrees) {
	return degrees * M_PI / 180.0f;
}

// 计算两个向量的叉积
QVector3D crossProduct(const QVector3D& vectorA, const QVector3D& vectorB) {
	return QVector3D::crossProduct(vectorA, vectorB);
}

// 计算两个向量的点积
float dotProduct(const QVector3D& vectorA, const QVector3D& vectorB) {
	return QVector3D::dotProduct(vectorA, vectorB);
}

// 创建平移矩阵
QMatrix4x4 makeTranslationMatrix(const QVector3D& translation) {
	QMatrix4x4 matrix;
	matrix.translate(translation);
	return matrix;
}

// 创建旋转矩阵
QMatrix4x4 makeRotationMatrix(float angle, const QVector3D& axis) {
	QMatrix4x4 matrix;
	matrix.rotate(angle, axis);
	return matrix;
}

// 创建缩放矩阵
QMatrix4x4 makeScaleMatrix(const QVector3D& scale) {
	QMatrix4x4 matrix;
	matrix.scale(scale);
	return matrix;
}

// 组合平移旋转缩放矩阵
QMatrix4x4 makeTransformMatrix(const QVector3D& translation, float angle, const QVector3D& axis, const QVector3D& scale) {
	QMatrix4x4 matrix;
	matrix.translate(translation);
	matrix.rotate(angle, axis);
	matrix.scale(scale);
	return matrix;
}

// 创建正交投影矩阵
QMatrix4x4 makeOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
	QMatrix4x4 matrix;
	matrix.ortho(left, right, bottom, top, nearPlane, farPlane);
	return matrix;
}

// 创建透视投影矩阵
QMatrix4x4 makePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
	QMatrix4x4 matrix;
	matrix.perspective(fov, aspectRatio, nearPlane, farPlane);
	return matrix;
}

} // namespace Math

} // namespace Utils