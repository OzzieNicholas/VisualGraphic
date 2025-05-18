#pragma once

#include "./Mesh.h"

class TriMesh : public Mesh {
public:
	TriMesh();
	~TriMesh();

	void setVertices(const std::vector<MeshVertex>& vertices) override;
	void setIndices(const std::vector<uint>& indices) override;
	void setDrawType(DrawPrimitiveType drawType) override;

	const std::vector<MeshVertex>& getVertices() const override;
	const std::vector<uint>& getIndices() const override;
	DrawPrimitiveType getDrawType() const override;

	void clear() override;
};