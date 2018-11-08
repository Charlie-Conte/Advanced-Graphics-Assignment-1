#include "AreaLight.h"



AreaLight::AreaLight(glm::vec3 position, glm::vec3 intensity,glm::vec3 size):
	LightSource(position,intensity), _size(size)
{
}



