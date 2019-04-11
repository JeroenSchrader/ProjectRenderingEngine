#include <iostream>

#include "Renderer.h"

Renderer::Renderer()
{
	if (glewInit() != GLEW_OK) {
		throw std::exception("Glew init error");
	}
}

Renderer::~Renderer()
{
}

void Renderer::Draw(unsigned int ibCount)
{
	glDrawElements(GL_TRIANGLES, ibCount, GL_UNSIGNED_INT, nullptr);
}
