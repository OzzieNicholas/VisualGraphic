/*
 * MeshQuad.h���ı��������ࣨMesh �����ࣩ
 *
 * ���ܸ�����
 *  - ��ʾ���ı���ͼԪ��ɵļ�������
 *  - ʵ�� Mesh �ӿڣ�֧�ֱ任����������������Ȳ���
 *
 * ʹ�ó�����
 *  - ƽ��ṹ��ģ��ֿ����չʾ
 *  - �����ı��ε�����ϸ��չʾ�������ʾ
 *  - �㷨�����������ı���Ԫ��ʾ����ӻ�
 */

#pragma once

#include "./Mesh.h"

class MeshQuad : public Mesh {
public:
    // ========== ���������� ========== //

    MeshQuad();
    ~MeshQuad();

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
