#include "Sphere.h"




//Sphere example (vector 3(3.0,4.0,10.0), float 3.2, vector 3(0.2,0.0,0.64))
Sphere::Sphere(glm::vec3 position, float radius, Material material) :
	Object(position, material), _radius(radius)
{

}




double Sphere::intersect(Ray *ray)
{
	glm::vec3 l = _position - ray->_origin;
	double tCA = glm::dot(l, ray->_direction);
	double s = glm::sqrt(glm::dot(l, l) - glm::pow(tCA, 2));
	double tHC = glm::sqrt(glm::pow(_radius, 2) - s);

	if (tCA < 0) return 0;//no hit
	else if (s > _radius) return 0;//no hit
	else
	{
		double t0 = tCA - tHC;
		return t0;
	}
	
}


glm::vec3 Sphere::normal(glm::vec3 p0)
{
	glm::vec3 pMinusC = p0 - _position;
	float pMinusCMag = glm::sqrt(glm::pow(pMinusC.x, 2) + glm::pow(pMinusC.y, 2) + glm::pow(pMinusC.z, 2));

	glm::vec3 normal = pMinusC / pMinusCMag;
	return normal;
}

