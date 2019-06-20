#pragma once

#include <GLEW/glew.h>
#include <iostream>

class Renderer {
private:
	static Renderer* m_Instance;
	Renderer();

public:
	static Renderer* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new Renderer;
		return m_Instance;
	}

	~Renderer() = default;
	void Draw(unsigned int ibCount);
};
