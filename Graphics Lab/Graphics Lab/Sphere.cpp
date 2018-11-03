#include "Sphere.h"


Sphere::Sphere()
{
	_position = glm::vec3(0);
	_radius = 1;
	_colour = glm::vec3(0);
}

//Sphere example (vector 3(3.0,4.0,10.0), float 3.2, vector 3(0.2,0.0,0.64))
Sphere::Sphere(glm::vec3 position,float radius, glm::vec3 colour)
{
	_position = position;
	_radius = radius;
	_colour = colour;
}



void Sphere::renderSpheres(std::list<Sphere> &spheres, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y,bool &hasHit)
{
	glm::vec3 tempP0 = glm::vec3(NULL);
	glm::vec3 tempP1 = glm::vec3(NULL);



	for (Sphere ball : spheres)
	{
		glm::vec3 l = ball._position - rayOrigin;
		double tCA = glm::dot(l, rayDirection);
		double s = glm::sqrt(glm::dot(l, l) - glm::pow(tCA, 2));
		double tHC = glm::sqrt(glm::pow(ball._radius, 2) - s);

		if (tCA < 0);//no hit
		else if (s > ball._radius)//no hit
		{
			if (hasHit==false)
				image[x][y] = glm::vec3(1);
		}
		else
		{
			hasHit = true;

			double t0 = tCA - tHC;
			double t1 = tCA + tHC;

			glm::vec3 p0 = rayOrigin + (float)t0 * rayDirection;
			glm::vec3 p1 = rayOrigin + (float)t1 * rayDirection;


			if (glm::length(p0) < glm::length(tempP0))
			{
				tempP0 = p0;
				tempP1 = p1;
				image[x][y].x = ball._colour.x;
				image[x][y].y = ball._colour.y;
				image[x][y].z = ball._colour.z;
			}
			else if (glm::length(tempP0) == 0 && glm::length(tempP1) == 0)
			{
				tempP0 = p0;
				tempP1 = p1;
				image[x][y].x = ball._colour.x;
				image[x][y].y = ball._colour.y;
				image[x][y].z = ball._colour.z;
			}



			//TODO normals  here

		}
	}
}