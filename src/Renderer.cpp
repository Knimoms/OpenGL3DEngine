#include "Renderer.h"
#include "Mesh.h"
#include <iostream>

void GLClearError()
{
	while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line)
{
	if (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const Camera& camera) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	shader.SetUniformMat4f("u_Projection", camera.GetProjectionMatrix());
	shader.SetUniformMat4f("u_View", camera.GetViewMatrix());

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader, const Camera& camera) const
{
	mesh.m_VertexArray.Bind();
	mesh.m_IndexBuffer.Bind();
	shader.Bind();

	shader.SetUniformMat4f("u_Projection", camera.GetProjectionMatrix());
	shader.SetUniformMat4f("u_View", camera.GetViewMatrix());

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	
	for (unsigned int i = 0; i < mesh.m_Textures.size(); i++)
	{
		std::string num;
		std::string type = mesh.m_Textures[i].GetType();
	
		if (type == "diffuse")
			num = std::to_string(numDiffuse++);
		else if (type == "specular")
			num = std::to_string(numSpecular++);
	
		shader.SetUniform1i((type + num).c_str(), i);
		mesh.m_Textures[0].Bind(i);
	}

	GLCall(glDrawElements(GL_TRIANGLES, mesh.m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
