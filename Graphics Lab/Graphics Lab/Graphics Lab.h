#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

#include <glm/glm.hpp>
#include "getbmp.h"
#include <SDL.h>

#include "Sphere.h"

using vector3 = glm::vec3;
using namespace std;

void renderSpheres(std::list<Sphere> &spheres, vector3 &rayOrigin, vector3 &rayDirection, vector3 ** image, int x, int y);
void createPPM(const int &WIDTH, const int &HEIGHT, vector3 ** image);

void render();

int wmain();