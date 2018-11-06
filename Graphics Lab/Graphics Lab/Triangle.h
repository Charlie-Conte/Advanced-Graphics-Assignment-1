#pragma once
#include "Object.h"
class Triangle :
	public Object
{
public:
	Triangle();
	Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 colour);

	Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 normal, glm::vec3 colour);



	static void MoveObject(std::list<Triangle>& object, glm::vec3 movementVector);

	static void renderTriangles(std::list<Triangle>& triangles, glm::vec3 & rayOrigin, glm::vec3 & rayDirection, glm::vec3 ** image, int x, int y, bool & hasHit, glm::vec3 &tempP0);

	
	glm::vec3 _vert0;
	glm::vec3 _vert1;
	glm::vec3 _vert2;
	glm::vec3 _normal = glm::vec3(0);
	glm::vec3 _colour;


private:
	float u, v, w;
	glm::vec3 e1, e2;

};

