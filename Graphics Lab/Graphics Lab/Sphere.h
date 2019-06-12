#pragma once
#include "Object.h"

class Sphere :
	public Object
{
public:

	double intersect(Ray *ray) override;
	glm::vec3 normal(glm::vec3 p0) override;
	float _radius;


	Sphere(glm::vec3 position, float radius, Material material);

};

