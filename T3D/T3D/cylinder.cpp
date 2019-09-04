#include "cylinder.h"
#include "Math.h"
#define _USE_MATH_DEFINES
using namespace T3D;
namespace T3D {
	// ... class declaration ...


	cylinder::cylinder(float r,float h,int density)
	{
		initArrays(2*density+2,	// num vertices
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

		}
		setVertex(2*density, 0, -h, 0);
		setVertex(2*density+1, 0, h, 0);


		for (int i = 0; i < density; i++)
		{
			setFace(i,   // face id
                 i,         // current top vertex
				(i + 1) % density,   // next top vertex (wrapping)
				density + (i + 1) % density, // next bottom vertex (wrapping) 
				density + i        // current bottom vertex
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

}