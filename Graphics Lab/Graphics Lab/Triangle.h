#pragma once
#include "Object.h"
class Triangle :
	public Object
{
public:

	Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, Material material);

	Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 normal0, glm::vec3 normal1, glm::vec3 normal2, Material material);


	//As all objects are made of triangles, this moves all the contained triangles
	static void MoveObject(std::vector<Triangle*> object, glm::vec3 movementVector);

	double intersect(Ray *ray) override;

	glm::vec3 normal(glm::vec3 p0) override;

	glm::vec3 _vert0;
	glm::vec3 _vert1;
	glm::vec3 _vert2;
	glm::vec3 _normal0 = glm::vec3(0);
	glm::vec3 _normal1 = glm::vec3(0);
	glm::vec3 _normal2 = glm::vec3(0);



private:
	float u, v, w;
	glm::vec3 e1, e2;

};

