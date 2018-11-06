#include "Ray.h"
#include "Object.h"


Ray::Ray()
{
}

Ray::Ray(glm::vec3 direction, glm::vec3 origin) :
	_direction(direction) , _origin(origin)
{
}

void Ray::RayCast(double & closestDistance, Object *& closestObject)
{
	for (Object *thisObject : Object::objectList)
	{
		double tempDistance = thisObject->intersect(this);
		if (tempDistance > 0 && tempDistance < closestDistance)
		{
			closestObject = thisObject;
			closestDistance = tempDistance;
		}
	}
}





