#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

#include <glm/glm.hpp>
#include "getbmp.h"
#include <SDL.h>
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
//#undef main

#include "Sphere.h"


using vector3 = glm::vec3;
using namespace std;


const int APP_WIDTH = 1280;
const int APP_HEIGHT = 720;

void renderSpheres(std::list<Sphere> &spheres, vector3 &rayOrigin, vector3 &rayDirection, vector3 ** image, int x, int y);
void createPPM(const int &WIDTH, const int &HEIGHT, vector3 ** image);

void render(const int &WIDTH, const int &HEIGHT);

int main(int argc, char* args[]);