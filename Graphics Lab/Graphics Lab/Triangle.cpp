#include "Triangle.h"



Triangle::Triangle()
{
	_vert0 = glm::vec3(0, 0, 5);
	_vert1 = glm::vec3(1, 0, 5);
	_vert2 = glm::vec3(1, 1, 5);
	_colour = glm::vec3(0.2, 0.2, 0.8);
}

Triangle::Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 colour)
{
	_vert0 = vert0;
	_vert1 = vert1;
	_vert2 = vert2;
	_colour = colour;
}

void Triangle::renderTriangles(std::list<Triangle> &triangles, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, bool &hasHit)
{
	glm::vec3 tempP0 = glm::vec3(NULL);


	for (Triangle thisTriangle : triangles)
	{

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

			if (glm::length(p0) < glm::length(tempP0))
			{
				tempP0 = p0;

				image[x][y].x = thisTriangle._colour.x;
				image[x][y].y = thisTriangle._colour.y;
				image[x][y].z = thisTriangle._colour.z;
			}
			else if (glm::length(tempP0) == 0)
			{
				tempP0 = p0;

				image[x][y].x = thisTriangle._colour.x;
				image[x][y].y = thisTriangle._colour.y;
				image[x][y].z = thisTriangle._colour.z;
			}
			//TODO normals  here
		}
	}
}
