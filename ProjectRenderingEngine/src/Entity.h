#pragma once

#include "Mesh.h"
#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"

class Entity {
private:
	Mesh* m_Mesh;

	glm::vec3 m_Position;
	float m_RotationXInDegrees;
	float m_RotationYInDegrees;
	float m_RotationZInDegrees;
	glm::vec3 m_Scale;

public:
	Entity(Mesh* mesh, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotations = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	~Entity();

	glm::mat4 GetTransformationMatrix();

	inline Mesh* GetMesh() const { return m_Mesh; }
};