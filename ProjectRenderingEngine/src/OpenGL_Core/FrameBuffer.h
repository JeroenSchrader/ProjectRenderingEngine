#pragma once

class FrameBuffer {
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetColorBufferID() { return m_ColorBufferID; }
private:
	unsigned int m_ID;
	unsigned int m_RenderBufferID;
	unsigned int m_ColorBufferID;
};