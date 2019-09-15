#include "ball.h"
#include "Math.h"


using namespace T3D;
ball::ball(float radius, int density)
{
	// VERTICES
	numVerts = density * (density - 1) + 2;
	vertices = new float[numVerts * 3];
	float dPhi = Math::PI / density;
	float dTheta = Math::TWO_PI / density;

	int pos = 0;
	for (int i = 1; i<density; i++) {
		float phi = i * dPhi;
		float r = sin(phi)*radius;
		float h = cos(phi)*radius;

		// note that this is same as cylinder code
		for (int j = 0; j<density; j++) {
			float theta = j * dTheta;
			float x = r * cos(theta);
			float z = r * sin(theta);
			setVertex((i - 1)*density + j, x, h, z);
		}
	}
	setVertex(density*(density - 1), 0, -radius, 0);
	setVertex(density*(density - 1) + 1, 0, radius, 0);
	//...
	// FACES
	int d = density;
	numTris = d * 2 + d * (d) * 2;
	triIndices = new unsigned int[numTris * 3];

	int face = 0;

	//top and bottom
	for (int j = 0; j<d; j++) {
		setFace(face++, d*(d - 1) + 1, (j + 1) % d, j);
		setFace(face++, d*(d - 1), d*(d - 2) + j, d*(d - 2) + (j + 1) % d);
	}

	//rest
	for (int i = 1; i<d - 1; i++) {
		for (int j = 0; j<d; j++) {
			setFace(face++, (i - 1)*d + j, (i - 1)*d + (j + 1) % density, i*d + j);
			setFace(face++,
				(i - 1)*d + (j + 1) % d, i*d + (j + 1) % density, i*d + j);
		}
	}
	// normals, colors, etc.
	// ... later
	checkArrays();

	// Calculate normals
	calcNormals();

}


ball::~ball()
{
}
