#include "Graphics Lab.h"



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


	//LightMain::ambientLight = glm::vec3(0.2f);
	LightSource MainLight = LightSource(glm::vec3(0, 20, 0),glm::vec3(1));
	LightMain::lights.push_back(MainLight);

	list<Sphere> spheres;

	Sphere redS =		Sphere(glm::vec3(0,		0,		-20), 3.95f, glm::vec3(1.00, 0.32, 0.36));
	Sphere yellowS =	Sphere(glm::vec3(5,		-1,		-15), 2, glm::vec3(0.90, 0.76, 0.46));
	Sphere lightBlueS = Sphere(glm::vec3(5,		0,		-25), 3, glm::vec3(0.65, 0.77, 0.97));
	Sphere lightGrayS = Sphere(glm::vec3(-5.5,	0,		-15), 3, glm::vec3(0.90, 0.90, 0.90));
	//Sphere darkGrayS =	Sphere(glm::vec3(0,	-10004,		-20), 10000, glm::vec3(0.20, 0.20, 0.20));
	spheres.push_back(redS);
	spheres.push_back(yellowS);
	spheres.push_back(lightBlueS);
	spheres.push_back(lightGrayS);
	//spheres.push_back(darkGrayS);

	list<Plane> planes;
	Plane floor = Plane(glm::vec3(0, -10, -20),glm::vec3(0,-1,0), glm::vec3(0.20, 0.20, 0.20));
	planes.push_back(floor);

	list<Triangle> triangles;
	Triangle tri = Triangle(glm::vec3(0, 1, -16.1), glm::vec3(-1.9, -1, -16.1), glm::vec3(1.6, -0.5, -16.1), glm::vec3(0, 0.5, 0.5));
	triangles.push_back(tri);

	Triangle::MoveObject(fileObjects[0], glm::vec3(7, 0, -10));
	Triangle::MoveObject(fileObjects[1], glm::vec3(-7, 0, -10));

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


			bool hasHit = false;

			glm::vec3 tempP0 = glm::vec3(NULL);
			glm::vec3 tempP1 = glm::vec3(NULL);
			Plane::renderPlanes(planes, rayOrigin, rayDirection, image, x, y, hasHit,tempP0);
			Sphere::renderSpheres(spheres, rayOrigin, rayDirection, image, x, y, hasHit,tempP0,tempP1);
			Triangle::renderTriangles(triangles, rayOrigin, rayDirection, image, x, y, hasHit,tempP0);


			Triangle::renderTriangles(fileObjects[0], rayOrigin, rayDirection, image, x, y, hasHit,tempP0);
			//Triangle::renderTriangles(fileObjects[1], rayOrigin, rayDirection, image, x, y, hasHit,tempP0); //teapot




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
			*((Uint32*)pixel) = *(Uint32 *) & color;

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
	objectList.push_back( loadOBJ("cube_simple.obj", glm::vec3(0.6, 0.0, 0.2)));
	objectList.push_back( loadOBJ("teapot_simple.obj", glm::vec3(1, 1, 0.9)));




	return objectList;


}
list<Triangle> loadOBJ(string OBJ_Name, glm::vec3 colour)
{
	vector<glm::vec3> verts, norms;
	loadOBJ((basePath + OBJ_Name).c_str(), verts, norms);


	list<Triangle> object;
	for (unsigned int i = 0; i < verts.size(); i += 3)
	{
		object.push_back(Triangle(verts[i], verts[i + 1], verts[i + 2], norms[i], colour));
	}
	return object;
}



int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	basePath = SDL_GetBasePath();
	SDL_free(&basePath);

	fileObjects = loadFileObjects();

	render(APP_WIDTH,APP_HEIGHT);
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
