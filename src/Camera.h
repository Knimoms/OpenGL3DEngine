#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	glm::vec3 m_Eye;
	glm::vec3 m_FrontVector;
	glm::vec3 m_UpVector;

	glm::vec2 m_PreviousMousePosition;
	glm::mat4 m_ProjectionMatrix;

	const glm::vec3 cm_WorldUpVector = glm::vec3(0, 1, 0);

	float m_Sensitivity = 0.1f;

	float m_MovementSpeed = 0.05f;

public:
	Camera(float fovDegrees, float clipNear, float clipFar, float screenSizeX, float screenSizeY);

	inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Eye, m_Eye + m_FrontVector, m_UpVector); }
	inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

	void MouseLook(int mouseX, int mouseY);

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void SetPreviousMousePosition(float xMousePos, float yMousePos);
};
