#pragma once
#include "MainIncludes.h"
#include "AreaLight.h"
class LightMain 
{
public:

	LightMain();
	static vector<AreaLight*> lights;

	static glm::vec3 ambientLight;
	static int SAMPLES;

};

