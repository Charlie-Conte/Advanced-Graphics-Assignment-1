#pragma once
#include "Object.h"
class Sphere :
	public Object
{
public:
	Sphere();
	Sphere(glm::vec3 position, float radius, glm::vec3 colour);


	glm::vec3 position;
	glm::vec3 colour;
	float radius;


};

