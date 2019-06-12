#pragma once
#include "MainIncludes.h"

class Object;


class Ray
{
public:
	Ray();
	Ray(glm::vec3 direction, glm::vec3 origin);

	void RayCast(double & closestDistance, Object *& closestObject);

	glm::vec3 _direction;
	glm::vec3 _origin;
};

