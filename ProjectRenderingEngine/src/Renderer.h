#pragma once

#include <GLEW/glew.h>

class Renderer {
private:

public:
	Renderer();
	~Renderer() = default;
	void Draw(unsigned int ibCount);
};
