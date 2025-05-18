#pragma once

#include "../Geometry/TriMesh.h"

#include<QMatrix4x4>

namespace Utils {

namespace Mesh {

// ������������
void scaleMesh(std::vector<QVector3D>& vertices, float factor);

// ��������ƽ��
void translateMesh(std::vector<QVector3D>& vertices, const QVector3D& translation);

// �ϲ������㼯�ϣ�����������ƫ�ƣ������ڿ��Ƶ�ȷ����˽ṹ��
void mergeMeshes(std::vector<QVector3D>& verticesA, const std::vector<QVector3D>& verticesB);

// Ϊ����������㶥�㷨�ߣ������淨�߼�Ȩƽ����
void computeNormals(std::vector<MeshVertex>& vertices, const std::vector<uint>& indices);

// �������Ļ���������ƽ����ԭ�㣩
void centerMesh(std::vector<QVector3D>& vertices);

// �Ƴ��ظ����㣨�����ڲü�/�����Ⱥ���
void removeDuplicateVertices(std::vector<QVector3D>& vertices, float tolerance = 1e-5f);

} // namespace Mesh

} // namespace Utils
