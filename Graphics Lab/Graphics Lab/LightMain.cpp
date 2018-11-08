#include "LightMain.h"



LightMain::LightMain()
{
}

vector<AreaLight*> LightMain::lights = vector<AreaLight*>();

glm::vec3 LightMain::ambientLight = glm::vec3(0.2f);
int LightMain::SAMPLES = 9;

