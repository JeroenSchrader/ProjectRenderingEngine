#pragma once

#include <string>
#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"

class OpenGLMesh;
class Material;

struct LightingInformation {
	glm::vec3 Position;
	//Ambient
	glm::vec3 AmbientColor;
	float AmbientStrength;
	//Diffuse
	glm::vec3 DiffuseColor;
	float DiffuseStrength;
	//Specular
	glm::vec3 SpecularColor;
	float SpecularStrength;
	glm::vec3 CameraPosition;
};

class Entity {
private:
	std::string m_Name;
	OpenGLMesh* m_Mesh;
	Material* m_Material;

	glm::vec3 m_Position;
	float m_RotationXInDegrees;
	float m_RotationYInDegrees;
	float m_RotationZInDegrees;
	glm::vec3 m_Scale;

public:
	Entity(std::string& name, OpenGLMesh* mesh, Material* material, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotations = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	~Entity();

	glm::mat4 GetTransformationMatrix();
	const void Bind();

	const void SetProjectionMatrix(glm::mat4 projectionMatrix);
	const void SetViewMatrix(glm::mat4 viewMatrix);
	const void SetTransformationMatrix(glm::mat4 transformationMatrix);
	const void SetLightingInformation(LightingInformation& information);

	inline glm::vec3& GetPosition() { return m_Position; }
	inline std::string& GetName() { return m_Name; }

	inline OpenGLMesh* GetMesh() const { return m_Mesh; }
	inline Material* GetMaterial() const { return m_Material; }
};