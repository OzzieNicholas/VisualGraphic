/*
 * LineMesh.h���߶������ࣨMesh �����ࣩ
 *
 * ���ܸ�����
 *  - ��ʾ���߶�ͼԪ���ɵ���������
 *  - ֧��������ʾ�����ᡢ�������������ߵȸ�����Ϣ
 *
 * ʹ�ó�����
 *  - ���ӻ�����ͼԪ��������ϵ��
 *  - �㷨���Թ����еı�Ե�ṹչʾ
 *  - ��Ⱦ���ߡ�����·�����߽��ߵ�
 */

#pragma once

#include "./Mesh.h"

class LineMesh : public Mesh {
public:
    // ========== ���������� ========== //

    LineMesh();
    ~LineMesh();

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
