#include "Tcylinder.h"
#include "Math.h"

using namespace T3D;
Tcylinder::Tcylinder(float r, float h, int density)
{
	initArrays(4 * density + 6,	// num vertices
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

		setVertex(2 * density +i+2, x, h, z);
		setUV(2 * density + i + 2, 0.25 + 0.25*cos(theta), 0.25 + 0.25*sin(theta));
		setVertex(3 * density + i+3, x, -h, z);
		setUV(3 * density + i + 3, 0.5 + 0.25*cos(theta), 0.5 + 0.25*sin(theta));

	}
	setVertex(4 * density+4, 0, -h, 0);
	setUV(4 * density + 4, 0.5, 0.5);
	setVertex(4 * density + 5, 0, h, 0);

	setUV(4 * density + 5, 0.25, 0.25);

	for (int i = 0; i < density; i++)
	{
		setFace(i,   // face id
			 i,         // current top vertex
			i + 1,   // next top vertex (wrapping)
			density +1+ (i + 1), // next bottom vertex (wrapping) 
			density + i+1        // current bottom vertex
		);
		setFace(i, 2*density+i + 1+2 , 2*density+i+2, 4 * density + 5);
		setFace(density + i, 3*density + i+3, 3*density + (i + 1)+3, 4 * density+4);
	}
	checkArrays();

	// Calculate normals
	calcNormals();

}


Tcylinder::~Tcylinder()
{
}

int Tcylinder::become8(int t, int d) {
	if (t%d == 0)
	{
		return t - d;
	}
	else
	{
		return t;
	}
}
