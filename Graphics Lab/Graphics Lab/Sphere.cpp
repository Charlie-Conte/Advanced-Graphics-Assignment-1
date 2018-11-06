#include "Sphere.h"


//Sphere::Sphere()
//{
//	_position = glm::vec3(0);
//	_radius = 1;
//	_material = Material(glm::vec3(0.5f, 0, 0.5f), glm::vec3(0.7f), 64);
//}



//Sphere example (vector 3(3.0,4.0,10.0), float 3.2, vector 3(0.2,0.0,0.64))
Sphere::Sphere(glm::vec3 position, float radius, Material material) :
	Object(position, material), _radius(radius)
{

}




double Sphere::intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection)
{
	glm::vec3 l = _position - rayOrigin;
	double tCA = glm::dot(l, rayDirection);
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

glm::vec3 Sphere::sphereShadowsAndReflection(vector<glm::vec3> listOfShadowRays, glm::vec3 ** image, int x, int y, glm::vec3 p0)
{

	for (int i = 0; i < listOfShadowRays.size(); i++)
	{
		double t0 = intersect(p0, listOfShadowRays[i]);
		if (t0 > 0)
		{
			//image[x][y] = _material._diffuseColour * LightMain::ambientLight;
			return glm::vec3(LightMain::lights[i]._position + (float)t0 * listOfShadowRays[i]);
		}


	}

}

glm::vec3 Sphere::normal(glm::vec3 p0)
{
	glm::vec3 pMinusC = p0 - _position;
	float pMinusCMag = glm::sqrt(glm::pow(pMinusC.x, 2) + glm::pow(pMinusC.y, 2) + glm::pow(pMinusC.z, 2));

	glm::vec3 normal = pMinusC / pMinusCMag;
	return normal;
}

