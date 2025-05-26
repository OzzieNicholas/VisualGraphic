/*
 * MeshLineBuilder.h���߶���������
 *
 * ���ܸ�����
 *  - �ṩһ�龲̬�������������ɸ����߶ι��ɵĸ���������
 *  - ���й�������Ϊ MeshLine ����
 *
 * ʹ�ó�����
 *  - ��Ⱦ��ά�����ᡢ���������ȸ���ͼԪ
 *  - �㷨�����е��м��߶Ρ����߹�����չʾ
 *  - ���ӻ������뼸�η���
 */

#pragma once

#include "./MeshLine.h"
#include "./MeshTri.h"

class MeshLineBuilder {
public:
    // ������ά�������ߣ�X/Y/Z ��������
    static MeshLine buildAxisLines(float length);

    // �������ߣ����Ӹ����㼯��
    static MeshLine buildPolylineMesh(const std::vector<QVector3D>& points, const QVector3D& color);

    // ���������߶Σ����������������ɣ�
    static MeshLine buildNormalLinesFromTriMesh(const MeshTri& mesh, float scale = 0.1f);
};
