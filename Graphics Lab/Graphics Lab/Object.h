#pragma once
#include "MainIncludes.h"
#include "LightMain.h"

class Object
{
public:

	Object();
	Object(glm::vec3 position);
	void PrintMatrix();

	static void calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y, glm::vec3 colour, glm::vec3 normal, glm::vec3 rayDirection);




	glm::vec3 _position;


	
};

