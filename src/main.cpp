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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define WIDTH 1080
#define HEIGHT 1080

glm::vec3 camerapos;

float speed = 0.01f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << key << std::endl;

	switch (key)
	{
	case 87: camerapos += glm::vec3(	0.f,	0.f,	-1.f) * speed;
		break;
	case 83: camerapos += glm::vec3(	0.f,	0.f,	1.f) * speed;
		break;
	case 65: camerapos += glm::vec3(	-1.f,	0.f,	0.f) * speed;
		break;
	case 68: camerapos += glm::vec3(	1.f,	0.f,	0.f) * speed;
		break;
	}

	std::cout << camerapos[2] << std::endl;

}

int main(void)
{
	camerapos = glm::vec3(0.f, 0.f, 0.f);

	{
		GLFWwindow* window;
		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(1080, 1080, "Knimoms' 3D Engine", NULL, NULL);

		/* Create a windowed mode window and its OpenGL context */
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);

		glfwSwapInterval(10);

		if (glewInit() != GLEW_OK)
			std::cout << "Ohoh" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;

		float positions[] =
		{
			/*vertices         texturecoords*/
			-0.5f,	-0.5f,  0.f, 0.0f, 0.0f,
			 0.5f,	-0.5f,	0.f, 1.0f, 0.0f,
			 0.5f,	 0.5f,	0.f, 1.0f, 1.0f,
			-0.5f,	 0.5f,	0.f, 0.0f, 1.0f
		};

		unsigned int  indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 5 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		glm::mat4 perspective = glm::perspective(glm::radians(45.f), (float)WIDTH/(float)HEIGHT, 0.1f, 10.f);
		glm::mat4 view = glm::translate(glm::mat4(1.f), camerapos);
		glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
		model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		Texture texture("res/textures/unknown.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);
		shader.SetUniformMat4f("u_Perspective", perspective);
		shader.SetUniformMat4f("u_Model", model);
		shader.SetUniformMat4f("u_View", view);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			shader.Bind();
			glm::mat4 view2 = glm::translate(glm::mat4(1.f), -1.f*camerapos);
			shader.SetUniformMat4f("u_View", view2);

			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}