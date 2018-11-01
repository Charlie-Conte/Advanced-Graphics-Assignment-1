#include "Sphere.h"


Sphere::Sphere()
{
	Sphere::position = glm::vec3(0);
	Sphere::radius = 0;
	Sphere::colour = glm::vec3(0);
}

//Sphere example (vector 3(3.0,4.0,10.0), float 3.2, vector 3(0.2,0.0,0.64))
Sphere::Sphere(glm::vec3 position,float radius, glm::vec3 colour)
{
	Sphere::position = position;
	Sphere::radius = radius;
	Sphere::colour = colour;
}


