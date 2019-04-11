#pragma once

#include <GLEW/glew.h>

class Renderer {
private:

public:
	Renderer();
	~Renderer();
	void Draw(unsigned int ibCount);
};
