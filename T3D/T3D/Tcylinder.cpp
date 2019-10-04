#include "Tcylinder.h"
#include "Math.h"

using namespace T3D;
Tcylinder::Tcylinder(float r, float h, int density)
{
	initArrays(2 * density + 4,	// num vertices
		2 * density,		// num tris
		density);		// num quads
	float angle = 2 * Math::PI / density;
	float theta;
	for (int i = 0; i <= density; i++)
	{
		theta = i * angle;
		float x = r * cos(theta);
		float z = r * sin(theta);

		// top vertex
		setVertex(i, x, h, z);
		setUV(i, float(i) / density, 0);
		// bottom vertex
		setVertex(density + i+1, x, -h, z);
		setUV(density + 1 + i, float(i) / density, 0.6);

	}
	setVertex(2 * density+2, 0, -h, 0);
	setVertex(2 * density + 3, 0, h, 0);


	for (int i = 0; i < density; i++)
	{
		setFace(i,   // face id
			i,         // current top vertex
			(i + 1) ,   // next top vertex (wrapping)
			density +1+ (i + 1) , // next bottom vertex (wrapping) 
			density + i+1        // current bottom vertex
		);
		
		setFace(i, (i + 1) , i, 2 * density + 3);

		setFace(density + i, density + i+1, density+1 + (i + 1) , 2 * density+2);
	}
	checkArrays();

	// Calculate normals
	calcNormals();

}


Tcylinder::~Tcylinder()
{
}
