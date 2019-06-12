#pragma once
#include "Object.h"
class Plane :
	public Object
{
public:

	Plane(glm::vec3 position, glm::vec3 normal, Material material);

	
	double intersect(Ray *ray) override;

	glm::vec3 normal(glm::vec3 p0) override;
	glm::vec3 _normal;


};

