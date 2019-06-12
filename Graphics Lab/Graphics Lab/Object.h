#pragma once
#include "MainIncludes.h"
#include "LightMain.h"
#include "Ray.h"

class Object
{
public:

	//Base Object
	Object(glm::vec3 position, Material material);

	//Will display the objects position XYZ
	void PrintMatrix();

	//Can calculate the current pixel colour by using the closest object
	static void calculateColour(glm::vec3 & p0, glm::vec3 ** image, int x, int y,Material material, glm::vec3 normal, glm::vec3 rayDirection);

	static void setShadow(bool hasHit, float shadowSoftness, glm::vec3 ** image, int x, int y, glm::vec3 ambientColour, glm::vec3 diffuseColour, glm::vec3 specularColour);


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
		HARD = 1,
		SOFT = 2
	};

	//for loading either Teapot or Monkey model
	enum objectState
	{
		PRIMATIVE_PLUS_TEAPOT = 2,
		PRIMATIVE_PLUS_MONKEY = 1,
		PRIMATIVE = 0
	};
};

