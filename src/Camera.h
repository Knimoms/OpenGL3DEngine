#pragma once

#include "glm/glm.hpp"

class Camera
{
private:
	glm::vec3 m_Eye;
	glm::vec3 m_Normal;
	glm::vec3 m_UpVector;

	glm::vec2 m_PreviousMousePosition;

	glm::mat4 m_ProjectionMatrix;

	float m_Sensitivity;

public:
	Camera(float fovDegrees, float clipNear, float clipFar, float screenSizeX, float screenSizeY);

	glm::mat4 GetViewMatrix() const;
	inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

	void MouseLook(int mouseX, int mouseY);

	void MoveForward(float speed);
	void MoveBackward(float speed);
	void MoveLeft(float speed);
	void MoveRight(float speed);
	void MoveUp(float speed);
	void MoveDown(float speed);

	void SetPreviousMousePosition(float xMousePos, float yMousePos);
};
