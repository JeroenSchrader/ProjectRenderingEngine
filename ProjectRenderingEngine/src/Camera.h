#pragma once

#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"
#include "InputManager.h"

class Camera {
private:
	InputManager* m_InputManager;
	glm::vec3 m_Position = glm::vec3(4.0f, 0.0f, 4.0f);
	glm::mat4 m_ProjectionMatrix;
	float m_Pitch = 0.0f;
	float m_Yaw = 0.0f;
	float m_MoveSpeed;
	float m_TurnSpeed;
	float m_HorizontalAngleInDegrees;
	float m_VerticalAngleInDegrees;

	const glm::mat4 GetOrientation();

public:
	Camera(InputManager* inputManager, float moveSpeed, float turnSpeed, float FoV, float nearPlane, float farPlane);
	~Camera();

	void Update();

	glm::mat4 GetViewMatrix();
	inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline glm::vec3 GetPosition() const { return m_Position; }
	inline float GetPitch() const { return m_Pitch; }
	inline float GetYaw() const { return m_Yaw; }
	glm::vec3 Up();
	glm::vec3 Right();
	glm::vec3 Forward();
};