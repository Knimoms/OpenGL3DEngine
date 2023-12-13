#include "WorldGeometryObject.h"

WorldGeometryObject::WorldGeometryObject()
{
}

void WorldGeometryObject::SetMesh(Mesh* mesh)
{
	m_Mesh = mesh;
}

void WorldGeometryObject::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void WorldGeometryObject::Move(const glm::vec3& offset)
{
	m_Transform.Translation += offset;
}

void WorldGeometryObject::Rotate(const glm::vec3& rotatingDegrees)
{
	m_Transform.Rotation += rotatingDegrees;
}

void WorldGeometryObject::SetScale(const glm::vec3& scale)
{
	m_Transform.Scale = scale;
}
