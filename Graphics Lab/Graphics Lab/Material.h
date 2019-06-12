#pragma once
#include "MainIncludes.h"
class Material
{
public:
	glm::vec3 _diffuseColour;
	glm::vec3 _specularColour;
	float _shinyness;

	Material(glm::vec3 diffuseColour, glm::vec3 specularColour, float shininess);
	Material();

};

