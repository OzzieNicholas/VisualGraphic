#include "../../include/Utils/UtilsMath.h"

namespace Utils {

namespace Math {

// ����ת��Ϊ�Ƕ�
float radiansToDegrees(float radians) {
	return radians * 180.0f / M_PI;
}

// �Ƕ�ת��Ϊ����
float degreesToRadians(float degrees) {
	return degrees * M_PI / 180.0f;
}

// �������������Ĳ��
QVector3D crossProduct(const QVector3D& vectorA, const QVector3D& vectorB) {
	return QVector3D::crossProduct(vectorA, vectorB);
}

// �������������ĵ��
float dotProduct(const QVector3D& vectorA, const QVector3D& vectorB) {
	return QVector3D::dotProduct(vectorA, vectorB);
}

// ����ƽ�ƾ���
QMatrix4x4 makeTranslationMatrix(const QVector3D& translation) {
	QMatrix4x4 matrix;
	matrix.translate(translation);
	return matrix;
}

// ������ת����
QMatrix4x4 makeRotationMatrix(float angle, const QVector3D& axis) {
	QMatrix4x4 matrix;
	matrix.rotate(angle, axis);
	return matrix;
}

// �������ž���
QMatrix4x4 makeScaleMatrix(const QVector3D& scale) {
	QMatrix4x4 matrix;
	matrix.scale(scale);
	return matrix;
}

// ���ƽ����ת���ž���
QMatrix4x4 makeTransformMatrix(const QVector3D& translation, float angle, const QVector3D& axis, const QVector3D& scale) {
	QMatrix4x4 matrix;
	matrix.translate(translation);
	matrix.rotate(angle, axis);
	matrix.scale(scale);
	return matrix;
}

// ��������ͶӰ����
QMatrix4x4 makeOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
	QMatrix4x4 matrix;
	matrix.ortho(left, right, bottom, top, nearPlane, farPlane);
	return matrix;
}

// ����͸��ͶӰ����
QMatrix4x4 makePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
	QMatrix4x4 matrix;
	matrix.perspective(fov, aspectRatio, nearPlane, farPlane);
	return matrix;
}

} // namespace Math

} // namespace Utils