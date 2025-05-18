#pragma once

#include <QVector>
#include <QMatrix4x4>

namespace Utils{

namespace Math {

	// ����ת��Ϊ�Ƕ�
	float radiansToDegrees(float radians);

	// �Ƕ�ת��Ϊ����
	float degreesToRadians(float degrees);

	// �������������Ĳ��
	QVector3D crossProduct(const QVector3D& vectorA, const QVector3D& vectorB);

	// �������������ĵ��
	float dotProduct(const QVector3D& vectorA, const QVector3D& vectorB);

	// ����ƽ�ƾ���
	QMatrix4x4 makeTranslationMatrix(const QVector3D& translation);

	// ������ת����
	QMatrix4x4 makeRotationMatrix(float angle, const QVector3D& axis);

	// �������ž���
	QMatrix4x4 makeScaleMatrix(const QVector3D& scale);

	// ���ƽ����ת���ž���
	QMatrix4x4 makeTransformMatrix(const QVector3D& translation, float angle, const QVector3D& axis, const QVector3D& scale);

	// ��������ͶӰ����
	QMatrix4x4 makeOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane);

	// ����͸��ͶӰ����
	QMatrix4x4 makePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

} // namespace Math

} // namespace Utils