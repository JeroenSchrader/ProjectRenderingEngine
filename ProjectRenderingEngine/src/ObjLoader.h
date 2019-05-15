#pragma once

#include <vector>
#include <string>

class Material;
class Texture;

struct ObjFileFormat {
	bool HasTextures;
	bool HasNormals;

	ObjFileFormat() {
		HasTextures = false;
		HasNormals = false;
	}
	~ObjFileFormat() = default;
};

class ObjLoader {
private:
	std::vector<std::string> SplitLine(std::string line);
	std::vector<std::string> SplitFaceLine(std::string line);
	std::vector<std::string> Split(std::string str, char delimiter);

public:
	ObjLoader() = default;
	~ObjLoader() = default;

	void LoadMesh(const std::string& filename, std::vector<float>& vertexData, std::vector<unsigned int>& indices, ObjFileFormat& format);
	void LoadMaterial(const std::string& filename, Material& material, Texture& texture);
};