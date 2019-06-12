#pragma once
#include "MainIncludes.h"
#include "AreaLight.h"
//Light manager
class LightMain 
{
public:

	LightMain();
	static vector<AreaLight*> lights;

	static glm::vec3 ambientLight;
	static int SAMPLES;

};

