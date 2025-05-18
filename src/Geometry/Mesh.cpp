#include "../../include/Geometry/Mesh.h"

// ����ά�ȣ�����2��ʾ��ά���񣬷���3��ʾ��ά
int Mesh::dimension() const {
    if (vertices.empty()) return 0;
    bool is2D = std::all_of(
        vertices.begin(),
        vertices.end(),
        [](const MeshVertex& v) {
            return std::abs(v.position.z()) < 1e-6;
        }
    );
    return is2D ? 2 : 3;
}

// �Ƿ������������
bool Mesh::hasNormals() const {
    return std::any_of(
        vertices.begin(),
        vertices.end(),
        [](const MeshVertex& v) {
            return !v.normal.isNull();
        }
    );
}

// ��ȡ��Χ�У�������С������㣩
std::pair<QVector3D, QVector3D> Mesh::getBoundingBox() const {
    if (vertices.empty()) return { {}, {} };
    QVector3D min = vertices[0].position;
    QVector3D max = vertices[0].position;
    for (const auto& v : vertices) {
        min.setX(std::min(min.x(), v.position.x()));
        min.setY(std::min(min.y(), v.position.y()));
        min.setZ(std::min(min.z(), v.position.z()));
        max.setX(std::max(max.x(), v.position.x()));
        max.setY(std::max(max.y(), v.position.y()));
        max.setZ(std::max(max.z(), v.position.z()));
    }
    return { min, max };
}
