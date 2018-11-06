#pragma once
#include "Object.h"

class Sphere :
	public Object
{
public:
	Sphere();
	Sphere(glm::vec3 position, float radius, Material material);
	static void renderSpheres(std::list<Sphere> &spheres, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, bool &hasHit, glm::vec3 &tempP0, glm::vec3 &tempP1);



	

	glm::vec3 _position;
	Material _material;
	float _radius;



};

