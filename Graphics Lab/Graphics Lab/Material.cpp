#include "Material.h"




Material::Material(glm::vec3 diffuseColour, glm::vec3 specularColour, float shininess)
{
	_diffuseColour = diffuseColour;
	_specularColour = specularColour;
	_shinyness = shininess;
}

Material::Material()
{
}
