#pragma once

#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"

class Mesh;
class Material;

class Entity {
private:
	Mesh* m_Mesh;
	Material* m_Material;

	glm::vec3 m_Position;
	float m_RotationXInDegrees;
	float m_RotationYInDegrees;
	float m_RotationZInDegrees;
	glm::vec3 m_Scale;

public:
	Entity(Mesh* mesh, Material* material, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotations = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	~Entity();

	glm::mat4 GetTransformationMatrix();
	const void BindMaterial();

	const void SetProjectionMatrix(glm::mat4 projectionMatrix);
	const void SetViewMatrix(glm::mat4 viewMatrix);
	const void SetTransformationMatrix(glm::mat4 transformationMatrix);

	inline Mesh* GetMesh() const { return m_Mesh; }
	inline Material* GetMaterial() const { return m_Material; }
};