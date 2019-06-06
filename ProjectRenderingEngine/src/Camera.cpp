#include "Camera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

float mouseClickposX;
float mouseClickposY;
bool isLeftMouseDown;
bool isMiddleMouseDown;

Camera::Camera(InputManager* inputManager, float moveSpeed, float turnSpeed, float FoV, float nearPlane, float farPlane, GLFWwindow* window)
	: m_InputManager(inputManager), m_MoveSpeed(moveSpeed / 10), m_TurnSpeed(turnSpeed / 10),
		m_ProjectionMatrix(glm::perspective(glm::radians(FoV), (float)1280 / (float)720, nearPlane, farPlane)), 
		m_Window(window)
{
	glfwSetScrollCallback(window, scroll_callback);
}

void Camera::Update()
{	
	glm::vec2 mousePosition = m_InputManager->GetMousePosition();

	if (m_InputManager->MouseClicked(GLFW_MOUSE_BUTTON_MIDDLE)) {
		if (isMiddleMouseDown) {
			float deltaY = -float(mouseClickposY - mousePosition.y);
			float deltaX = float(mouseClickposX - mousePosition.x);

			glm::vec3 originToCamera = m_Position - glm::vec3(0.0);
			glm::mat4 rotY = glm::rotate(m_TurnSpeed / 15 * deltaY, m_Right);
			glm::mat4 rotX = glm::rotate(m_TurnSpeed / 15 * deltaX, m_Up);
			originToCamera = rotY * rotX * glm::vec4(originToCamera, 0.0);
			m_Position = originToCamera;
			m_Right = glm::normalize(glm::cross(glm::normalize(originToCamera), glm::vec3(0.0, 1.0, 0.0)));
			m_Up = glm::normalize(-glm::cross(glm::normalize(originToCamera), m_Right));
			m_Forward = glm::normalize(glm::cross(m_Right, m_Up));

			mouseClickposX = mousePosition.x;
			mouseClickposY = mousePosition.y;
		}
		else {
			mouseClickposX = mousePosition.x;
			mouseClickposY = mousePosition.y;
			isMiddleMouseDown = true;
		}
	}

	if (m_InputManager->MouseReleased(GLFW_MOUSE_BUTTON_MIDDLE)) {
		isMiddleMouseDown = false;
	}
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, glm::vec3(0.0, 0.0, 0.0), m_Up);
}

