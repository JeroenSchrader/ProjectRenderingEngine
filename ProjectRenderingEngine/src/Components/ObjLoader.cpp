#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "GLM/vec3.hpp"
#include "GLM/vec2.hpp"
#include "Material.h"
#include "Texture.h"
#include "GLM/geometric.hpp"

void ObjLoader::LoadMesh(std::istream& fileStream, std::vector<float>& vertexData, std::vector<unsigned int>& indices, ObjFileFormat &format)
{
	if (fileStream.fail()) {
		std::cout << "Failed to open filestream" << std::endl;
		return;
	}
	std::string line;

	std::vector<glm::vec3> loadedVertices;
	std::vector<glm::vec2> loadedTextures;
	std::vector<glm::vec3> loadedNormals;

	unsigned int index = 0;
	
	while (std::getline(fileStream, line)) {
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
			std::vector<std::string> splitString = SplitLine(line);
			std::vector<glm::vec3> positions;
			std::vector<glm::vec2> textureCoords;
			std::vector<glm::vec3> normals;

			assert(loadedVertices.size() > 0);
			assert(loadedNormals.size() > 0);

			for (size_t i = 0; i < 3; i++)
			{
				std::vector<std::string> faceData = SplitFaceLine(splitString[i]);
				glm::vec3 position = loadedVertices[static_cast<int64_t>(std::stoi(faceData[0])) - 1];
				positions.push_back(position);
				if (faceData.size() > 2) {
					format.HasTextures = true;
					glm::vec2 texture = loadedTextures[static_cast<int64_t>(std::stoi(faceData[1])) - 1];
					textureCoords.push_back(texture);
					glm::vec3 normal = loadedNormals[static_cast<int64_t>(std::stoi(faceData[2])) - 1];
					normals.push_back(normal);
				}
				else {
					format.HasTextures = false;
					glm::vec3 normal = loadedNormals[static_cast<int64_t>(std::stoi(faceData[1])) - 1];
					normals.push_back(normal);
				}
				indices.push_back(index++);
				indices.push_back(index++);
				indices.push_back(index++);

				if (i == 2) {
					assert(positions.size() == normals.size());

					glm::vec3 tangent;
					glm::vec3 bitangent;
					if (format.HasTextures) {
						//Calculate tangent and bi-tangent, only if all values have been gathered and the model has textures
						glm::vec3 edge1 = positions[1] - positions[0];
						glm::vec3 edge2 = positions[2] - positions[0];
						glm::vec2 deltaUV1 = textureCoords[1] - textureCoords[0];
						glm::vec2 deltaUV2 = textureCoords[2] - textureCoords[0];

						float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

						tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent = glm::normalize(tangent);

						bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent = glm::normalize(bitangent);
					}

					for (size_t i = 0; i < positions.size(); i++)
					{
						if (format.HasTextures) {
							assert(positions.size() == textureCoords.size());
						}
						vertexData.push_back(positions[i].x);
						vertexData.push_back(positions[i].y);
						vertexData.push_back(positions[i].z);
						if (format.HasTextures) {
							vertexData.push_back(textureCoords[i].x);
							vertexData.push_back(textureCoords[i].y);
						}
						vertexData.push_back(normals[i].x);
						vertexData.push_back(normals[i].y);
						vertexData.push_back(normals[i].z);
						if (format.HasTextures) {
							vertexData.push_back(tangent.x);
							vertexData.push_back(tangent.y);
							vertexData.push_back(tangent.z);
							vertexData.push_back(bitangent.x);
							vertexData.push_back(bitangent.y);
							vertexData.push_back(bitangent.z);
						}
					}	
				}
			}
		}
	}
}

void ObjLoader::LoadMaterial(const std::string& filename, Material& material, Texture& textureMap, Texture& normalMap)
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
		else if (line.find("map_Ka ") != std::string::npos) {

		}
		else if (line.find("Ka ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			material.GetAmbient() = glm::vec3(std::stof(splitString[0]), std::stof(splitString[1]), std::stof(splitString[2]));
		}
		else if (line.find("map_Kd ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			textureMap.LoadNewTexture("res/textures/" + splitString[0], TextureTypes::TextureMap);
		}
		else if (line.find("map_Bump ") != std::string::npos) {
			std::vector<std::string> splitString = SplitLine(line);
			normalMap.LoadNewTexture("res/normals/" + splitString[0], TextureTypes::NormalMap);
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
