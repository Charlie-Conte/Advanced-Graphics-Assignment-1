#include "Plane.h"



Plane::Plane()
{
	_position = glm::vec3(0);
	_normal = glm::vec3(0,1,0);
	_material = Material(glm::vec3(0.5f,0,0.5f),glm::vec3(0.7f),64);
}

Plane::Plane(glm::vec3 position, glm::vec3 normal, Material material)
{
	_position = position;
	_normal = normal;
	_material = material;
}


void Plane::renderPlanes(std::list<Plane> &planes, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, bool &hasHit, glm::vec3 &tempP0)
{

	for (Plane thisPlane : planes)
	{

		float denominator = glm::dot(thisPlane._normal, rayDirection);
			if (denominator > 1e-6)
			{
				glm::vec3 rayOriginMinusPlaneOrigin =  thisPlane._position - rayOrigin;
				float t = glm::dot(rayOriginMinusPlaneOrigin, thisPlane._normal) / denominator;
				//std::cout << thisPlane._normal.x << "," << thisPlane._normal.y << "," << thisPlane._normal.z << "\n";
				if (t >= 0)
				{
					hasHit = true;

					glm::vec3 p0 = rayOrigin + t * rayDirection;

					if (glm::length(p0) < glm::length(tempP0))
					{
						tempP0 = p0;

						calculateColour(p0, image, x, y, thisPlane._material, thisPlane._normal * -1.0f, rayDirection);
					}
				}
			}
		
	}
}


