#pragma once
#include <unordered_map>
class GLFWwindow;
class Camera;

typedef void (Camera::* CameraFunction) (void);

class InputHandler
{
private:
	std::unordered_map<int, bool> m_PressedKeys;
	std::unordered_map<int, CameraFunction> m_KeyFunctions;

	GLFWwindow* m_InputWindow;
	static Camera* m_ControllingCamera;

public:
	static InputHandler& GetInstance()
	{
		static InputHandler instance;

		return instance;
	}

private:
	InputHandler(){}

public:
	InputHandler(InputHandler const&) = delete;
	void operator=(InputHandler const&) = delete;

public:
	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);

	void AddInput(int key, CameraFunction callbackFunc);

	void KeyboardMovementInputTick();

	void SetInputWindow(GLFWwindow* window);

	void SetControllingCamera(Camera* controllingCamera);

};