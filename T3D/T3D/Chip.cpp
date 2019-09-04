#include "Chip.h"
#include "Math.h"


using namespace T3D;
Chip::Chip(Vector3 wallSize, float chipX, float chipY, float r, float depth, int density)
{
	initArrays(2 * density + 9,	// num vertices
		2 * density + 4,		// num tris
		density + 5);		// num quads
	int rr = 3 / 4 * r;
	float angle = 2 * Math::PI / density;
	float theta;
	for (int i = 0; i < density; i++)
	{
		theta = i * angle;
		float y = r * cos(theta) + chipY;
		float x = r * sin(theta) + chipX;
		// top vertex
		setVertex(i, x, y, wallSize.z);

		float yy = rr * cos(theta) + chipY;
		float xx = rr * sin(theta) + chipX;
		//inside vertex 
		setVertex(density + i, xx, yy, wallSize.z-depth);
	}
	setVertex(2 * density, wallSize.x, wallSize.y, wallSize.z);
	setVertex(2 * density + 1, wallSize.x, -wallSize.y, wallSize.z);
	setVertex(2 * density + 2, -wallSize.x, wallSize.y, wallSize.z);
	setVertex(2 * density + 3, -wallSize.x, -wallSize.y, wallSize.z);
	setVertex(2 * density + 4, wallSize.x, wallSize.y, -wallSize.z);
	setVertex(2 * density + 5, wallSize.x, -wallSize.y, -wallSize.z);
	setVertex(2 * density + 6, -wallSize.x, wallSize.y, -wallSize.z);
	setVertex(2 * density + 7, -wallSize.x, -wallSize.y, -wallSize.z);
	setVertex(2 * density + 8, chipX, chipY, wallSize.z - depth);
	
	for (int i = 0; i < density; i++)
	{
		setFace(i,   // face id
			density + i,
			Become8(density + (i + 1), density),

			(i + 1) % density,
			i

		);
	}
	
	for (int i = 0; i < density / 4; i++)
	{
		setFace(i, i, i + 1, 2 * density); // top phase 1 1
		//setFace(density + i, density + i + 1, density + i, 2 * density + 4);//bottom phase 1 
		setFace(i + density / 4, i + density / 4, i + density / 4 + 1, 2 * density + 1);//top phase 2 1
		//setFace(i + 5 * density / 4, i + 5 * density / 4 + 1, i + 5 * density / 4, 2 * density + 5);//bottom phase 2 
		setFace(i + 2 * density / 4, i + 2 * density / 4, i + 2 * density / 4 + 1, 2 * density + 3);//top phase 3 
		//setFace(i + 6 * density / 4, i + 6 * density / 4 + 1, i + 6 * density / 4, 2 * density + 7);//bottom phase 3 
		setFace(i + 3 * density / 4, i + 3 * density / 4, (i + 3 * density / 4 + 1) % density, 2 * density + 2);//top phase 4 
		//setFace(i + 7 * density / 4, Become8(i + 7 * density / 4 + 1, density), i + 7 * density / 4, 2 * density + 6);//bottom phase 4 

	}


	
	for (int i = 0; i < density; i++)
	{
		setFace(density + i, Become8(density+i+1,density),density+i,  2 * density + 8);
	}
	
	

	//set 4 regular tri
	setFace(2 * density, 2 * density + 2, 0, 2 * density);
	setFace(2 * density + 1, 2 * density, density / 4, 2 * density + 1);
	setFace(2 * density + 2, 2 * density + 1, density / 2, 2 * density + 3);
	setFace(2 * density + 3, 2 * density + 3, 3 * density / 4, 2 * density + 2);
	//5 regular rectangle 
	
	setFace(density, 2 * density + 2, 2 * density, 2 * density + 4, 2 * density + 6);
	setFace(density + 1, 2 * density, 2 * density + 1, 2 * density + 5, 2 * density + 4);
	setFace(density + 2, 2 * density + 3, 2 * density + 7, 2 * density + 5, 2 * density + 1);
	setFace(density + 3, 2 * density + 2, 2 * density + 6, 2 * density + 7, 2 * density + 3);
	setFace(density + 4, 2 * density + 4, 2 * density + 5, 2 * density + 7, 2 * density + 6);
	
	checkArrays();

	// Calculate normals
	calcNormals();


}


Chip::~Chip()
{
}

int Chip::Become8(int n, int d) {
	if (n == 2 * d)
	{
		return d;
	}
	else
	{
		return n;
	}

}