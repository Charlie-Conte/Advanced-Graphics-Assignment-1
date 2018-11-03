#include "Graphics Lab.h"



void render(const int &WIDTH, const int &HEIGHT)
{

	//Angle A
	const int FOV = 30;

	//Ray is O + tD
	//rayOrigin = O		rayDirection = D		rayDistance = t
	vector3	rayOrigin = { 0,0,0 }, rayDirection, rayDistance;

	//from rastor space to normalised
	float pixelNormalisedX, pixelNormalisedY;
	//from normalised space to screen space (PixelRemapped)
	float pixelScreenX, pixelScreenY;
	//from screen space to world space (PixelCamera)
	float pixelWorldX, pixelWorldY;


	vector3 pixelCameraSpace;


	//Internal Aspect Ratio
	float iAR;
	//Tan value of half the FOV(Angle A) in Radians
	float tanValue = tanf((FOV / 2)*glm::pi<float>() / 180.0f);


	vector3 **image = new vector3*[WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		image[i] = new vector3[HEIGHT];
	}
	
	iAR = WIDTH / (float)HEIGHT;

	list<Sphere> spheres;

	Sphere redS =		Sphere(vector3(0,		0,		-20), 4, vector3(1.00, 0.32, 0.36));
	Sphere yellowS =	Sphere(vector3(5,		-1,		-15), 2, vector3(0.90, 0.76, 0.46));
	Sphere lightBlueS = Sphere(vector3(5,		0,		-25), 3, vector3(0.65, 0.77, 0.97));
	Sphere lightGrayS = Sphere(vector3(-5.5,	0,		-15), 3, vector3(0.90, 0.90, 0.90));
	Sphere darkGrayS =	Sphere(vector3(0,	-10004,		-20), 10000, vector3(0.20, 0.20, 0.20));
	spheres.push_back(redS);
	spheres.push_back(yellowS);
	spheres.push_back(lightBlueS);
	spheres.push_back(lightGrayS);
	spheres.push_back(darkGrayS);


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
			pixelCameraSpace = vector3(pixelWorldX, pixelWorldY, -1.0);

			rayDirection = glm::normalize(pixelCameraSpace - rayOrigin);

			renderSpheres(spheres, rayOrigin, rayDirection, image, x, y);



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
void createPPM(const int &WIDTH, const int &HEIGHT, vector3 ** image)
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

void renderSpheres(std::list<Sphere> &spheres, vector3 &rayOrigin, vector3 &rayDirection, vector3 ** image, int x, int y)
{
	vector3 tempP0 = vector3(NULL);
	vector3 tempP1 = vector3(NULL);

	for (Sphere ball : spheres)
	{
		vector3 l = ball.position - rayOrigin;
		double tCA = glm::dot(l, rayDirection);
		double s = glm::sqrt(glm::dot(l, l) - glm::pow(tCA, 2));
		double tHC = glm::sqrt(glm::pow(ball.radius, 2) - s);

		if (tCA < 0);//no hit
		else if (s > ball.radius);//no hit
		else
		{
			double t0 = tCA - tHC;
			double t1 = tCA + tHC;

			vector3 p0 = rayOrigin + (float)t0 * rayDirection;
			vector3 p1 = rayOrigin + (float)t1 * rayDirection;


			if (glm::length(p0) < glm::length(tempP0))
			{
				tempP0 = p0;
				tempP1 = p1;
				image[x][y].x = ball.colour.x;
				image[x][y].y = ball.colour.y;
				image[x][y].z = ball.colour.z;
			}
			else if (glm::length(tempP0) == 0 && glm::length(tempP1) == 0)
			{
				tempP0 = p0;
				tempP1 = p1;
				image[x][y].x = ball.colour.x;
				image[x][y].y = ball.colour.y;
				image[x][y].z = ball.colour.z;
			}





		}
	}
}


int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);


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
