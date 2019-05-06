#pragma once

#include "GLM/vec3.hpp"
#include <vector>

class Mesh {
private:
	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec3> m_Uvs;
	std::vector<glm::vec3> m_Normals;
	std::vector<unsigned int> m_Indices;
	std::vector<float> m_Vertices;

public:
	Mesh() : m_Vertices(), m_Positions(), m_Uvs(), m_Normals(), m_Indices() {}
	virtual ~Mesh() = default;

	inline std::vector<glm::vec3>& GetPositions(){ return m_Positions; }
	inline std::vector<glm::vec3>& GetUvs() { return m_Uvs; }
	inline std::vector<glm::vec3>& GetNormals() { return m_Normals; }
	inline std::vector<unsigned int>& GetIndices() { return m_Indices; }
	inline std::vector<float>& GetVertices() { return m_Vertices; }

	inline const unsigned int GetVertexIndexCount() { return m_Indices.size(); }
};