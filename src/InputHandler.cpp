#include "InputHandler.h"
#include "Camera.h"

#include "GLFW/glfw3.h"

Camera* InputHandler::m_ControllingCamera;

void InputHandler::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	m_ControllingCamera->MouseLook(xpos, ypos);
}

void InputHandler::AddInput(int key, CameraFunction callbackFunc)
{
	m_KeyFunctions[key] = callbackFunc;
}

void InputHandler::KeyboardMovementInputTick()
{
	for (auto [key, value] : m_KeyFunctions)
		if (glfwGetKey(m_InputWindow, key)) 
			(m_ControllingCamera->*value)();
}

void InputHandler::SetInputWindow(GLFWwindow* window)
{
	m_InputWindow = window;
}

void InputHandler::SetControllingCamera(Camera* controllingCamera)
{
	m_ControllingCamera = controllingCamera;
}
