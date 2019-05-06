#pragma once

class VertexBuffer {
private:
	unsigned int m_Id;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;

	inline const unsigned int GetId() const { return m_Id; }
};