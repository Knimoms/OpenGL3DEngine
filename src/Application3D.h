#pragma once

#include <string>

#include "Camera.h"
#include "InputHandler.h"

class Application3D
{
private:
	std::string m_AppName;
	class GLFWwindow* m_Window;
	Camera m_Camera;
	InputHandler* m_InputHandler;

	int m_WindowWidth;
	int m_WindowHeight;

protected:
	int SetupGLFWWindow();

public:
	Application3D(const std::string& appName, int windowPixelWidth, int windowPixelHeight, float cameraFovDegrees, float cameraClipNear, float cameraClipFar);

	void Run();
};