#include <iostream>
#include "Texture.h"
#include "Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Stb/stb_image.h"

Texture::Texture(std::string file, TextureTypes type)
	: m_TextureType(type)
{
	LoadNewTexture(file, type);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Id);
}

void Texture::LoadNewTexture(std::string file, TextureTypes type)
{
	glGenTextures(1, &m_Id);
	m_TextureType = type;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file.c_str(), &m_Width, &m_Height, &m_NrOfChannels, 0);
	if (data) {

		GLenum format;
		if (m_NrOfChannels == 1)
			format = GL_RED;
		else if (m_NrOfChannels == 3)
			format = GL_RGB;
		else if (m_NrOfChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load texture: " << file << std::endl;
	}
}

void Texture::Bind()
{
	glActiveTexture((int)GetTextureType());
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
