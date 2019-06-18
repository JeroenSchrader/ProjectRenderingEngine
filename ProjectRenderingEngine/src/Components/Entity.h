#pragma once

#include <string>
#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"

class OpenGLMesh;
class Material;
class Texture;
class LightingInformation;

class Entity {
private:
	std::string m_Name;
	OpenGLMesh* m_Mesh;
	Material* m_Material;
	Texture* m_TextureMap;
	Texture* m_NormalMap;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

public:
	Entity(std::string& name, OpenGLMesh* mesh, Material* material, Texture* textureMap, Texture* normalMap, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotations = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	~Entity();

	glm::mat4 GetTransformationMatrix();
	const void Bind();

	const void SetProjectionMatrix(glm::mat4 projectionMatrix);
	const void SetViewMatrix(glm::mat4 viewMatrix);
	const void SetTransformationMatrix(glm::mat4 transformationMatrix);
	const void SetLightingInformation(LightingInformation& information);

	inline glm::vec3& GetPosition() { return m_Position; }
	inline glm::vec3& GetRotation() { return m_Rotation; }
	inline glm::vec3& GetScale() { return m_Scale; }
	inline std::string& GetName() { return m_Name; }

	inline OpenGLMesh* GetMesh() const { return m_Mesh; }
	inline Material* GetMaterial() const { return m_Material; }
	inline Texture* GetTextureMap() const { return m_TextureMap; }
	inline Texture* GetNormalMap() const { return m_NormalMap; }
};