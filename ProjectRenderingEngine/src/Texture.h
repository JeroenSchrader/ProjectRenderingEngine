#pragma once

#include <string>

class Texture {
private:
	unsigned int m_Id;
	unsigned char* m_ImageData;
	int m_Width;
	int m_Height;
	int m_NrOfChannels;
public:
	Texture() : m_Id(0), m_ImageData(nullptr), m_Width(0), m_Height(0), m_NrOfChannels(0) {};
	Texture(std::string file);
	~Texture();

	void LoadNewTexture(std::string file);

	void Bind() const;
	void Unbind() const;
};