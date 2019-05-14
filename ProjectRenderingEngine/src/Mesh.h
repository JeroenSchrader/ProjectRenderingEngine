#pragma once

#include "GLM/vec3.hpp"
#include <vector>

class Mesh {
private:
	std::vector<unsigned int> m_Indices;
	std::vector<float> m_Vertices;

public:
	Mesh() = default;
	virtual ~Mesh() = default;

	inline std::vector<unsigned int>& GetIndices() { return m_Indices; }
	inline std::vector<float>& GetVertices() { return m_Vertices; }

	inline const unsigned int GetVertexIndexCount() { return m_Indices.size(); }
};