#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
//#include "Mesh.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class WorldGeometryObject;

class Mesh;

struct Transform;

class Renderer
{

public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const Camera& camera) const;

	void DrawMesh(const Mesh& mesh, const Shader& shader, const Camera& camera) const;

	void DrawMeshWithTransform(const Mesh& mesh, const Shader& shader, const Camera& camera, const Transform& transform) const;

	void DrawMeshWithTransforms(const Mesh& mesh, const Shader& shader, const Camera& camera, const std::vector<Transform>& transforms) const;

	void Clear() const;

};