#pragma once

#include <QVector>
#include <QMatrix4x4>

namespace Utils{

namespace Math {

inline QVector3D crossProduct(const QVector3D& a, const QVector3D& b) {
	return QVector3D::crossProduct(a, b);
}

inline float dotProduct(const QVector3D& a, const QVector3D& b) {
	return QVector3D::dotProduct(a, b);
}

inline QMatrix4x4 makeTranslationMatrix(const QVector3D& translation) {
	QMatrix4x4 matrix;
	matrix.translate(translation);
	return matrix;
}

inline QMatrix4x4 makeRotationMatrix(float angle, const QVector3D& axis) {
	QMatrix4x4 matrix;
	matrix.rotate(angle, axis);
	return matrix;
}

} // namespace Math

} // namespace Utils