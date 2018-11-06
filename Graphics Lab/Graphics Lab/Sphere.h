#pragma once
#include "Object.h"

class Sphere :
	public Object
{
public:

	Sphere(glm::vec3 position, float radius, Material material);
	

	double intersect(Ray *ray) override;


	/*glm::vec3 sphereShadowsAndReflection(vector<glm::vec3> listOfShadowRays, glm::vec3 ** image, int x, int y, glm::vec3 p0);*/
	

	glm::vec3 normal(glm::vec3 p0) override;

	float _radius;



};

