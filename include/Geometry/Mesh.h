/*
 * Mesh.h���������ӿڶ��壨������ࣩ
 *
 * ���ܸ�����
 *  - �ṩ�����������ͣ��� TriMesh��LineMesh��QuadMesh �ȣ���ͳһ����ӿ�
 *  - �������㡢������ͼԪ���͡�����״̬��ͨ�����ݳ�Ա
 *  - �ṩ���η��ʡ��任���ж��������Ƚӿ�
 *  - ������ʵ�ֺ��Ĵ��麯����֧���Զ��幹������Ⱦ
 *
 * ʹ�ó�����
 *  - �������ݽ�ģ��Geometry ģ�飩
 *  - OpenGL ��Ⱦ�ϴ���Renderer ģ�飩
 *  - ֧����չ�����ߡ����������
 */

#pragma once

#include <vector>
#include <QVector3D>
#include <QMatrix4x4>

// ========== ����ͼԪ���� ========== //
enum class DrawPrimitiveType {
    Points,
    Lines,
    Triangles,
    Quads,
};

// ========== �������ݽṹ ========== //
struct MeshVertex {
    QVector3D position;   // ����λ��
    QVector3D normal;     // ��������
    QVector3D color;      // ��ɫ��RGB��
    QVector3D texCoord;   // ��������
    QVector3D tangent;    // ��������
    QVector3D bitangent;  // ����������
};

// ========== ���������� ========== //
class Mesh {
public:
    virtual ~Mesh() = default;

    // ========== �����������ȡ ========== //

    // ���ö�������
    virtual void setVertices(const std::vector<MeshVertex>& vertices) = 0;

    // ������������
    virtual void setIndices(const std::vector<uint>& indices) = 0;

    // ����ͼԪ����
    virtual void setDrawType(DrawPrimitiveType drawType) = 0;

    // ��ȡ��������
    virtual const std::vector<MeshVertex>& getVertices() const;

    // ��ȡ��������
    virtual const std::vector<uint>& getIndices() const;

    // ��ȡ��ǰ����ͼԪ����
    virtual DrawPrimitiveType getDrawPrimitiveType() const;

    // ��ȡ��Χ��
    virtual std::pair<QVector3D, QVector3D> computeBoundingBox() const;

    // �����������
    virtual void clearGeometryData();

    // ========== ���������ж� ========== //

    // �ж϶���������Ƿ���Ч
    virtual bool hasValidGeometry() const;

    // �ж�ͼ���Ƿ�պ�
    virtual bool isGeometryClosed() const;

    // �жϼ���ά�ȣ�����2��ʾ��ά���񣬷���3��ʾ��ά
    virtual int getGeometryDimension() const;

    // �ж��Ƿ������������
    virtual bool hasNormalData() const;

    // ======== ���α任����� ======== //

    // Ӧ�ñ任�������ж���
    virtual void applyTransform(const QMatrix4x4& matrix) = 0;

    // ������/��������㣨������Ⱦ�򶯻���
    virtual std::vector<QVector3D> samplePoints(int count = 100) const;

    // ======== ���ӻ� ======== //

    // ���ö���״̬����
    virtual void setAnimationStep(float step);

    // ��ȡ����״̬����
    virtual float getAnimationStep() const;

    // ======== �������� ======== //

    // ����Ϊ SVG ·��
    virtual std::string exportToSvgPath() const {
        return {};
    }

    // ����Ϊ JSON �ַ���
    virtual std::string exportToJson() const;

    // �� JSON �ַ�������
    virtual void importFromJson(const std::string&);

protected:
    std::vector<MeshVertex> vertices;       // ��������
    std::vector<uint> indices;              // ��������
    DrawPrimitiveType drawPrimitiveType;    // ͼԪ����
    float animationStep = 0.0f;             // �������������ڲ�ֵ��ʾ�ȣ�
};
