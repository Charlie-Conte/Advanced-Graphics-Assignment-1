#pragma once
#include "Object.h"
class Plane :
	public Object
{
public:
	Plane();
	Plane(glm::vec3 position, glm::vec3 normal, Material material);

	static void renderPlanes(std::list<Plane> &planes, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, bool &hasHit, glm::vec3 &tempP0);

	

	glm::vec3 _position;
	glm::vec3 _normal;
	Material _material;

};

