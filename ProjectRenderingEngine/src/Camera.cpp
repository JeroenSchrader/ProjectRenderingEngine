#include "Camera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

float horizontal = 0.0f;
float vertical = 0.0f;

float mouseClickposX;
float mouseClickposY;
bool isMouseDown;

Camera::Camera(InputManager* inputManager, float moveSpeed, float turnSpeed, float FoV, float nearPlane, float farPlane)
	: m_InputManager(inputManager), m_MoveSpeed(moveSpeed), m_TurnSpeed(turnSpeed), m_ViewMatrix(glm::mat4(1.0f)),
		m_ProjectionMatrix(glm::perspective(glm::radians(FoV), (float)1280 / (float)720, nearPlane, farPlane))
{
	double lastTime = 0.0f;	
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (m_InputManager->KeyPressed(GLFW_KEY_W)) {
		//glm::mat4 orientation = glm::mat4(1.0f);
		//orientation = glm::rotate(orientation, glm::radians(horizontal), glm::vec3(1, 0, 0));
		//m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(vertical), glm::vec3(0, 1, 0));
		glm::vec3 forward = m_ViewMatrix * glm::vec4(0, 0, -1, 0);	

		glm::vec3 displacement = forward * m_MoveSpeed;
		m_Position += displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_S)) {
		glm::vec3 forward = m_ViewMatrix * glm::vec4(0, 0, -1, 0);

		glm::vec3 displacement = forward * m_MoveSpeed;
		m_Position -= displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_D)) {
		m_Position.x += m_MoveSpeed;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_A)) {
		m_Position.x -= m_MoveSpeed;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_Y)) {
		m_Position.y += m_MoveSpeed;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_H)) {
		m_Position.y -= m_MoveSpeed;
	}

	glm::vec2 mousePosition = m_InputManager->GetMousePosition();

	if (m_InputManager->MouseClicked(GLFW_MOUSE_BUTTON_LEFT)) {
		if (isMouseDown) {
			horizontal -= m_TurnSpeed * float(mouseClickposY - mousePosition.y);
			vertical -= m_TurnSpeed * float(mouseClickposX - mousePosition.x);

			mouseClickposX = mousePosition.x;
			mouseClickposY = mousePosition.y;
		}
		else {
			mouseClickposX = mousePosition.x;
			mouseClickposY = mousePosition.y;
			isMouseDown = true;
		}
	}

	if (m_InputManager->MouseReleased(GLFW_MOUSE_BUTTON_LEFT)) {
		isMouseDown = false;
	}

	m_ViewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(horizontal), glm::vec3(1, 0, 0));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(vertical), glm::vec3(0, 1, 0));
	m_ViewMatrix = glm::translate(m_ViewMatrix, -m_Position);
}
