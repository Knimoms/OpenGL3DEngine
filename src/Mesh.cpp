#include "Mesh.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector <Texture>& textures)
	:m_Vertices(vertices), m_Indices(indices), m_Textures(textures), m_IndexBuffer(IndexBuffer(indices)), m_VertexBuffer(vertices)
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);

	m_VertexArray.AddBuffer(m_VertexBuffer, layout);
}

