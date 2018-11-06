#pragma once
#include "Object.h"
class Plane :
	public Object
{
public:
	//Plane();
	Plane(glm::vec3 position, glm::vec3 normal, Material material);

	/*static void renderPlanes(std::list<Plane> &planes, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, glm::vec3 &tempP0, glm::vec3 &tempP0Shadow);*/

	double intersect(Ray *ray) override;

	glm::vec3 normal(glm::vec3 p0) override;
	glm::vec3 _normal;


};

