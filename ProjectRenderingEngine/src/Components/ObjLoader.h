#pragma once

#include <vector>
#include <string>

class Material;
class Texture;

struct ObjFileFormat {
	bool HasTextures;

	ObjFileFormat() {
		HasTextures = false;
	}
	~ObjFileFormat() = default;
};

class ObjLoader {
private:
	static ObjLoader* m_Instance;
	ObjLoader() = default;

	std::vector<std::string> SplitLine(std::string line);
	std::vector<std::string> SplitFaceLine(std::string line);
	std::vector<std::string> Split(std::string str, char delimiter);

public:
	static ObjLoader* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new ObjLoader();
		return m_Instance;
	}

	~ObjLoader() = default;

	void LoadMesh(std::istream& fileStream, std::vector<float>& vertexData, std::vector<unsigned int>& indices, ObjFileFormat& format);
	void LoadMaterial(const std::string& filename, Material& material, Texture& textureMap, Texture& normalMap);
};