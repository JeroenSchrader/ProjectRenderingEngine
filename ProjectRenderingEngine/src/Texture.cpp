#include <iostream>
#include "Texture.h"
#include "Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Stb/stb_image.h"

Texture::Texture(std::string file)
{
	LoadNewTexture(file);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Id);
}

void Texture::LoadNewTexture(std::string file)
{
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file.c_str(), &m_Width, &m_Height, &m_NrOfChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture: " << file << std::endl;
	}
	stbi_image_free(data);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
