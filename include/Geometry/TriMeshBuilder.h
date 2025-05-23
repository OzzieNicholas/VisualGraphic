/*
 * TriMeshBuilder.h��������������
 *
 * ���ܸ�����
 *  - �ṩһ�龲̬�������������ɸ��ֱ�׼���������񼸺���
 *  - ���й�������Ϊ TriMesh ����
 *
 * ʹ�ó�����
 *  - ����ģ����Ⱦ��ʼ��
 *  - ��ά���곡���������桢��ͷ������ͼԪ��
 */

#pragma once

#include <cmath>
#include "./TriMesh.h"

class TriMeshBuilder {
public:
    // ������������XYƽ�棩
    static TriMesh buildGridMesh(uint rows, uint cols, float size);

    // ������������Z=0ƽ�棩
    static TriMesh buildGroundPlaneMesh(float size, uint resolution);

    // ����������ĩ�˼�ͷ
    static TriMesh buildArrowMesh(float radius, float height, int segments);

	// ��������������
    static TriMesh buildCubeMesh();

	// ������������
	static TriMesh buildSphereMesh(uint stacks, uint slices);
};
