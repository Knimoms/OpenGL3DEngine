#include "Application3D.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

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

#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Application3D::Application3D(const std::string& appName, int windowPixelWidth, int windowPixelHeight, float cameraFovDegrees, float cameraClipNear, float cameraClipFar)
	:m_AppName(appName), m_Camera(cameraFovDegrees, cameraClipNear, cameraClipFar, windowPixelWidth, windowPixelHeight), m_InputHandler(&InputHandler::GetInstance()),
	 m_WindowWidth(windowPixelWidth), m_WindowHeight(windowPixelHeight)
{
	m_InputHandler->AddInput(87, &Camera::MoveForward);
	m_InputHandler->AddInput(83, &Camera::MoveBackward);
	m_InputHandler->AddInput(68, &Camera::MoveRight);
	m_InputHandler->AddInput(65, &Camera::MoveLeft);
	m_InputHandler->AddInput(32, &Camera::MoveUp);
	m_InputHandler->AddInput(341, &Camera::MoveDown);

	m_InputHandler->SetControllingCamera(&m_Camera);
}

void Application3D::Run()
{
	{
		SetupGLFWWindow();

		m_InputHandler->SetInputWindow(m_Window);

		glfwSetCursorPosCallback(m_Window, InputHandler::MousePositionCallback);


		if (!m_Window)
			return;

		std::vector<Vertex> grassBlockVertices =
		{
						/*position						normal					color					texturecoords*/
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.f, 0.f,  1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.f, 0.f,  1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.f, 0.f,  1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)},
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.f, 0.f,  1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.5f, 0.f)},
													    
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.f, 0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.f, 0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.f, 0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)},
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.f, 0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.5f, 0.f)},
													    
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.f, 0.f, -1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.f, 0.f, -1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.f, 0.f, -1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)},
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.f, 0.f, -1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.5f, 0.f)},

			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)},
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.5f, 0.f)},

			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.0f, 0.f)},
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.f)},
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f, 0.5f, 0.f)},
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)},

			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.5f, 0.f)},
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)},
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5f, 1.0f, 0.f)},
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.f)}
		};

		std::vector<unsigned int> grassBlockIndices =
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

			20, 23, 22,
			22, 21, 20
		};


		Shader shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
		//shader.Bind();

		Texture textures[]
		{
			Texture("res/textures/grass.png", "diffuse")
		};

		std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

		Mesh grassBlockMesh(grassBlockVertices, grassBlockIndices, tex);

		std::vector<Vertex> floorVertices =
		{
			{glm::vec3(-20.f, 0.f,  20.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)},
			{glm::vec3( 20.f, 0.f,  20.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)},
			{glm::vec3( 20.f, 0.f, -20.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 0.f)},
			{glm::vec3(-20.f, 0.f, -20.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)},
		};

		std::vector<unsigned int> floorIndices =
		{
			0, 1, 2,
			2, 3, 0
		};

		Texture floorTextures[]
		{
			Texture("res/textures/cowinpool.jpg", "diffuse")
		};

		Transform floorTransform;

		std::vector<Texture>fT (floorTextures, floorTextures + sizeof(floorTextures) / sizeof(Texture));

		Mesh FloorMesh(floorVertices, floorIndices, fT);

		Renderer renderer;

		glm::vec3 backgroundColor = glm::vec3((float)113 / 255, (float)188 / 255, (float)225 / 255);

		/* Loop until the user closes the window */

		std::vector<Transform> GrassBlockTransforms;

		int squarePlaneSize = 16;

		for (int i = 0; i < squarePlaneSize; i++)
			for (int j = 0; j < squarePlaneSize; j++)
				GrassBlockTransforms.push_back({ glm::vec3(-squarePlaneSize / 2 + i, 0, -squarePlaneSize / 2 + j) ,glm::vec3(0, 0, 0) ,glm::vec3(1, 1, 1) });

		while (!glfwWindowShouldClose(m_Window))
		{
			glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0);

			m_InputHandler->KeyboardMovementInputTick();
			renderer.Clear();

			//renderer.DrawMeshWithTransforms(grassBlockMesh, shader, m_Camera, GrassBlockTransforms);

			renderer.DrawMeshWithTransform(grassBlockMesh, shader, m_Camera, { glm::vec3(0, 2, -3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
			//renderer.DrawMeshWithTransform(FloorMesh, shader, m_Camera, floorTransform);

			/* Swap front and back buffers */
			glfwSwapBuffers(m_Window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
}

int Application3D::SetupGLFWWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

	m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_AppName.c_str(), NULL, NULL);

	/* Create a windowed mode window and its OpenGL context */
	if (!m_Window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);

	m_Camera.SetPreviousMousePosition(xpos, ypos);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Ohoh" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}