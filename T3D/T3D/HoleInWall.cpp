#include "HoleInWall.h"
#include "Math.h"

using namespace T3D;
//finished hole in wall 
HoleInWall::HoleInWall( Vector3 wallSize,float holeX,float holeY,float r, int density)
{
	initArrays(2 * density + 8,	// num vertices
		2 * density+8,		// num tris
		 density + 4);		// num quads
	float angle = 2 * Math::PI / density;
	float theta;
	for (int i = 0; i < density; i++)
	{
		theta = i * angle;
		float y = r * cos(theta)+holeY;
		float x = r * sin(theta)+holeX;
		// top vertex
		setVertex(i, x, y, wallSize.z);

		// bottom vertex
		setVertex(density + i, x, y, -wallSize.z);
	}

	setVertex(2 * density, wallSize.x, wallSize.y, wallSize.z);
	setVertex(2 * density+1, wallSize.x, -wallSize.y, wallSize.z);
	setVertex(2 * density+2, -wallSize.x, wallSize.y, wallSize.z);
	setVertex(2 * density+3, -wallSize.x, -wallSize.y, wallSize.z);
	setVertex(2 * density+4, wallSize.x, wallSize.y, -wallSize.z);
	setVertex(2 * density+5, wallSize.x, -wallSize.y, -wallSize.z);
	setVertex(2 * density+6, -wallSize.x, wallSize.y, -wallSize.z);
	setVertex(2 * density+7, -wallSize.x, -wallSize.y, -wallSize.z);
	//set the rectangle inside first 
	
	
	for (int i = 0; i < density; i++)
	{
		setFace(i,   // face id
			density + i,
			Become8(density + (i + 1) , density),
			 
			(i + 1) % density  ,
			i         
			
		);
	}
	
	
	//set triangle 
	
	
	for (int i = 0; i < density/4; i++)
	{
		setFace(i, i, i + 1, 2 * density); // top phase 1 1
		setFace(density + i, density + i + 1,density + i, 2*density + 4);//bottom phase 1 
		setFace(i + density / 4, i + density / 4, i + density / 4 + 1, 2 * density + 1);//top phase 2 1
		setFace(i + 5*density / 4,  i + 5*density / 4 + 1,i + 5*density / 4, 2 * density + 5);//bottom phase 2 
		setFace(i + 2*density / 4, i + 2*density / 4, i + 2*density / 4 + 1, 2 * density + 3);//top phase 3 
		setFace(i + 6*density / 4, i + 6*density / 4 + 1,i + 6*density / 4,  2 * density + 7);//bottom phase 3 
		setFace(i + 3*density / 4, i + 3*density / 4, (i + 3*density / 4 + 1)%density, 2 * density + 2);//top phase 4 
		setFace(i + 7*density / 4, Become8(i + 7*density / 4 + 1,density),i + 7*density / 4,  2 * density + 6);//bottom phase 4 

	}
	
	
	//then set 8 regular triabngle 
	setFace(2 * density , 2 * density + 2,0,2 * density  );
	setFace(2 * density +1,  2 * density,density/4, 2 * density + 1);
	setFace(2 * density +2, 2 * density+1,density/2,  2 * density + 3);
	setFace(2 * density +3, 2 * density+3,3*density/4,  2 * density + 2);

	setFace(2 * density +4, density, 2 * density+6, 2 * density + 4);
	setFace(2 * density +5, 5*density/4, 2 * density+4, 2 * density + 5);
	setFace(2 * density +6, 3*density/2, 2 * density+5, 2 * density + 7);
	setFace(2 * density +7, 7*density/4, 2 * density+7, 2 * density + 6);
	
	//set 4 regular rectangle 
	setFace(density, 2 * density + 2,2 * density,  2 * density + 4, 2 * density + 6);
	setFace(density+1, 2 * density,2 * density + 1,  2 * density + 5, 2 * density + 4);
	setFace(density+2, 2 * density+3,2 * density + 7,  2 * density + 5, 2 * density + 1);
	setFace(density+3, 2 * density+2,  2 * density + 6,2 * density + 7, 2 * density + 3);


	checkArrays();

	// Calculate normals
	calcNormals();
	
}


HoleInWall::~HoleInWall()
{
}

//mathmatically i need some easy line 
int HoleInWall::Become8(int n,int d){
	if (n == 2*d)
	{
		return d;
	}
	else
	{
		return n;
	}

}

