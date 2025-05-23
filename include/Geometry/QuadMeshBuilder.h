/*
 * QuadMeshBuilder.h���ı�����������
 *
 * ���ܸ�����
 *  - �ṩһ�龲̬���������ڹ��쳣�����ı������񼸺νṹ
 *  - ���й�������Ϊ QuadMesh ����
 *
 * ʹ�ó�����
 *  - ������ι��������ש���ذ塢���̸�
 *  - �����ı��νṹ����ɢ�����ʾ
 *  - ֧��ϸ�������㷨�����ν�ģ��ͼ�δ���
 */

#pragma once

#include "./QuadMesh.h"
#include <cmath>

class QuadMeshBuilder {
public:
    // ���������ı�������XY ƽ�棩
    static QuadMesh buildGridMesh(uint rows, uint cols, float size);

    // ��������ƽ�����񣨻�ɫ Z=0 �棩
    static QuadMesh buildGroundPlaneMesh(float size, uint resolution);

    // �������� Z ����ı����
    static QuadMesh buildZFacingQuad(float width, float height);

    // �����ı���������չ���ṹ������ֲ���
    static QuadMesh buildCubeFaceMesh();
};
