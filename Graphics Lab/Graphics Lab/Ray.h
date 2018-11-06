#pragma once
#include "MainIncludes.h"
class Ray
{
public:
	Ray();
	Ray(glm::vec3 direction, glm::vec3 origin);

	glm::vec3 _direction;
	glm::vec3 _origin;
};

