#include "Chip.h"
#include "Math.h"


using namespace T3D;
Chip::Chip(Vector3 wallSize, float chipX, float chipY, float r, float depth, int density)
{
	float sn= density / 4.0;//number of slope 
	initArrays((sn+1)*density + 9 ,	// num vertices
		2 * density + 4,		// num tris
		(sn)*density + 5);		// num quads
	float angle = 2 * Math::PI / density;
	float theta;
	
	for (int j = 0; j < sn + 1; j++)
	{
		for (int i = 0; i < density; i++)
		{
        theta = i * angle;
		float y = (1-0.25*j/sn)*r * cos(theta) + chipY;
		float x = (1 - 0.25*j / sn)*r * sin(theta) + chipX;
		float z = wallSize.z - j / sn * depth;
		setVertex(i+density*j, x, y, z);
		}				
	}
	setVertex((sn+1) * density, wallSize.x, wallSize.y, wallSize.z);
	setVertex((sn + 1) * density + 1, wallSize.x, -wallSize.y, wallSize.z);
	setVertex((sn + 1) * density + 2, -wallSize.x, wallSize.y, wallSize.z);
	setVertex((sn + 1) * density + 3, -wallSize.x, -wallSize.y, wallSize.z);
	setVertex((sn + 1)* density + 4, wallSize.x, wallSize.y, -wallSize.z);
	setVertex((sn + 1) * density + 5, wallSize.x, -wallSize.y, -wallSize.z);
	setVertex((sn + 1) * density + 6, -wallSize.x, wallSize.y, -wallSize.z);
	setVertex((sn + 1) * density + 7, -wallSize.x, -wallSize.y, -wallSize.z);
	setVertex((sn + 1) * density + 8, chipX, chipY, wallSize.z - depth);
	
	for (int i = 0; i < density; i++)
	{
		setFace(i,   // face id
			(sn + 1)*density + i,
			Become8((sn + 1)*density + (i + 1), density),
			(i + 1) % density,
			i
		);
	}
	
	//don't need to change 
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
		setFace(density + i, Become8((sn + 1)*density+i+1,density), (sn + 1)*density+i, (sn + 1) * density + 8);
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

//some mathmatical function 
int Chip::Become8(int n, int d) {
	if (n %d == 0)
	{
		return n-d;
	}
	else
	{
		return n;
	}

}