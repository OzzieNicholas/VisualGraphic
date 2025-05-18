#pragma once

#include <vector>
#include <QVector3D>

//���ƵĻ���ͼԪ����
enum class DrawPrimitiveType {
    Points,
    Lines,
    Triangles,
    Quads,
};

// ͨ�ö������ݽṹ���������Ρ����ߡ���ɫ�����������
struct MeshVertex {
    QVector3D position;   // ����λ��
    QVector3D normal;     // ��������
    QVector3D color;      // ��ɫ��RGB��
    QVector3D texCoord;   // ��������
    QVector3D tangent;    // ��������
    QVector3D bitangent;  // ����������
};

// ���������ࣺ�������� Mesh ���͵�ͨ�ýӿ�
class Mesh {
public:
    virtual ~Mesh() = default;

// �����������������

    // ���ö�������
    virtual void setVertices(const std::vector<MeshVertex>& vertices) = 0;

    // ������������
    virtual void setIndices(const std::vector<uint>& indices) = 0;

    // ����ͼԪ����
    virtual void setDrawType(DrawPrimitiveType drawType) = 0;

    // ��ȡ��������
    virtual const std::vector<MeshVertex>& getVertices() const = 0;

    // ��ȡ��������
    virtual const std::vector<uint>& getIndices() const = 0;

    // ��ȡ��ǰ����ͼԪ����
    virtual DrawPrimitiveType getDrawType() const = 0;

    // �����������
    virtual void clear() = 0;

// ���������ж�

    // �ж϶���������Ƿ���Ч
    virtual bool isValid() const {
        return !vertices.empty() && !indices.empty();
    }

    // �Ƿ�Ϊ�պ�ͼ�Σ���պ����ߡ�����Σ�
    virtual bool isClosed() const {
        return false;
    }

    // ����ά�ȣ�����2��ʾ��ά���񣬷���3��ʾ��ά
    virtual int dimension() const;

    // �Ƿ������������
    virtual bool hasNormals() const;

    // ��ȡ��Χ�У�������С������㣩
    virtual std::pair<QVector3D, QVector3D> getBoundingBox() const;

// ���α任�����

    // Ӧ�ñ任�������ж���
    virtual void applyTransform(const QMatrix4x4& matrix) = 0;

    // ������/��������㣨������Ⱦ�򶯻���
    virtual std::vector<QVector3D> samplePoints(int count = 100) const {
        return {};
    }

// �����ӿڣ�JSON / SVG��

    // ����Ϊ SVG ·������ "M 0 0 L 1 1 ..."��
    virtual std::string toSvgPath() const {
        return {};
    }

    // ����Ϊ JSON �ַ���
    virtual std::string toJson() const {
        return {};
    }

    // �� JSON �ַ�������
    virtual void fromJson(const std::string&) {}

// ����֧��

    // ���ö���״̬���� t ������
    virtual void setAnimationStep(float step) {
        animationStep = step;
    }

    // ��ȡ����״̬����
    virtual float getAnimationStep() const {
        return animationStep;
    }

protected:
    std::vector<MeshVertex> vertices;       // ��������
    std::vector<uint> indices;              // ��������
    DrawPrimitiveType drawPrimitiveType;    // ͼԪ����
    float animationStep = 0.0f;             // �������������ڲ�ֵ��ʾ�ȣ�
};
