#include "Camera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

float mouseClickposX;
float mouseClickposY;
bool isMouseDown;

Camera::Camera(InputManager* inputManager, float moveSpeed, float turnSpeed, float FoV, float nearPlane, float farPlane)
	: m_InputManager(inputManager), m_MoveSpeed(moveSpeed), m_TurnSpeed(turnSpeed),
		m_ProjectionMatrix(glm::perspective(glm::radians(FoV), (float)1280 / (float)720, nearPlane, farPlane))
{
	double lastTime = 0.0f;	
}

Camera::~Camera()
{
}

const glm::mat4 Camera::GetOrientation()
{
	glm::mat4 orientation = glm::rotate(glm::mat4(1.0f), glm::radians(m_HorizontalAngleInDegrees), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(m_VerticalAngleInDegrees), glm::vec3(0, 1, 0));
	return orientation;
}

void Camera::Update()
{
	if (m_InputManager->KeyPressed(GLFW_KEY_W)) {
		glm::vec3 displacement = Forward() * m_MoveSpeed;
		m_Position += displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_S)) {
		glm::vec3 displacement = Forward() * m_MoveSpeed;
		m_Position -= displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_D)) {
		glm::vec3 displacement = Right() * m_MoveSpeed;
		m_Position += displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_A)) {
		glm::vec3 displacement = Right() * m_MoveSpeed;
		m_Position -= displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_SPACE)) {
		glm::vec3 displacement = Up() * m_MoveSpeed;
		m_Position += displacement;
	}
	if (m_InputManager->KeyPressed(GLFW_KEY_LEFT_CONTROL)) {
		glm::vec3 displacement = Up() * m_MoveSpeed;
		m_Position -= displacement;
	}

	glm::vec2 mousePosition = m_InputManager->GetMousePosition();

	if (m_InputManager->MouseClicked(GLFW_MOUSE_BUTTON_LEFT)) {
		if (isMouseDown) {
			m_HorizontalAngleInDegrees -= m_TurnSpeed * float(mouseClickposY - mousePosition.y);
			m_VerticalAngleInDegrees -= m_TurnSpeed * float(mouseClickposX - mousePosition.x);

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
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::translate(GetOrientation(), -m_Position);
}

glm::vec3 Camera::Up()
{
	return glm::inverse(GetOrientation()) * glm::vec4(0, 1, 0, 1);
}

glm::vec3 Camera::Right()
{
	return glm::inverse(GetOrientation()) * glm::vec4(1, 0, 0, 1);
}

glm::vec3 Camera::Forward()
{
	return glm::inverse(GetOrientation()) * glm::vec4(0, 0, -1, 1);
}
