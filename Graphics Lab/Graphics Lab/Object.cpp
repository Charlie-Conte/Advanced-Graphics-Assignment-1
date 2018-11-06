#include "Object.h"



Object::Object()
{
	_position = glm::vec3();

}
Object::Object(glm::vec3 position)
{
	_position = position;
}

void Object::PrintMatrix()
{
	std::cout << "(" << _position.x << ",\t" << _position.y << ",\t" << _position.z << ")\n";


}


void Object::calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y, Material material, glm::vec3 normal, glm::vec3 rayDirection)
{

	glm::vec3 ambientColour;
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;

	//ambient lighting
	ambientColour = material._diffuseColour * LightMain::ambientLight;

	for (LightSource lightSource : LightMain::lights)
	{


		//diffuse lighting
		glm::vec3 l = glm::normalize(lightSource._position - p0);
		glm::vec3 n = glm::normalize(normal);
		diffuseColour = material._diffuseColour			* lightSource._intensity	*	fmax(	glm::dot(l, normal),0.0f);


		//specular lighting
		glm::vec3 r = 2.0f * (glm::dot(l, n)) * n - l;

		float rDotV = glm::dot(glm::normalize(r), rayDirection *-1.0f);
		specularColour = material._specularColour	* lightSource._intensity	*	glm::pow(	glm::max(rDotV, 0.0f), material._shininess);

	}

	image[x][y] = ambientColour + diffuseColour + specularColour;
	
}










