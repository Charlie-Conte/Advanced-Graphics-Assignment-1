#pragma once
#include "Graphics Lab.h"
#include "Ray.h"


void render(const int &WIDTH, const int &HEIGHT)
{
	//Ray is O + tD
	//rayOrigin = O		rayDirection = D		rayDistance = t
	glm::vec3	rayOrigin = { 0,0,0 }, rayDirection, rayDistance;

	//from rastor space to normalised
	float pixelNormalisedX, pixelNormalisedY;
	//from normalised space to screen space (PixelRemapped)
	float pixelScreenX, pixelScreenY;
	//from screen space to world space (PixelCamera)
	float pixelWorldX, pixelWorldY;


	glm::vec3 pixelCameraSpace;


	//Internal Aspect Ratio
	float iAR;
	//Tan value of half the FOV(Angle A) in Radians
	float tanValue = tanf((FOV / 2)*glm::pi<float>() / 180.0f);


	glm::vec3 **image = new glm::vec3*[WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		image[i] = new glm::vec3[HEIGHT];
	}

	iAR = WIDTH / (float)HEIGHT;



#pragma region Setup Scene



	LightSource MainLight = LightSource(glm::vec3(0, 20, 0), glm::vec3(1));
	LightMain::lights.push_back(MainLight);



	Sphere *redS = new Sphere(glm::vec3(0, 0, -20), 3.95f, Material(glm::vec3(1.00, 0.32, 0.36), glm::vec3(0.7f), 128));
	Sphere *yellowS = new Sphere(glm::vec3(5, -1, -15), 2, Material(glm::vec3(0.90, 0.76, 0.46), glm::vec3(0.7f), 200));
	Sphere *lightBlueS = new Sphere(glm::vec3(5, 0, -25), 3, Material(glm::vec3(0.65, 0.77, 0.97), glm::vec3(0.7f), 60));
	Sphere *lightGrayS = new Sphere(glm::vec3(-5.5, 0, -15), 3, Material(glm::vec3(0.90, 0.90, 0.90), glm::vec3(0.7f), 100));
	Sphere *lightGrayS2 = new Sphere(glm::vec3(-5.5, 3, -13), 3, Material(glm::vec3(0.90, 0.90, 0.90), glm::vec3(0.7f), 100));

	Object::objectList.push_back(redS);
	Object::objectList.push_back(yellowS);
	Object::objectList.push_back(lightBlueS);
	Object::objectList.push_back(lightGrayS);
	Object::objectList.push_back(lightGrayS2);



	Plane *floor = new Plane(glm::vec3(-0, -10, -0), glm::vec3(0, -1, 0), Material(glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.7f), 64));
	Object::objectList.push_back(floor);


	Triangle *tri = new Triangle(glm::vec3(0, 1, -16.1), glm::vec3(-1.9, -1, -16.1), glm::vec3(1.6, -0.5, -16.1), Material(glm::vec3(0, 0.5, 0.5), glm::vec3(0.7f), 128));
	//Triangle triSmooth = Triangle(glm::vec3(0,1,-2), glm::vec3(-1.9, -1, -2), glm::vec3(1.6, -0.5, -2),glm::vec3(0,0.6f,1), glm::vec3(-0.4f,-0.4f,1), glm::vec3(0.4f,-0.4f,1), Material(glm::vec3(0, 0.5, 0.5), glm::vec3(0.7f), 128));
	Object::objectList.push_back(tri);
	//objectList.push_back(triSmooth);

	//Triangle::MoveObject(fileObjects[0], glm::vec3(7, 0, -10));
	//Triangle::MoveObject(fileObjects[1], glm::vec3(-7, 0, -10));
	//Triangle::MoveObject(fileObjects[2], glm::vec3(-8, 0, -10));



#pragma endregion

	SDL_Window *window = SDL_CreateWindow("Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, APP_WIDTH, APP_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface *surface = nullptr;

	surface = SDL_GetWindowSurface(window);

	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0x00, 0x00, 0x00, 0x00));

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{

			pixelNormalisedX = (x + 0.5f) / (float)WIDTH;
			pixelNormalisedY = (y + 0.5f) / (float)HEIGHT;
			pixelScreenX = 2 * pixelNormalisedX - 1.0f;
			pixelScreenY = 1.0f - 2 * pixelNormalisedY;
			pixelScreenX = pixelScreenX * iAR;

			pixelWorldX = pixelScreenX * tanValue;
			pixelWorldY = pixelScreenY * tanValue;

			//set pixel camera space - in regards to origin
			//TODO - add object origin manipulation 
			//													,distance from origin
			pixelCameraSpace = glm::vec3(pixelWorldX, pixelWorldY, -1.0);

			rayDirection = glm::normalize(pixelCameraSpace - rayOrigin);

			Ray *mainRay = new Ray(rayDirection, rayOrigin);

			image[x][y] = glm::vec3(0.22f,0.69f,0.87f); //set background colour


			double closestDistance = 1000000.f;
			Object *closestObject = new Object(glm::vec3(0),Material());

			mainRay->RayCast(closestDistance, closestObject);

			if (closestDistance < 999999.f) {
				glm::vec3 p0 = rayOrigin + closestDistance * rayDirection;
				closestObject->calculateColour(p0, image, x, y, closestObject->_material, closestObject->normal(p0), rayDirection);
			}

			typedef struct
			{
				Uint8 r;
				Uint8 g;
				Uint8 b;
				Uint8 unused;
			} My_Color;
			My_Color color;
			color.r = (unsigned char)(std::min((float)1, (float)image[x][y].z) * 255);
			color.g = (unsigned char)(std::min((float)1, (float)image[x][y].y) * 255);
			color.b = (unsigned char)(std::min((float)1, (float)image[x][y].x) * 255);
			Uint8* pixel = (Uint8*)surface->pixels;
			pixel += (y * surface->pitch) + (x *(sizeof(Uint32)));
			*((Uint32*)pixel) = *(Uint32 *)& color;

		}

	}

	SDL_UpdateWindowSurface(window);
	//createPPM(WIDTH, HEIGHT, image);




}

void createPPM(const int &WIDTH, const int &HEIGHT, glm::vec3 ** image)
{
	// Save result to a PPM image
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			ofs << (unsigned char)(std::min((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(std::min((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(std::min((float)1, (float)image[x][y].z) * 255);
		}

		//cout << ((1 / (float)HEIGHT)*y) * 100 << "%\n";
	}
	ofs.close();
}

vector<list<Triangle>> loadFileObjects()
{
	vector<list<Triangle>> objectList;
	//objectList.push_back(loadOBJ("cube_simple.obj", Material(glm::vec3(0.6, 0.0, 0.2), glm::vec3(0.7f), 128) ));
	//objectList.push_back(loadOBJ("teapot_simple.obj", Material(glm::vec3(0, 1, 0.9), glm::vec3(0.7f), 128) ));
	//objectList.push_back(loadOBJ("monkey_simple.obj", Material(glm::vec3(0.37, 0.15, 0.02), glm::vec3(0.7f), 50) ));




	return objectList;


}
list<Triangle> loadOBJ(string OBJ_Name, Material material)
{
	//vector<glm::vec3> verts, norms;
	//loadOBJ((basePath + OBJ_Name).c_str(), verts, norms);


	//for (unsigned int i = 0; i < verts.size(); i += 3)
	//{
	//	objectList.push_back(new Triangle(verts[i], verts[i + 1], verts[i + 2], norms[i],norms[i+1],norms[i+2], material));
	//}
	//return object;
}



int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	basePath = SDL_GetBasePath();
	SDL_free(&basePath);

	fileObjects = loadFileObjects();

	render(APP_WIDTH, APP_HEIGHT);
	cout << "Done\n\n";



	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					return 0;
					break;
				}
			case SDL_QUIT:

				return 0;
				break;
			}
		}
	}


	return 0;
}
