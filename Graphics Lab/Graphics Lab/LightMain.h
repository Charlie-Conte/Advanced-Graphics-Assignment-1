#pragma once
#include "MainIncludes.h"
#include "LightSource.h"
class LightMain 
{
public:

	LightMain();
	static vector<LightSource> lights;

	static glm::vec3 ambientLight;


};

