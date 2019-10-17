#include "pyramid.h"

using namespace T3D;

pyramid::pyramid(float size, float height)
{

	initArrays(12,	// num vertices
		4,		// num tris
		0);
	int pos = 0;
	setVertex(pos++, 0, 0, height);
	setVertex(pos++, size, -size / 2, -height);
	setVertex(pos++, 0, size, -height);

	setVertex(pos++, 0, 0, height);	
	setVertex(pos++, 0,size ,  -height);
    setVertex(pos++, -size, -size / 2, -height);

	setVertex(pos++, 0, 0, height);
	setVertex(pos++, -size, -size / 2, -height);
	setVertex(pos++, size, -size / 2, -height);

	setVertex(pos++, -size, -size / 2, -height);
	setVertex(pos++, 0,size ,  -height);
    setVertex(pos++, size, -size / 2, -height);

	pos = 0;
	setFace(pos++, 0, 1, 2);
    setFace(pos++, 3, 4, 5);
	setFace(pos++, 6, 7, 8);
	setFace(pos++, 9, 10, 11);
	
	checkArrays();
	calcNormals();

}


pyramid::~pyramid()
{
}
