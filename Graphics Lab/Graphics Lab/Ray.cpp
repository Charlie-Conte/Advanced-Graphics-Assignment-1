#include "Ray.h"



Ray::Ray()
{
}

Ray::Ray(glm::vec3 direction, glm::vec3 origin) :
	_direction(direction) , _origin(origin)
{
}



