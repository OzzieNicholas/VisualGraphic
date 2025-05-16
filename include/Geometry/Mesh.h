#pragma once

#include <vector>
#include <QVector3D>

enum class DrawPrimitiveType {
    Points,
    Lines,
    Triangles,
    Quads,
};

struct MeshVertex {
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    QVector3D texCoord;
    QVector3D tangent;
    QVector3D bitangent;
};

class Mesh {
public:
    virtual ~Mesh() = default;
    virtual void setVertices(const std::vector<MeshVertex>& vertices) = 0;
    virtual void setIndices(const std::vector<uint>& indices) = 0;
    virtual void setDrawType(DrawPrimitiveType drawType) = 0;
    virtual const std::vector<MeshVertex>& getVertices() const = 0;
    virtual const std::vector<uint>& getIndices() const = 0;
    virtual DrawPrimitiveType getDrawType() const = 0;
    virtual void clear() = 0;

protected:
    std::vector<MeshVertex> vertices;
    std::vector<uint> indices;
    DrawPrimitiveType drawPrimitiveType;
};