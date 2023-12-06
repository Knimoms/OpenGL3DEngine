#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(float fovDegrees, float clipNear, float clipFar, float screenSizeX, float screenSizeY)
	:m_Eye(glm::vec3(0.f, 0.f, 3.f)), m_Normal(glm::vec3(0.f, 0.f, -1.f)), m_UpVector(glm::vec3(0.f, 1.f, 0.f)), m_Sensitivity(0.1f), m_PreviousMousePosition(glm::vec3())
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fovDegrees), screenSizeX / screenSizeY, clipNear, clipFar);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_Eye, m_Eye + m_Normal, m_UpVector);
}

void Camera::MouseLook(int mouseX, int mouseY)
{
	
	glm::vec2 currentMousePosition = glm::vec2(mouseX, mouseY);
	glm::vec2 deltaMousePosition = m_PreviousMousePosition - currentMousePosition;

	glm::vec3 rightVector = glm::normalize(glm::cross(m_Normal, glm::vec3(0.f, 1.f, 0.f)));

	rightVector = glm::normalize(rightVector);
	m_Normal = glm::rotate(m_Normal, glm::radians(deltaMousePosition[1] * m_Sensitivity), rightVector);
	m_UpVector = glm::cross(rightVector, m_Normal);

	m_Normal = glm::rotate(m_Normal, glm::radians(deltaMousePosition[0] * m_Sensitivity), glm::vec3(0.f, 1.f, 0.f));

	m_PreviousMousePosition = currentMousePosition;

}

void Camera::MoveForward(float speed)
{
	glm::vec3 walkDirection = m_Normal;
	walkDirection.y = 0;

	walkDirection = glm::normalize(walkDirection);

	m_Eye += walkDirection * speed;

}

void Camera::MoveBackward(float speed)
{
	glm::vec3 walkDirection = m_Normal;
	walkDirection.y = 0;

	walkDirection = glm::normalize(walkDirection);

	m_Eye -= walkDirection * speed;
}

void Camera::MoveLeft(float speed)
{
	glm::vec3 rightVector = glm::cross(m_Normal, m_UpVector);
	m_Eye -= rightVector * speed;
}

void Camera::MoveRight(float speed)
{
	glm::vec3 rightVector = glm::cross(m_Normal, m_UpVector);
	m_Eye += rightVector * speed;
}

void Camera::MoveUp(float speed)
{
	m_Eye += glm::vec3(0.f, 1.f, 0.f) * speed;
}

void Camera::MoveDown(float speed)
{
	m_Eye -= glm::vec3(0.f, 1.f, 0.f) * speed;
}

void Camera::SetPreviousMousePosition(float xMousePos, float yMousePos)
{
	m_PreviousMousePosition[0] = xMousePos;
	m_PreviousMousePosition[1] = yMousePos;
}
