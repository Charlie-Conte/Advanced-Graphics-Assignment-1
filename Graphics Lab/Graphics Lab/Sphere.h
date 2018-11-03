#pragma once
#include "Object.h"

class Sphere :
	public Object
{
public:
	Sphere();
	Sphere(glm::vec3 position, float radius, glm::vec3 colour);
	static void renderSpheres(std::list<Sphere> &spheres, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, bool &hasHit);

	glm::vec3 _position;
	glm::vec3 _colour;
	float _radius;


};

