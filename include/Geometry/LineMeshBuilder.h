/*
 * LineMeshBuilder.h���߶���������
 *
 * ���ܸ�����
 *  - �ṩһ�龲̬�������������ɸ����߶ι��ɵĸ���������
 *  - ���й�������Ϊ LineMesh ����
 *
 * ʹ�ó�����
 *  - ��Ⱦ��ά�����ᡢ���������ȸ���ͼԪ
 *  - �㷨�����е��м��߶Ρ����߹�����չʾ
 *  - ���ӻ������뼸�η���
 */

#pragma once

#include "./LineMesh.h"
#include "./TriMesh.h"

class LineMeshBuilder {
public:
    // ������ά�������ߣ�X/Y/Z ��������
    static LineMesh buildAxisLines(float length);

    // �������ߣ����Ӹ����㼯��
    static LineMesh buildPolylineMesh(const std::vector<QVector3D>& points, const QVector3D& color);

    // ���������߶Σ����������������ɣ�
    static LineMesh buildNormalLinesFromTriMesh(const TriMesh& mesh, float scale = 0.1f);
};
