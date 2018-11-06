#include "Triangle.h"



//Triangle::Triangle()
//{
//	_vert0 = glm::vec3(0, 0, 5);
//	_vert1 = glm::vec3(1, 0, 5);
//	_vert2 = glm::vec3(1, 1, 5);
//	_material = Material(glm::vec3(0.5f, 0, 0.5f), glm::vec3(0.7f), 64);
//}

Triangle::Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, Material material) :
	Object(glm::vec3(0), material), _vert0(vert0), _vert1(vert1), _vert2(vert2)
{
}
Triangle::Triangle(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 normal0, glm::vec3 normal1, glm::vec3 normal2, Material material) :
	Object(glm::vec3(0), material), _vert0(vert0), _vert1(vert1), _vert2(vert2), _normal0(normal0), _normal1(normal1), _normal2(normal2)
{
}


void Triangle::MoveObject(std::vector<Triangle*> object, glm::vec3 movementVector)
{
	for (Triangle *tri : object)
	{
		//std::cout << tri._vert0.z << std::endl;
		tri->_vert0 += movementVector;
		//std::cout << tri._vert0.z << std::endl;
		tri->_vert1 += movementVector;
		tri->_vert2 += movementVector;
	}
	//std::cout << "\n\n\n"<< std::endl;
}

//void Triangle::renderTriangles(std::list<Triangle> &triangles, glm::vec3 &rayOrigin, glm::vec3 &rayDirection, glm::vec3 ** image, int x, int y, glm::vec3 &tempP0, glm::vec3 &tempP0Shadow)
//{
//
//	for (Triangle thisTriangle : triangles)
//	{
//		double t = thisTriangle.intersect(rayOrigin, rayDirection);
//
//		if (t != 0)
//		{
//			
//
//			glm::vec3 p0 = rayOrigin + (float)t * rayDirection;
//
//
//			if (thisTriangle._normal0 == glm::vec3(0) && thisTriangle._normal1 == glm::vec3(0)&& thisTriangle._normal2 == glm::vec3(0))
//			{
//				glm::vec3 flatFaceNormal;
//				flatFaceNormal.x = (thisTriangle.e1.y * thisTriangle.e2.z) - (thisTriangle.e1.z * thisTriangle.e2.y);
//				flatFaceNormal.y = (thisTriangle.e1.z * thisTriangle.e2.x) - (thisTriangle.e1.x * thisTriangle.e2.z);
//				flatFaceNormal.z = (thisTriangle.e1.x * thisTriangle.e2.y) - (thisTriangle.e1.y * thisTriangle.e2.x);
//				thisTriangle._normal0 = glm::normalize(flatFaceNormal);
//				thisTriangle._normal1 = glm::normalize(flatFaceNormal);
//				thisTriangle._normal2 = glm::normalize(flatFaceNormal);
//				//std::cout << glm::length(thisTriangle._normal) << std::endl;
//			}

//
//		}
//	}
//}

double Triangle::intersect(Ray *ray)
{

	//std::cout << thisTriangle._vert0.z << std::endl;
	e1 = _vert1 - _vert0;
	e2 = _vert2 - _vert0;
	glm::vec3 oA = (ray->_origin - _vert0);
	glm::vec3 dE2 = glm::cross(ray->_direction, e2);

	u = glm::dot(oA, dE2) / glm::dot(e1, dE2);

	v = glm::dot(ray->_direction, glm::cross((oA), e1)) / glm::dot(e1, dE2);

	w = 1 - u - v;
	float t = glm::dot(e2, glm::cross(oA, e1)) / glm::dot(e1, dE2);

	if (u < 0 || u > 1)return 0;

	else if (v < 0 || u + v > 1)return 0;

	else
	{

		return t;
	}
}

glm::vec3 Triangle::normal(glm::vec3 p0)
{
	if (_normal0 == glm::vec3(0) && _normal1 == glm::vec3(0) && _normal2 == glm::vec3(0))
	{
		glm::vec3 flatFaceNormal;
		flatFaceNormal.x = (e1.y * e2.z) - (e1.z * e2.y);
		flatFaceNormal.y = (e1.z * e2.x) - (e1.x * e2.z);
		flatFaceNormal.z = (e1.x * e2.y) - (e1.y * e2.x);
		_normal0 = glm::normalize(flatFaceNormal);
		_normal1 = glm::normalize(flatFaceNormal);
		_normal2 = glm::normalize(flatFaceNormal);
		//std::cout << glm::length(thisTriangle._normal) << std::endl;
	}

	glm::vec3 faceNormal = glm::normalize((w * _normal0) + (u * _normal1) + (v * _normal2));


	return faceNormal;
}
