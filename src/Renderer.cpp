#include "Renderer.h"
#include "Mesh.h"
#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const Camera& camera) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glm::mat4 modelMatrix(1.0);

	shader.SetUniformMat4f("u_Model", modelMatrix);
	shader.SetUniformMat4f("u_Projection", camera.GetProjectionMatrix());
	shader.SetUniformMat4f("u_View", camera.GetViewMatrix());

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader, const Camera& camera) const
{
	mesh.Bind();
	shader.Bind();

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

	glm::mat4 modelMatrix(1.0);

	shader.SetUniformMat4f("u_Model", modelMatrix);
	shader.SetUniformMat4f("u_Projection", camera.GetProjectionMatrix());
	shader.SetUniformMat4f("u_View", camera.GetViewMatrix());


	glDrawElements(GL_TRIANGLES, mesh.m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawMeshWithTransform(const Mesh& mesh, const Shader& shader, const Camera& camera, const Transform& transform) const
{
	mesh.Bind();
	shader.Bind();

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

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), transform.Translation);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.Rotation.x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.Rotation.y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.Rotation.z), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, transform.Scale);

	shader.SetUniformMat4f("u_Model", modelMatrix);
	shader.SetUniformMat4f("u_Projection", camera.GetProjectionMatrix());
	shader.SetUniformMat4f("u_View", camera.GetViewMatrix());


	glDrawElements(GL_TRIANGLES, mesh.m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::DrawMeshWithTransforms(const Mesh& mesh, const Shader& shader, const Camera& camera, const std::vector<Transform>& transforms) const
{
	mesh.Bind();
	shader.Bind();

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

	size_t meshAmount = transforms.size();

	for (int i = 0; i < meshAmount; i++)
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), transforms[i].Translation);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(transforms[i].Rotation.x), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(transforms[i].Rotation.y), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(transforms[i].Rotation.z), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, transforms[i].Scale);

		shader.SetUniformMat4f("u_Model", modelMatrix);
		shader.SetUniformMat4f("u_Projection", camera.GetProjectionMatrix());
		shader.SetUniformMat4f("u_View", camera.GetViewMatrix());


		glDrawElements(GL_TRIANGLES, mesh.m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
