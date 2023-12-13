#pragma once
#include "glm/glm.hpp"
#include "Mesh.h"

struct Transform
{
	glm::vec3 Translation = { 0.f, 0.f, 0.f };
	glm::vec3 Rotation = { 0.f, 0.f, 0.f };;
	glm::vec3 Scale = { 1.f, 1.f, 1.f };;
};

class WorldGeometryObject
{
private:
	Mesh* m_Mesh;
	Transform m_Transform;

public:
	WorldGeometryObject();

	inline Mesh* GetMesh() const { return m_Mesh; }
	void SetMesh(Mesh* mesh);

	inline const Transform& GetTransform() const { return m_Transform; }
	void SetTransform(const Transform& transform);

	void Move(const glm::vec3& offset);

	void Rotate(const glm::vec3& rotatingDegrees);

	void SetScale(const glm::vec3& scale);
	
};