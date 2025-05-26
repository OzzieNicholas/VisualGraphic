/*
 * MeshQuadBuilder.h���ı�����������
 *
 * ���ܸ�����
 *  - �ṩһ�龲̬���������ڹ��쳣�����ı������񼸺νṹ
 *  - ���й�������Ϊ MeshQuad ����
 *
 * ʹ�ó�����
 *  - ������ι��������ש���ذ塢���̸�
 *  - �����ı��νṹ����ɢ�����ʾ
 *  - ֧��ϸ�������㷨�����ν�ģ��ͼ�δ���
 */

#pragma once

#include "./MeshQuad.h"
#include <cmath>

class MeshQuadBuilder {
public:
    // ���������ı�������XY ƽ�棩
    static MeshQuad buildGridMesh(uint rows, uint cols, float size);

    // ��������ƽ�����񣨻�ɫ Z=0 �棩
    static MeshQuad buildGroundPlaneMesh(float size, uint resolution);

    // �������� Z ����ı����
    static MeshQuad buildZFacingQuad(float width, float height);

    // �����ı���������չ���ṹ������ֲ���
    static MeshQuad buildCubeFaceMesh();
};
