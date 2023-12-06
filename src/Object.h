#pragma once

#include "glm/glm.hpp"
#include <vector>

#include "Material.h"

struct Transform 
{
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class Object
{
private:
	std::vector<float> m_Vertices;
	Transform m_Transform;

	Material m_Material;

public:
	Object(std::vector<float> vertices, Transform transform = {glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)}, Material material = Material());

};