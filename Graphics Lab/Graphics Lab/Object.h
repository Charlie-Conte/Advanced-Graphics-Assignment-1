#pragma once
#include "MainIncludes.h"
#include "LightMain.h"


class Object
{
public:


	Object(glm::vec3 position, Material material);
	void PrintMatrix();

	static vector<glm::vec3> calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y,Material material, glm::vec3 normal, glm::vec3 rayDirection);


	virtual double intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection);
	virtual glm::vec3 normal(glm::vec3 p0);

	glm::vec3 _position;
	Material _material;


	
};

