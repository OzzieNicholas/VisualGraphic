/*
 * TriMesh.h�������������ࣨMesh �����ࣩ
 *
 * ���ܸ�����
 *  - ʵ�� Mesh �ӿڣ�ר����������ͼԪ���͵������ʾ
 *  - ���ڱ��潨ģ�����ӻ��������������任������
 *
 * ����˵����
 *  - Ĭ��ͼԪ���͹̶�Ϊ DrawPrimitiveType::Triangles
 *  - ֧�ֻ������β���������任�����뵼���Ƚӿ�
 */

#pragma once

#include "./Mesh.h"

class TriMesh : public Mesh {
public:
    // ========== ���������� ========== //

    TriMesh();
    ~TriMesh();

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
