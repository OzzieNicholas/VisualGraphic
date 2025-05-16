#pragma once
#include "./TriMesh.h"

class TriMesh;

class TriMeshBuilder {
public:
    static TriMesh createGrid(uint rows, uint cols, float size);
    static TriMesh createAxisLines(float length); // ������ά�ռ�������ᣨ���߶Σ�
    static TriMesh createGroundPlane(float size, uint resolution); // ����Z=0��ɫ���棨���������棩
    static TriMesh createAxisArrow(float radius, float height, int segments); // �����򵥼�ͷ����СԲ׶��
	static TriMesh createPolyline(const std::vector<QVector3D>& points, const QVector3D& color); // ��������
};
