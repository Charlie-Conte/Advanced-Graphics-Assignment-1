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

//const int APP_WIDTH = 800;
//const int APP_HEIGHT = 400;

//Angle A
const int FOV = 60;




void createPPM(const int &WIDTH, const int &HEIGHT, glm::vec3 ** image);
vector<vector<Triangle*>> loadFileObjects();
vector<Triangle*> loadColouredOBJ(string OBJ_Name, Material material);
void render(const int &WIDTH, const int &HEIGHT);





int main(int argc, char* args[]);