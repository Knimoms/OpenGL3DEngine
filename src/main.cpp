#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Windows.h"

#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define WIDTH 1920
#define HEIGHT 1080

Camera g_Camera(45.f, 0.1f, 100.f, WIDTH, HEIGHT);

float speed = 0.01f;

std::unordered_map<int, bool> g_PressedKeys;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	g_Camera.MouseLook(xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	g_PressedKeys[key] = action;
}

void KeyboardInputHandler()
{
	if (g_PressedKeys[87])
		g_Camera.MoveForward(speed);

	if (g_PressedKeys[83])
		g_Camera.MoveBackward(speed);

	if (g_PressedKeys[68])
		g_Camera.MoveRight(speed);

	if (g_PressedKeys[65])
		g_Camera.MoveLeft(speed);

	if (g_PressedKeys[32])
		g_Camera.MoveUp(speed);

	if (g_PressedKeys[341])
		g_Camera.MoveDown(speed);

}

GLFWwindow* SetupGLFWWindow()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Knimoms' 3D Engine", NULL, NULL);

	/* Create a windowed mode window and its OpenGL context */
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	g_Camera.SetPreviousMousePosition(xpos, ypos);

	glEnable(GL_DEPTH_TEST);

	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
		std::cout << "Ohoh" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	return window;
}

int main(void)
{
	{
		GLFWwindow* window = SetupGLFWWindow();

		if (!window)
			return -1;

		std::vector<Vertex> positions =
		{
			/*vertices         texturecoords*/
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)},
											   													   
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)},
																								   
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)},
																								   
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)},

			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)},

			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)}

		};

		std::vector<unsigned int>  indices =
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};

		glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -2.f));
		glm::mat4 view = g_Camera.GetViewMatrix();
		glm::mat4 projection = g_Camera.GetProjectionMatrix();

		//model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		Texture textures[]
		{
			Texture("res/textures/unknown.png", "diffuse")
		};
		
		std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

		Mesh weirdBox(positions, indices, tex);

		shader.SetUniformMat4f("u_Projection", projection);
		shader.SetUniformMat4f("u_Model", model);
		shader.SetUniformMat4f("u_View", view);


		Renderer renderer;

		/* Loop until the user closes the window */

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.2, 0.2, 0.2, 1.0);

			KeyboardInputHandler();
			renderer.Clear();
			
			renderer.DrawMesh(weirdBox, shader, g_Camera);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}