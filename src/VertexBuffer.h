#pragma once

#include "glm/glm.hpp"
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texUV;

};

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(std::vector<Vertex>& vertices);
	~VertexBuffer();

	void Bind() const;
	static void Unbind();
};