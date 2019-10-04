#include "cylinder.h"
#include "Math.h"
#define _USE_MATH_DEFINES
using namespace T3D;
namespace T3D {
	// ... class declaration ...


	cylinder::cylinder(float r,float h,int density)
	{
		initArrays(4*density+2,	// num vertices
			2*density,		// num tris
			density);		// num quads
		float angle = 2 * Math::PI / density;
		float theta;
		for (int i = 0; i < density; i++)
		{
			theta = i * angle;
			float x = r * cos(theta);
			float z = r * sin(theta);

			// top vertex
			setVertex(i, x, h, z);

			// bottom vertex
			setVertex(density + i, x, -h, z);

			//copy
			setVertex(2*density+i, x, h, z);
			setVertex(3*density + i, x, -h, z);

		}
		setVertex(4*density, 0, -h, 0);
		setVertex(4*density+1, 0, h, 0);


		for (int i = 0; i < density; i++)
		{
			setFace(i,   // face id
                 2*density+i,         // current top vertex
				become8(2*density+i+1,density),   // next top vertex (wrapping)
				become8(3*density + (i + 1) , density), // next bottom vertex (wrapping) 
				3*density + i        // current bottom vertex
			);
			setFace(i, (i + 1) % density,i, 2*density+1);
			setFace(density+i, density+i,density+(i + 1) % density,  2*density);
		}
		checkArrays();

		// Calculate normals
		calcNormals();

	}


	cylinder::~cylinder()
	{
	}

	int cylinder::become8(int t,int d) {
		if (t%d == 0)
		{
			return t - d;
		}
		else
		{
			return t;
		}
	}

}