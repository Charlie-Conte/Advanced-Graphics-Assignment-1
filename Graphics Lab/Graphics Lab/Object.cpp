#include "Object.h"

vector<Object *> Object::objectList;

int Object::LIGHTING = Object::ALL;
int Object::SHADOWS = Object::HARD;
int Object::OBJECT_TOGGLE = Object::PRIMATIVE;

Object::Object(glm::vec3 position, Material material) :
	_position(position), _material(material)
{

}

void Object::PrintMatrix()
{
	std::cout << "(" << _position.x << ",\t" << _position.y << ",\t" << _position.z << ")\n";


}


void Object::calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y, Material material, glm::vec3 normal, glm::vec3 rayDirection)
{

	bool hasHit = false;
	float shadowSoftness;

	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;

	//ambient lighting

	ambientColour = material._diffuseColour * LightMain::ambientLight;

	for (AreaLight *lightSource : LightMain::lights)
	{
		//diffuse lighting

		glm::vec3 l = glm::normalize(lightSource->_position - p0);

		glm::vec3 n = glm::normalize(normal);
		diffuseColour = material._diffuseColour			* lightSource->_intensity	*	fmax(glm::dot(l, normal), 0.0f);


		//specular lighting

		glm::vec3 r = 2.0f * (glm::dot(l, n)) * n - l;

		float rDotV = glm::dot(glm::normalize(r), rayDirection *-1.0f);
		specularColour = material._specularColour	* lightSource->_intensity	*	glm::pow(glm::max(rDotV, 0.0f), material._shininess);



		switch (SHADOWS)
		{
		case HARD:
		{
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
		break;
		case SOFT:
		{
			glm::vec3 lSSize = lightSource->_size;
			glm::vec3 posOnLightSource = lSSize + glm::vec3(-lSSize.x / 2, 0, -lSSize.z / 2);
			glm::vec3 posIncrement = glm::vec3(lSSize.x / LightMain::SAMPLES,0, lSSize.z / LightMain::SAMPLES);
			glm::vec3 jitter = glm::linearRand(glm::vec3(0), posIncrement);
			jitter.y = 0;


			for (int i = 0; i < LightMain::SAMPLES; i++)
			{
				for (int j = 0; j < LightMain::SAMPLES; j++)
				{
					double closestDistance = 1000000.f;
					Object *closestObject = nullptr;
					glm::vec3 sampleOrigin = glm::vec3(posOnLightSource.x + (posIncrement.x * i), posOnLightSource.y, posOnLightSource.z + (posIncrement.z * j)) + lightSource->_position + jitter;
					l = glm::normalize(sampleOrigin - p0);
					
					Ray *shadowRay = new Ray(l, p0 + (n * 1e-4));
					shadowRay->RayCast(closestDistance, closestObject);
					if (closestDistance < 999999.f)
					{
						hasHit = true;
						shadowSoftness += 1;
					}
					delete shadowRay;
					
				}
			}
			shadowSoftness = shadowSoftness / glm::pow(LightMain::SAMPLES, 2);
		}
		break;
		}

	}


	switch (LIGHTING)
	{
	case NO_LIGHT:
		image[x][y] = material._diffuseColour;
		break;
	case AMBIENT:
		setShadow(hasHit, shadowSoftness, image, x, y, ambientColour, glm::vec3(0), glm::vec3(0));
		break;
	case AMBIENT_AND_DIFFUSE:
		setShadow(hasHit, shadowSoftness, image, x, y, ambientColour, diffuseColour, glm::vec3(0));
		break;
	case ALL:
		setShadow(hasHit, shadowSoftness, image, x, y, ambientColour, diffuseColour, specularColour);
		break;
	}

}

void Object::setShadow(bool hasHit, float shadowSoftness, glm::vec3 ** image, int x, int y, glm::vec3 ambientColour, glm::vec3 diffuseColour, glm::vec3 specularColour)
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
	case SOFT:
		if (!hasHit)
		{
			image[x][y] = ambientColour + diffuseColour + specularColour;
		}
		else
		{
			image[x][y] = ambientColour + (diffuseColour + specularColour)*(1 - shadowSoftness);
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










