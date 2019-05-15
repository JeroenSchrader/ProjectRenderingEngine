#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "GLM/vec3.hpp"
#include "GLM/vec2.hpp"
#include "Material.h"
#include "Texture.h"

void ObjLoader::LoadMesh(const std::string& filename, std::vector<float>& vertexData, std::vector<unsigned int>& indices, ObjFileFormat &format)
{
	std::ifstream fileStream(filename);
	if (fileStream.fail()) {
		std::cout << "Failed to open filestream for " << filename << std::endl;
		return;
	}
	std::string line;

	std::vector<glm::vec3> loadedVertices;
	std::vector<glm::vec2> loadedTextures;
	std::vector<glm::vec3> loadedNormals;

	unsigned int index = 0;
	bool finishedFacing = true;

	while (std::getline(fileStream, line)) {
		if (line.find("f ") == std::string::npos && finishedFacing == false) {
			finishedFacing = true;
			loadedVertices.clear();
			loadedTextures.clear();
			loadedNormals.clear();
		}

		if (line.find("v ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			glm::vec3 vertex(std::stof(splitString[0]), std::stof(splitString[1]), std::stof(splitString[2]));
			loadedVertices.push_back(vertex);
		}
		else if (line.find("vt ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			glm::vec2 texture(std::stof(splitString[0]), std::stof(splitString[1]));
			loadedTextures.push_back(texture);
		}
		else if (line.find("vn ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			glm::vec3 normal(std::stof(splitString[0]), std::stof(splitString[1]), std::stof(splitString[2]));
			loadedNormals.push_back(normal);
		}
		else if (line.find("f ") != std::string::npos) {
			if (finishedFacing) {
				finishedFacing = false;
			}

			std::vector<std::string> splitString = SplitLine(line);
			for (size_t i = 0; i < 3; i++)
			{
				std::vector<std::string> faceData = SplitFaceLine(splitString[i]);
				glm::vec3 position = loadedVertices[std::stoi(faceData[0]) - 1];
				vertexData.push_back(position.x);
				vertexData.push_back(position.y);
				vertexData.push_back(position.z);
				if (faceData.size() > 2) {
					format.HasTextures = true;
					format.HasNormals= true;
					glm::vec2 texture = loadedTextures[std::stoi(faceData[1]) - 1];
					vertexData.push_back(texture.x);
					vertexData.push_back(texture.y);
					glm::vec3 normal = loadedNormals[std::stoi(faceData[2]) - 1];
					vertexData.push_back(normal.x);
					vertexData.push_back(normal.y);
					vertexData.push_back(normal.z);
				}
				else {
					format.HasTextures = false;
					format.HasNormals = true;
					glm::vec3 normal = loadedNormals[std::stoi(faceData[1]) - 1];
					vertexData.push_back(normal.x);
					vertexData.push_back(normal.y);
					vertexData.push_back(normal.z);
				}
				indices.push_back(index++);
				indices.push_back(index++);
				indices.push_back(index++);
			}
		}
	}
}

void ObjLoader::LoadMaterial(const std::string& filename, Material& material, Texture& texture)
{
	std::ifstream fileStream(filename);
	if (fileStream.fail()) {
		std::cout << "Failed to open filestream for " << filename << std::endl;
		return;
	}
	std::string line;

	while (std::getline(fileStream, line)) {
		if (line.find("Ns ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			material.GetShininess() = std::stof(splitString[0]);
		}
		else if (line.find("Ka ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			material.GetAmbient() = glm::vec3(std::stof(splitString[0]), std::stof(splitString[1]), std::stof(splitString[2]));
		}
		else if (line.find("map_Kd ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			texture.LoadNewTexture("res/textures/" + splitString[0]);
		}
		else if (line.find("Kd ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			material.GetDiffuse() = glm::vec3(std::stof(splitString[0]), std::stof(splitString[1]), std::stof(splitString[2]));
		}
		else if (line.find("Ks ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			material.GetSpecular() = glm::vec3(std::stof(splitString[0]), std::stof(splitString[1]), std::stof(splitString[2]));
		}
	}
}

std::vector<std::string> ObjLoader::SplitLine(std::string line) {
	std::vector<std::string> splitString = Split(line, ' ');
	splitString.erase(splitString.begin()); //remove first element as it's not actual data
	return splitString;
}

std::vector<std::string> ObjLoader::SplitFaceLine(std::string line) {
	std::vector<std::string> splitString = Split(line, ' ');
	std::vector<std::string> faceIndices = Split(splitString[0], '/');

	return faceIndices;
}

std::vector<std::string> ObjLoader::Split(std::string str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str); // Turn the string into a stream.
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		if (token.find_first_not_of(" ") != std::string::npos) {
			tokens.push_back(token);
		}
	}

	return tokens;
}
