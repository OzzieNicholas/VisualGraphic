/*
 * MeshTri.h�������������ࣨMesh �����ࣩ
 *
 * ���ܸ�����
 *  - ��ʾ��������ͼԪ��ɵļ�������
 *  - ʵ�� Mesh �ӿڵı任�����������뵼���ȹ���
 *
 * ʹ�ó�����
 *  - ���潨ģ��ͼ�ι�����ʾ
 *  - ��άģ�Ϳ��ӻ��������任
 *  - �����ʷ��㷨�����δ������
 */

#pragma once

#include "./Mesh.h"

class MeshTri : public Mesh {
public:
    // ========== ���������� ========== //

    MeshTri();
    ~MeshTri();

    // ========== �����������ȡ ========== //

    // ���ö�������
    void setVertices(const std::vector<MeshVertex>& vertices) override;

    // ������������
    void setIndices(const std::vector<uint>& indices) override;

    // ����ͼԪ����
    void setDrawType(DrawPrimitiveType drawType) override;

    // ========== ���α任����� ========== //

    // Ӧ�ñ任�������ж���
    void applyTransform(const QMatrix4x4& matrix) override;

    // �����������
    std::vector<QVector3D> samplePoints(int count = 100) const override;

    // ========== �������빦�� ========== //

    // ����Ϊ JSON �ַ���
    std::string exportToJson() const override;

    // �� JSON �ַ�������
    void importFromJson(const std::string& json) override;
};
