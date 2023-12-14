#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/euler_angles.hpp"

Camera::Camera(float fovDegrees, float clipNear, float clipFar, float screenSizeX, float screenSizeY)
	:m_Eye(glm::vec3(0.f, 1.7f, 0.f)), m_FrontVector(glm::vec3(0.f, 0.f, -1.f)), m_UpVector(glm::vec3(0.f, 1.f, 0.f)), m_PreviousMousePosition(glm::vec3())
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fovDegrees), screenSizeX / screenSizeY, clipNear, clipFar);
}

void Camera::MouseLook(int mouseX, int mouseY)
{
	glm::vec2 currentMousePosition = glm::vec2(mouseX, mouseY);
	glm::vec2 deltaMousePosition = m_PreviousMousePosition - currentMousePosition;

	m_PreviousMousePosition = currentMousePosition;

	m_FrontVector = glm::rotate(m_FrontVector, glm::radians(deltaMousePosition[0] * m_Sensitivity), cm_WorldUpVector);

	glm::vec3 rightVector = glm::normalize(glm::cross(m_FrontVector, glm::vec3(0.f, 1.f, 0.f)));

	rightVector = glm::normalize(rightVector);
	glm::vec3 newFrontVector = glm::rotate(m_FrontVector, glm::radians(deltaMousePosition[1] * m_Sensitivity), rightVector);

	if (glm::dot(newFrontVector, glm::cross(cm_WorldUpVector, rightVector)) > 0.005f)
		m_FrontVector = newFrontVector;

	m_UpVector = glm::cross(rightVector, m_FrontVector);
}

void Camera::MoveForward()
{
	glm::vec3 walkDirection = m_FrontVector;
	walkDirection.y = 0;

	walkDirection = glm::normalize(walkDirection);

	m_Eye += walkDirection * m_MovementSpeed;
}

void Camera::MoveBackward()
{
	glm::vec3 walkDirection = m_FrontVector;
	walkDirection.y = 0;

	walkDirection = glm::normalize(walkDirection);

	m_Eye -= walkDirection * m_MovementSpeed;
}

void Camera::MoveLeft()
{
	glm::vec3 rightVector = glm::cross(m_FrontVector, m_UpVector);
	m_Eye -= rightVector * m_MovementSpeed;
}

void Camera::MoveRight()
{
	glm::vec3 rightVector = glm::cross(m_FrontVector, m_UpVector);
	m_Eye += rightVector * m_MovementSpeed;
}

void Camera::MoveUp()
{
	m_Eye += glm::vec3(0.f, 1.f, 0.f) * m_MovementSpeed;
}

void Camera::MoveDown()
{
	m_Eye -= glm::vec3(0.f, 1.f, 0.f) * m_MovementSpeed;
}

void Camera::SetPreviousMousePosition(float xMousePos, float yMousePos)
{
	m_PreviousMousePosition[0] = xMousePos;
	m_PreviousMousePosition[1] = yMousePos;
}
