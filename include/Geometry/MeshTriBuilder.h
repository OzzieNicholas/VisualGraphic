/*
 * MeshTriBuilder.h��������������
 *
 * ���ܸ�����
 *  - �ṩһ�龲̬�������������ɸ��ֱ�׼���������񼸺���
 *  - ���й�������Ϊ MeshTri ����
 *
 * ʹ�ó�����
 *  - ����ģ����Ⱦ��ʼ��
 *  - ��ά���곡���������桢��ͷ������ͼԪ��
 */

#pragma once

#include <cmath>
#include "./MeshTri.h"

class MeshTriBuilder {
public:
    // ������������XYƽ�棩
    static MeshTri buildGridMesh(uint rows, uint cols, float size);

    // ������������Z=0ƽ�棩
    static MeshTri buildGroundPlaneMesh(float size, uint resolution);

    // ����������ĩ�˼�ͷ
    static MeshTri buildArrowMesh(float radius, float height, int segments);

	// ��������������
    static MeshTri buildCubeMesh();

	// ������������
	static MeshTri buildSphereMesh(uint stacks, uint slices);
};
