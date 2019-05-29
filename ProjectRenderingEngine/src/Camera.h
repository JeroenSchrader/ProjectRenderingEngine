#pragma once

#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"
#include "InputManager.h"

class Camera {
private:
	static Camera* m_Instance;
	Camera(InputManager* inputManager, float moveSpeed, float turnSpeed, float FoV, float nearPlane, float farPlane, GLFWwindow* window);

	InputManager* m_InputManager;
	GLFWwindow* m_Window;
	glm::vec3 m_Position = glm::vec3(0.0f, 8.0f, 8.0f);
	glm::mat4 m_ProjectionMatrix;
	float m_Pitch = 0.0f;
	float m_Yaw = 0.0f;
	float m_MoveSpeed = 1.0f;
	float m_ScrollSpeed = 1.5f;
	float m_TurnSpeed = 1.0f;
	int m_MaxZoomSteps = 7;
	int m_CurrentZoomSteps = 0;

	glm::vec3 m_Right = glm::cross(glm::normalize(m_Position - glm::vec3(0.0)), glm::vec3(0.0, 1.0, 0.0));
	glm::vec3 m_Up = -glm::cross(glm::normalize(m_Position - glm::vec3(0.0)), m_Right);
	glm::vec3 m_Forward = glm::cross(m_Right, m_Up);

public:
	~Camera() = default;

	static Camera* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new Camera(InputManager::GetInstance(), 1.0f, 1.0f, 90.0f, 0.01f, 1000.0f, DisplayManager::GetInstance()->GetWindow());
		return m_Instance;
	}

	void Update();

	glm::mat4 GetViewMatrix();
	inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline glm::vec3& GetPosition() { return m_Position; }
	inline float GetScrollSpeed() { return m_ScrollSpeed; }
	inline float GetPitch() const { return m_Pitch; }
	inline float GetYaw() const { return m_Yaw; }

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Camera* instance = Camera::GetInstance();

		if (InputManager::GetInstance()->MouseClicked(GLFW_MOUSE_BUTTON_3)) {
			return; //If middle mouse is clicked
		}

		glm::vec3 displacement;
		if (yoffset > 0) {
			if (instance->m_CurrentZoomSteps >= instance->m_MaxZoomSteps) {
				return; //Don't zoom if completely zoomed in
			}
			displacement = instance->m_Forward * instance->GetScrollSpeed();
			instance->m_CurrentZoomSteps++;
		}
		else if (yoffset < 0) {
			if (instance->m_CurrentZoomSteps == 0) {
				return; //Don't zoom if completely zoomed out
			}
			displacement = -instance->m_Forward * instance->GetScrollSpeed();
			instance->m_CurrentZoomSteps--;
			if (instance->m_CurrentZoomSteps < 0) {
				instance->m_CurrentZoomSteps = 0;
			}
		}
		else return;

		instance->GetPosition() += displacement;
	}
};