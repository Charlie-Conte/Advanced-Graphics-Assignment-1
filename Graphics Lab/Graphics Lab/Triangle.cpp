#include "Triangle.h"



Triangle::Triangle()
{
	_vert0 = glm::vec3(0, 0, 5);
	_vert1 = glm::vec3(1, 0, 5);
	_vert2 = glm::vec3(1, 1, 5);
	_material = Material(glm::vec3(0.5f, 0, 0.5f), glm::vec3(0.7f), 64);
}

Triangle::Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, Material material)
{
	_vert0 = vert0;
	_vert1 = vert1;
	_vert2 = vert2;
	_material = material;
}
Triangle::Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 normal, Material material)
{
	_vert0 = vert0;
	_vert1 = vert1;
	_vert2 = vert2;
	_normal = normal;
	_material = material;
}


void Triangle::MoveObject(std::list<Triangle> &object,glm::vec3 movementVector)
{
	for (Triangle &tri : object)
	{
		//std::cout << tri._vert0.z << std::endl;
		tri._vert0 += movementVector;
		//std::cout << tri._vert0.z << std::endl;
		tri._vert1 += movementVector;
		tri._vert2 += movementVector;
	}
	//std::cout << "\n\n\n"<< std::endl;
}

void Triangle::renderTriangles(std::list<Triangle> &triangles, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, bool &hasHit, glm::vec3 &tempP0)
{

	for (Triangle thisTriangle : triangles)
	{
		//std::cout << thisTriangle._vert0.z << std::endl;
		thisTriangle.e1 = thisTriangle._vert1 - thisTriangle._vert0;
		thisTriangle.e2 = thisTriangle._vert2 - thisTriangle._vert0;
		glm::vec3 oA = (rayOrigin - thisTriangle._vert0);
		glm::vec3 dE2 = glm::cross(rayDirection , thisTriangle.e2);

		thisTriangle.u = glm::dot(oA, dE2) / glm::dot(thisTriangle.e1, dE2);

		thisTriangle.v = glm::dot(rayDirection, glm::cross((oA),thisTriangle.e1)) / glm::dot(thisTriangle.e1,dE2);

		thisTriangle.w = 1 - thisTriangle.u - thisTriangle.v;

		float t = glm::dot(thisTriangle.e2, glm::cross(oA , thisTriangle.e1)) / glm::dot(thisTriangle.e1, dE2);





		if (thisTriangle.u < 0 || thisTriangle.u > 1);

		else if (thisTriangle.v < 0 || thisTriangle.u + thisTriangle.v > 1);

		else
		{

			hasHit = true;

			glm::vec3 p0 = rayOrigin + (float)t * rayDirection;


			if (thisTriangle._normal == glm::vec3(0))
			{

				thisTriangle._normal.x = (thisTriangle.e1.y * thisTriangle.e2.z) - (thisTriangle.e1.z * thisTriangle.e2.y);
				thisTriangle._normal.y = (thisTriangle.e1.z * thisTriangle.e2.x) - (thisTriangle.e1.x * thisTriangle.e2.z);
				thisTriangle._normal.z = (thisTriangle.e1.x * thisTriangle.e2.y) - (thisTriangle.e1.y * thisTriangle.e2.x);
				thisTriangle._normal = glm::normalize(thisTriangle._normal);
				//std::cout << glm::length(thisTriangle._normal) << std::endl;
			}

			//std::cout << thisTriangle._normal.x<<"\t,\t" << thisTriangle._normal.y<<"\t,\t" << thisTriangle._normal.z << std::endl;
			if (glm::length(p0) < glm::length(tempP0))
			{
				tempP0 = p0;

				calculateColour( p0, image, x, y, thisTriangle._material, thisTriangle._normal, rayDirection);
			}
			else if (glm::length(tempP0) == 0)
			{
				tempP0 = p0;

				calculateColour( p0, image, x, y, thisTriangle._material, thisTriangle._normal, rayDirection);
			}

		}
	}
}
