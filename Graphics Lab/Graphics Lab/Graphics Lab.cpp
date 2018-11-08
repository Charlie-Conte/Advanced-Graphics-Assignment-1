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
	float tanValue = tanf(((FOV + FOVmod) / 2)*glm::pi<float>() / 180.0f);


	glm::vec3 **image = new glm::vec3*[WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		image[i] = new glm::vec3[HEIGHT];
	}

	iAR = WIDTH / (float)HEIGHT;



#pragma region Setup Scene

	AreaLight *MainLight = nullptr;

	if (activeLight == 2)MainLight = new AreaLight(glm::vec3(-4.5, 10, 0), glm::vec3(1), glm::vec3(9, 0.1, 9));
	if (activeLight == 1)MainLight = new AreaLight(glm::vec3(10, 10, 0), glm::vec3(1), glm::vec3(5, 0.1, 5));

	LightMain::lights.push_back(MainLight);




	Sphere *redS = new Sphere(glm::vec3(0, 0, -30), 3.95f, Material(glm::vec3(1.00, 0.32, 0.36), glm::vec3(0.7f), 128));
	Sphere *yellowS = new Sphere(glm::vec3(5, -1, -25), 2, Material(glm::vec3(0.90, 0.76, 0.46), glm::vec3(0.7f), 200));
	Sphere *lightBlueS = new Sphere(glm::vec3(5, 0, -30), 3, Material(glm::vec3(0.65, 0.77, 0.97), glm::vec3(0.7f), 60));
	Sphere *lightGrayS = new Sphere(glm::vec3(-5.5, 0, -27), 3, Material(glm::vec3(0.90, 0.90, 0.90), glm::vec3(0.7f), 100));


	Object::objectList.push_back(redS);
	Object::objectList.push_back(yellowS);
	Object::objectList.push_back(lightBlueS);
	Object::objectList.push_back(lightGrayS);




	Plane *floor = new Plane(glm::vec3(-0, -10, -0), glm::vec3(0, -1, 0), Material(glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.7f), 64));
	Object::objectList.push_back(floor);


	//Triangle *tri = new Triangle(glm::vec3(0, 1, -16.1), glm::vec3(-1.9, -1, -16.1), glm::vec3(1.6, -0.5, -16.1), Material(glm::vec3(0, 0.5, 0.5), glm::vec3(0.7f), 128));
	//Triangle triSmooth = Triangle(glm::vec3(0,1,-2), glm::vec3(-1.9, -1, -2), glm::vec3(1.6, -0.5, -2),glm::vec3(0,0.6f,1), glm::vec3(-0.4f,-0.4f,1), glm::vec3(0.4f,-0.4f,1), Material(glm::vec3(0, 0.5, 0.5), glm::vec3(0.7f), 128));
	//Object::objectList.push_back(tri);
	//objectList.push_back(triSmooth);
	Triangle::MoveObject(fileObjects[0], glm::vec3(6, 4, -12));
	Triangle::MoveObject(fileObjects[1], glm::vec3(1, 3, -10));

	if (Object::OBJECT_TOGGLE == Object::PRIMATIVE_PLUS_TEAPOT)
	{
		Triangle::MoveObject(fileObjects[2], glm::vec3(-6, -2, -13));
	}
	if (Object::OBJECT_TOGGLE == Object::PRIMATIVE_PLUS_MONKEY)
	{
		Triangle::MoveObject(fileObjects[2], glm::vec3(-8, 0, -10));
	}

	for (vector<Triangle*> vTri : fileObjects)
	{
		for (Triangle* thisTri :vTri)
		{
			Object::objectList.push_back(thisTri);
		}
	}



#pragma endregion

	window = SDL_CreateWindow("Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == 0)
	{
		cout << "SDL_CreateWindow failed\n";
	}
	SDL_Surface *surface = nullptr;

	surface = SDL_GetWindowSurface(window);

	if (SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0x00, 0x00, 0x00, 0x00)) != 0)
	{
		cout << "SDL_FillRect failed\n";
	}

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
			//													,distance from origin
			pixelCameraSpace = glm::vec3(pixelWorldX, pixelWorldY, -1.0);

			rayDirection = glm::normalize(pixelCameraSpace - rayOrigin);

			Ray *mainRay = new Ray(rayDirection, rayOrigin);

			image[x][y] = glm::vec3(0.22f,0.69f,0.87f); //set background colour


			double closestDistance = 1000000.f;
			Object *closestObject = nullptr;

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

			delete mainRay;


		}

	}

	if (SDL_UpdateWindowSurface(window) != 0)
	{
		cout << "SDL_UpdateWindowSurface failed\n";
	}
	createPPM(WIDTH, HEIGHT, image);


}

void createPPM(const int &WIDTH, const int &HEIGHT, glm::vec3 ** image)
{
	// Save result to a PPM image
	std::ofstream ofs("./export.ppm", std::ios::out | std::ios::binary);
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

vector<vector<Triangle*>> loadFileObjects()
{
	vector<vector<Triangle*>> importedOBJList;
	importedOBJList.push_back(loadColouredOBJ("cube_simple.obj", Material(glm::vec3(0.8, 0.0, 0.8), glm::vec3(0.7f), 128)));
	importedOBJList.push_back(loadColouredOBJ("custom.obj", Material(glm::vec3(0.6, 0.0, 0.2), glm::vec3(0.7f), 30)));

	if (Object::OBJECT_TOGGLE == Object::PRIMATIVE_PLUS_TEAPOT)
	{
		importedOBJList.push_back(loadColouredOBJ("teapot_simple.obj", Material(glm::vec3(0.55, 0.46, 0), glm::vec3(0.7f), 30)));
	}
	if (Object::OBJECT_TOGGLE == Object::PRIMATIVE_PLUS_MONKEY)
	{
		importedOBJList.push_back(loadColouredOBJ("monkey_simple.obj", Material(glm::vec3(0.37, 0.15, 0.02), glm::vec3(0.7f), 50)));
	}



	return importedOBJList;


}
vector<Triangle*> loadColouredOBJ(string OBJ_Name, Material material)
{
	vector<glm::vec3> verts, norms;
	loadOBJ((basePath + OBJ_Name).c_str(), verts, norms);

	vector<Triangle*> triList;
	for (unsigned int i = 0; i < verts.size(); i += 3)
	{
		triList.push_back(new Triangle(verts[i], verts[i + 1], verts[i + 2], norms[i],norms[i+1],norms[i+2], material));
	}
	return triList;
}



int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	basePath = SDL_GetBasePath();
	if (basePath == "")
	{
		cout << "SDL_GetBasePath failed\n";
	}
	SDL_free(&basePath);


	fileObjects = loadFileObjects();

	render(APP_WIDTH*sizeModifier, APP_HEIGHT*sizeModifier);
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
				case SDLK_1:
					activeLight = 1;
					reRender();
					break;		
				case SDLK_2:
					activeLight = 2;
					reRender();
					break;

				case SDLK_l:
					Object::LIGHTING += 1;
					if (Object::LIGHTING == 4)Object::LIGHTING = 0;
					if (Object::LIGHTING == 0)Object::SHADOWS = Object::NO_SHADOW;
					reRender();
					break;		
				case SDLK_s:
					Object::SHADOWS += 1;
					if (Object::SHADOWS == 3)Object::SHADOWS = 0;
					reRender();
					break;

				case SDLK_EQUALS:
					FOVmod += FOVincrement;
					reRender();
					break;		
				case SDLK_MINUS:
					FOVmod -= FOVincrement;
					reRender();
					break;
				case SDLK_b:
					Object::OBJECT_TOGGLE = Object::PRIMATIVE;
					reRender();
					break;
				case SDLK_n:
					Object::OBJECT_TOGGLE = Object::PRIMATIVE_PLUS_TEAPOT;
					reRender();
					break;				
				case SDLK_m:
					Object::OBJECT_TOGGLE = Object::PRIMATIVE_PLUS_MONKEY;
					reRender();
					break;

				case SDLK_UP:
					sizeModifier += sizeIncrement;
					reRender();
					break;				
				case SDLK_DOWN:
					sizeModifier -= sizeIncrement;
					reRender();
					break;
				case SDLK_ESCAPE:
					return 0;
					break;
				}
				break;
			case SDL_QUIT:

				return 0;
				break;
			}
		}
	}


	return 0;
}

void reRender()
{
	LightMain::lights.clear();
	Object::objectList.clear();
	SDL_DestroyWindow(window);
	fileObjects.clear();
	fileObjects = loadFileObjects();
	render(APP_WIDTH*sizeModifier, APP_HEIGHT*sizeModifier);
	cout << "Done\n\n";
}

