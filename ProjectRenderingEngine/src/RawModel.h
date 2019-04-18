#pragma once

class RawModel {
private:
	unsigned int m_VertexArrayID;
	unsigned int m_VertexIndexCount;
public:
	RawModel(unsigned int vertexArrayID, unsigned int vertexIndexCount) : m_VertexArrayID(vertexArrayID), m_VertexIndexCount(vertexIndexCount) {};
	~RawModel() {};

	inline const unsigned int GetVertexArrayId() const { return m_VertexArrayID; }
	inline const unsigned int GetVertexIndexCount() const { return m_VertexIndexCount; }
};