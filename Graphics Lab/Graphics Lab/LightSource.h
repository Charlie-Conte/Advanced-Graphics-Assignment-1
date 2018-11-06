#pragma once
#include "MainIncludes.h"
#include "Material.h"

class LightSource 
{
public:
	LightSource(glm::vec3 position, glm::vec3 intensity);

	glm::vec3 _intensity;
	glm::vec3 _position;

};

