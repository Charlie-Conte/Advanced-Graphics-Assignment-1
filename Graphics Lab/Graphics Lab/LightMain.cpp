#include "LightMain.h"



LightMain::LightMain()
{
}

vector<LightSource> LightMain::lights = vector<LightSource>();

glm::vec3 LightMain::ambientLight = glm::vec3(0.2f);


