#pragma once

class IndexBuffer {
private:
	unsigned int m_Id;
	unsigned int m_Count;

public:
	IndexBuffer();
	IndexBuffer(const unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	
	inline const unsigned int GetId() const { return m_Id; }
	inline const unsigned int GetCount() const { return m_Count; }
};
