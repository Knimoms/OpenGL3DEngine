#include "Mesh.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector <Texture>& textures)
	:m_Vertices(vertices), m_Indices(indices), m_Textures(textures), m_IndexBuffer(IndexBuffer(indices)), m_VertexBuffer(vertices)
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	m_VertexArray.AddBuffer(m_VertexBuffer, layout);
}

void Mesh::Bind() const
{
	m_VertexArray.Bind();
	m_IndexBuffer.Bind();
}

void Mesh::Unbind()
{
	VertexArray::Unbind();
	IndexBuffer::Unbind();
}