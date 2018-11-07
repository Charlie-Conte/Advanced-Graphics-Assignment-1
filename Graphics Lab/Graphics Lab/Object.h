#pragma once
#include "MainIncludes.h"
#include "LightMain.h"
#include "Ray.h"

class Object
{
public:


	Object(glm::vec3 position, Material material);
	void PrintMatrix();

	static vector<glm::vec3> calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y,Material material, glm::vec3 normal, glm::vec3 rayDirection);

	static void setShadow(bool hasHit, glm::vec3 ** image, int x, int y, glm::vec3 ambientColour, glm::vec3 diffuseColour, glm::vec3 specularColour);


	virtual double intersect(Ray * ray);
	virtual glm::vec3 normal(glm::vec3 p0);

	glm::vec3 _position;
	Material _material;


	static vector<Object *> objectList;
	static int LIGHTING, SHADOWS, OBJECT_TOGGLE;

	enum lightState
	{
		ALL = 3,
		AMBIENT_AND_DIFFUSE = 2,
		AMBIENT = 1,
		NO_LIGHT = 0
	};

	enum shadowState
	{
		NO_SHADOW = 0,
		HARD = 1
	};

	enum objectState
	{
		PRIMATIVE_PLUS_TEAPOT = 2,
		PRIMATIVE_PLUS_MONKEY = 1,
		PRIMATIVE = 0
	};
};

