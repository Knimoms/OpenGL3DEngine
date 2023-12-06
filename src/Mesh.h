#pragma once

#include <vector>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

	IndexBuffer m_IndexBuffer;
	VertexBuffer m_VertexBuffer;

	VertexArray m_VertexArray;

	friend class Renderer;

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector <Texture>& textures);
};