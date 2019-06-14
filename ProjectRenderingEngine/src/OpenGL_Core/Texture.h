#pragma once

#include <string>

enum TextureTypes {
	None,
	TextureMap = 33984, //So they correspond with GL_ENUM values
	NormalMap
};

class Texture {
private:
	unsigned int m_Id;
	unsigned char* m_ImageData;
	int m_Width;
	int m_Height;
	int m_NrOfChannels;
	TextureTypes m_TextureType;
public:
	Texture() : m_Id(0), m_ImageData(nullptr), m_Width(0), m_Height(0), m_NrOfChannels(0), m_TextureType(TextureTypes::None){};
	Texture(std::string file, TextureTypes type);
	~Texture();

	void LoadNewTexture(std::string file, TextureTypes type);

	void Bind();
	void Unbind() const;

	inline TextureTypes& GetTextureType() { return m_TextureType; }
};