#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <list>
class Object
{
public:

	Object();
	Object(glm::vec3 position);
	void PrintMatrix();

	glm::vec3 _position;

	
};

