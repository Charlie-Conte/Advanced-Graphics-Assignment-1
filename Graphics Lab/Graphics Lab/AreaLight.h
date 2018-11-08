#pragma once
#include "LightSource.h"
class AreaLight :
	public LightSource
{
public:
	AreaLight(glm::vec3 position, glm::vec3 intensity, glm::vec3 size);

	glm::vec3 _size;

};

