#include "MainIncludes.h"

#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "objloader.h"
#include "LightSource.h"


string basePath;
vector<vector<Triangle*>> fileObjects;

const int APP_WIDTH = 1280;
const int APP_HEIGHT = 720;

SDL_Window *window;

//const int APP_WIDTH = 800;
//const int APP_HEIGHT = 400;

//Angle A
const int FOV = 60;
int FOVmod = 0;
int FOVincrement = 5;

float sizeModifier = 0.25f;
float sizeIncrement = 0.05f;


void createPPM(const int &WIDTH, const int &HEIGHT, glm::vec3 ** image);
vector<vector<Triangle*>> loadFileObjects();
vector<Triangle*> loadColouredOBJ(string OBJ_Name, Material material);
void render(const int &WIDTH, const int &HEIGHT);





int main(int argc, char* args[]);

void reRender();
