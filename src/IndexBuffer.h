#pragma once

#include <vector>

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer(std::vector<unsigned int>& indices);
	~IndexBuffer();

	void Bind() const;
	static void Unbind();

	inline unsigned int GetCount() const { return m_Count; }
};