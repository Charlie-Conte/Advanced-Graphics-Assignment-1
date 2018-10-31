
#include <iostream>
#include <fstream>
#include <algorithm>

#include <glm/glm.hpp>
#include "getbmp.h"
#include <SDL.h>

using vector3 = glm::vec3;
using namespace std;

void render()
{
	const  float PI = 3.14159;
	const int WIDTH = 48;
	const int HEIGHT = 27;
	//Angle A
	const int FOV = 30;

	//Ray is O + tD
	//rayOrigin = O		rayDirection = D		rayDistance = t
	vector3	rayOrigin = { 0,0,0 }, rayDirection, rayDistance;

	//from rastor space to normalised
	float pixelNormalisedX, pixelNormalisedY;
	//from normalised space to screen space
	float pixelScreenX, pixelScreenY;
	//from screen space to world space
	float pixelWorldX, pixelWorldY;


	//Internal Aspect Ratio
	float iAR;
	//Tan value of half the FOV(Angle A) in Radians
	float tanValue = tanf((FOV / 2)*PI / 180.0);


	vector3 **image = new vector3*[WIDTH];
	for (int i = 0; i < WIDTH; i++) { image[i] = new vector3[HEIGHT]; }

	iAR = WIDTH / (float)HEIGHT;
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			image[x][y].r = 100;	
			image[x][y].g = 0;	
			image[x][y].b = 100;	


			pixelNormalisedX = (x + 0.5) / (float)WIDTH;
			pixelNormalisedY = (y + 0.5) / (float)HEIGHT;
			pixelScreenX = 2 * pixelNormalisedX - 1.0;
			pixelScreenY = 1.0 - 2 * pixelNormalisedY;
			pixelScreenX = pixelScreenX * iAR;

			pixelWorldX = pixelScreenX * tanValue;
			pixelWorldY = pixelScreenY * tanValue;

			image[x][y].x = pixelWorldX;
			image[x][y].y = pixelWorldY;
			image[x][y].z = -1.0;
			
		}

	}

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
		
		cout << ((1 / (float)HEIGHT)*y) *100 << "%\n";
	}
	ofs.close();

}


void mathTest()
{
	vector3 one = { 1, 2, 3 };
	vector3 two = { 4, 5, 5 };

	vector3 sum = one + two;

	cout << "one" << "[" << one.x << "," << one.y << "," << one.z << "]\n";
	cout << "two" << "[" << two.x << "," << two.y << "," << two.z << "]\n\n";
	cout << "sum" << "[" << sum.x << "," << sum.y << "," << sum.z << "]";
}


int wmain()
{
	//mathTest();


	render();
	cout << "Done";
	string hi;
	getline(cin,hi );

	return 0;
}