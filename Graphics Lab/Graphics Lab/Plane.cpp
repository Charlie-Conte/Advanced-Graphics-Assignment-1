#include "Plane.h"




Plane::Plane(glm::vec3 position, glm::vec3 normal, Material material):
	Object(position,material),_normal(normal)
{
}




double Plane::intersect(Ray *ray)
{
	float denominator = glm::dot(_normal, ray->_direction);
	if (denominator > 1e-6)
	{
		glm::vec3 rayOriginMinusPlaneOrigin = _position - ray->_origin;
		float t = glm::dot(rayOriginMinusPlaneOrigin, _normal) / denominator;
		return t;
	}
	return 0.0;
}

glm::vec3 Plane::normal(glm::vec3 p0)
{
	return _normal * -1.0f;
}


