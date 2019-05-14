#pragma once

#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"

class OpenGLMesh;
class Material;

struct LightingInformation {
	//Ambient
	glm::vec3 AmbientColor;
	float AmbientStrength;
	//Diffuse
	glm::vec3 DiffuseColor;
	glm::vec3 DiffusePosition;
	//Specular
	glm::vec3 SpecularColor;
	float SpecularStrength;
	glm::vec3 CameraPosition;
};

class Entity {
private:
	OpenGLMesh* m_Mesh;
	Material* m_Material;

	glm::vec3 m_Position;
	float m_RotationXInDegrees;
	float m_RotationYInDegrees;
	float m_RotationZInDegrees;
	glm::vec3 m_Scale;

public:
	Entity(OpenGLMesh* mesh, Material* material, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotations = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	~Entity();

	glm::mat4 GetTransformationMatrix();
	const void Bind();

	const void SetProjectionMatrix(glm::mat4 projectionMatrix);
	const void SetViewMatrix(glm::mat4 viewMatrix);
	const void SetTransformationMatrix(glm::mat4 transformationMatrix);
	const void SetLightingInformation(LightingInformation& information);

	inline OpenGLMesh* GetMesh() const { return m_Mesh; }
	inline Material* GetMaterial() const { return m_Material; }
};