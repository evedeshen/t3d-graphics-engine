#include "HoleInWall.h"
#include "Math.h"

using namespace T3D;

HoleInWall::HoleInWall( Vector3 wallSize,float holeX,float holeY,float r, int density)
{
	initArrays(2 * density + 8,	// num vertices
		2 * density,		// num tris
		density+4);		// num quads
	float angle = 2 * Math::PI / density;
	float theta;
	for (int i = 0; i < density; i++)
	{
		theta = i * angle;
		float x = r * cos(theta)+holeX;
		float z = r * sin(theta)+holeY;
		// top vertex
		setVertex(i, x, wallSize.y, z);

		// bottom vertex
		setVertex(density + i, x, -wallSize.y, z);
	}

	setVertex(2 * density, wallSize.x, wallSize.y, wallSize.z);
	setVertex(2 * density+1, wallSize.x, -wallSize.y, wallSize.z);
	setVertex(2 * density+2, -wallSize.x, wallSize.y, wallSize.z);
	setVertex(2 * density+3, -wallSize.x, -wallSize.y, wallSize.z);
	setVertex(2 * density+4, wallSize.x, wallSize.y, -wallSize.z);
	setVertex(2 * density+5, wallSize.x, -wallSize.y, -wallSize.z);
	setVertex(2 * density+6, -wallSize.x, wallSize.y, -wallSize.z);
	setVertex(2 * density+7, -wallSize.x, -wallSize.y, -wallSize.z);
	//set the rectangle stuff first 
	for (int i = 0; i < density; i++)
	{
		setFace(i,   // face id
			density + (i + 1) % density,
			density + i, 
			i,         
			(i + 1) % density  
		);
	}
	//set triangle 
	for (int i = 0; i < density/4; i++)
	{

	}
}


HoleInWall::~HoleInWall()
{
}
