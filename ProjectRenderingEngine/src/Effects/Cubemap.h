#pragma once

#include <string>

class Cubemap {
public:
	Cubemap(std::string path);
	~Cubemap() = default;

	void Bind();

private:
	unsigned int m_ID;
};