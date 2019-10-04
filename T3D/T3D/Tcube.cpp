#include "Tcube.h"
namespace T3D
{
	Tcube::Tcube(float size)
	{
		// Init vertex and index arrays
		initArrays(4 * 6,	// num vertices
			0,		// num tris
			6);		// num quads

 // Set vertices

		int pos = 0;
		int uvpos = 0;
		//front
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, -size, size, -size);

		setUV(uvpos++, 0, 0);
		setUV(uvpos++, 0.5, 0);
		setUV(uvpos++, 0.5, 0.5);
		setUV(uvpos++, 0, 0.5);
		//back
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, -size, size, size);

		setUV(uvpos++, 0.5, 0);
		setUV(uvpos++, 1, 0);
		setUV(uvpos++, 1, 0.5);
		setUV(uvpos++, 0.5, 0.5);
		//left
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, -size, -size, size);

		setUV(uvpos++, 0, 0.5);
		setUV(uvpos++, 0.5, 0.5);
		setUV(uvpos++, 0.5, 1);
		setUV(uvpos++, 0, 1);
		//right
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, -size, size);

		
		
		setUV(uvpos++, 0.5, 1);
		setUV(uvpos++, 0.5, 0.5);
		setUV(uvpos++,1, 0.5);
		setUV(uvpos++, 1, 1);
		//bottom
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);

		setUV(uvpos++, 0, 0);
		setUV(uvpos++, 0.5, 0);
		setUV(uvpos++, 0.5, 0.5);
		setUV(uvpos++, 0, 0.5);
		//top
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, size, -size);

		setUV(uvpos++, 0, 0);
		setUV(uvpos++, 0.5, 0);
		setUV(uvpos++, 0.5, 0.5);
		setUV(uvpos++, 0, 0.5);

		// Build quads
		pos = 0;
		//front
		setFace(pos++, 3, 2, 1, 0);
		//back
		setFace(pos++, 4, 5, 6, 7);
		//left
		setFace(pos++, 11, 10, 9, 8);
		//right
		setFace(pos++, 12, 13, 14, 15);
		//bottom
		setFace(pos++, 19, 18, 17, 16);
		//top
		setFace(pos++, 20, 21, 22, 23);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}
}