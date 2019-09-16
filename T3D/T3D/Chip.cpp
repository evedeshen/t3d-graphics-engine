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
	float phi;//use for sphere coordination , the curve is hard in XYZ coordination
	
	for (int j = 0; j < sn + 1; j++)
	{
		theta = Math::PI /2-(0.5*Math::PI - acos(depth/r))*(j/sn);
		for (int i = 0; i < density; i++)
		{
        phi = i * angle;
		
		//theta = 1.0 / 6 * Math::PI*(j / (sn));
		//float y = curveIndexGenerator(j,sn) *r * cos(theta) + chipY; //its not like a curve but if change 0.4 into some specific math funciton it will be allright 
		//float x = curveIndexGenerator(j, sn)*r * sin(theta) + chipX;
        float x = (sin(theta) * sin(phi))*r + chipX;//its most likely use some power series method like 1/2 ^n or something, if i have time i will fill this part 
		float y = (sin(theta) * cos(phi))*r + chipY;
		float z = wallSize.z-(cos(theta))*r;


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
	setVertex((sn + 1) * density + 8, chipX, chipY, wallSize.z-depth);
	

	// this part finished first and works well 
	for (int j = 1; j < sn+1; j++)
	{
		for (int i = 0; i < density; i++)
		{
			setFace(i + (j - 1)*density,   // face id
				(j)*density + i,
				Become8((j)*density + (i + 1), density),
				Become8((j-1)*density + (i + 1), density),
				i + (j-1) * density
			);
		}
	}

	
	
	//don't need to change 
	for (int i = 0; i < density / 4; i++)
	{
		setFace(i, i, i + 1, (sn + 1) * density); // top phase 1 1
		//setFace(density + i, density + i + 1, density + i, 2 * density + 4);//bottom phase 1 
		setFace(i + density / 4, i + density / 4, i + density / 4 + 1, (sn + 1) * density + 1);//top phase 2 1
		//setFace(i + 5 * density / 4, i + 5 * density / 4 + 1, i + 5 * density / 4, 2 * density + 5);//bottom phase 2 
		setFace(i + 2 * density / 4, i + 2 * density / 4, i + 2 * density / 4 + 1, (sn + 1) * density + 3);//top phase 3 
		//setFace(i + 6 * density / 4, i + 6 * density / 4 + 1, i + 6 * density / 4, 2 * density + 7);//bottom phase 3 
		setFace(i + 3 * density / 4, i + 3 * density / 4, (i + 3 * density / 4 + 1) % density, (sn + 1) * density + 2);//top phase 4 
		//setFace(i + 7 * density / 4, Become8(i + 7 * density / 4 + 1, density), i + 7 * density / 4, 2 * density + 6);//bottom phase 4 

	}
	

	
	for (int i = 0; i < density; i++)
	{
		setFace(density + i, Become8((sn)*density+i+1,density), (sn )*density+i, (sn + 1) * density + 8);
	}
	
	

	//set 4 regular tri
	setFace(2 * density, (sn + 1) * density + 2, 0, (sn + 1) * density);
	setFace(2 * density + 1, (sn + 1) * density, density / 4, (sn + 1) * density + 1);
	setFace(2 * density + 2, (sn + 1) * density + 1, density / 2, (sn + 1) * density + 3);
	setFace(2 * density + 3, (sn + 1) * density + 3, 3 * density / 4, (sn + 1) * density + 2);
	//5 regular rectangle 
	
	setFace(sn*density, (sn + 1) * density + 2, (sn + 1) * density, (sn + 1) * density + 4, (sn + 1) * density + 6);
	setFace(sn*density + 1, (sn + 1) * density, (sn + 1) * density + 1, (sn + 1) * density + 5, (sn + 1) * density + 4);
	setFace(sn*density + 2, (sn + 1) * density + 3, (sn + 1) * density + 7, (sn + 1) * density + 5, (sn + 1) * density + 1);
	setFace(sn*density + 3, (sn + 1) * density + 2, (sn + 1) * density + 6, (sn + 1) * density + 7, (sn + 1) * density + 3);
	setFace(sn*density + 4, (sn + 1) * density + 4, (sn + 1) * density + 5, (sn + 1) * density + 7, (sn + 1) * density + 6);
	
	checkArrays();
	
	// Calculate normals
	calcNormals();


}


Chip::~Chip()
{
}

//some mathmatical function 
//this function is used for in loop, a substitution of %
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

//not working as i wish, just leave it here 
float T3D::Chip::curveIndexGenerator(int j, int sn)
{
	if (j == 0)
	{
		return 1.0;
	}
	else {
		return 1.0 - 0.4*pow(1 / 2, sn - j);
	}
}

