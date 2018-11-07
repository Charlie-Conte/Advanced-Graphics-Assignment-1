#include "Object.h"

vector<Object *> Object::objectList;

int Object::LIGHTING = 0;
int Object::SHADOWS = 1;
int Object::OBJECT_TOGGLE = 0;

Object::Object(glm::vec3 position, Material material) :
	_position(position), _material(material)
{

}

void Object::PrintMatrix()
{
	std::cout << "(" << _position.x << ",\t" << _position.y << ",\t" << _position.z << ")\n";


}


vector<glm::vec3> Object::calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y, Material material, glm::vec3 normal, glm::vec3 rayDirection)
{
	vector<glm::vec3>listOfShadowRays;

	bool hasHit = false;

	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;

	//ambient lighting
	ambientColour = material._diffuseColour * LightMain::ambientLight;

	for (LightSource lightSource : LightMain::lights)
	{
		//diffuse lighting
		glm::vec3 l = glm::normalize(lightSource._position - p0);

		listOfShadowRays.push_back(l);

		glm::vec3 n = glm::normalize(normal);
		diffuseColour = material._diffuseColour			* lightSource._intensity	*	fmax(glm::dot(l, normal), 0.0f);


		//specular lighting
		glm::vec3 r = 2.0f * (glm::dot(l, n)) * n - l;

		float rDotV = glm::dot(glm::normalize(r), rayDirection *-1.0f);
		specularColour = material._specularColour	* lightSource._intensity	*	glm::pow(glm::max(rDotV, 0.0f), material._shininess);

		// PUT SHADOW STUFF HERE
		double closestDistance = 1000000.f;
		Object *closestObject = nullptr;
		Ray *shadowRay = new Ray(l, p0 + (n * 1e-4));

		shadowRay->RayCast(closestDistance, closestObject);
		if (closestDistance < 999999.f)
		{
			hasHit = true;
		}
		delete shadowRay;

	}
	switch (LIGHTING)
	{
	case NO_LIGHT:
		image[x][y] = material._diffuseColour;
		break;
	case AMBIENT:
		setShadow(hasHit, image, x, y, ambientColour, glm::vec3(0), glm::vec3(0));
		break;
	case AMBIENT_AND_DIFFUSE:
		setShadow(hasHit, image, x, y, ambientColour, diffuseColour, glm::vec3(0));
		break;
	case ALL:
		setShadow(hasHit, image, x, y, ambientColour, diffuseColour, specularColour);
		break;
	}



	return listOfShadowRays;
}

void Object::setShadow(bool hasHit, glm::vec3 ** image, int x, int y, glm::vec3 ambientColour, glm::vec3 diffuseColour, glm::vec3 specularColour)
{
	switch (SHADOWS)
	{
	case HARD:
		if (!hasHit)
		{
			image[x][y] = ambientColour + diffuseColour + specularColour;
		}
		else
		{
			image[x][y] = ambientColour;
		}
		break;
	case NO_SHADOW:
		image[x][y] = ambientColour + diffuseColour + specularColour;
		break;
	}


}

double Object::intersect(Ray * ray)
{
	return 0.0;
}

glm::vec3 Object::normal(glm::vec3 p0)
{
	return glm::vec3();
}










