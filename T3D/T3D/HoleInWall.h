#pragma once
#include "Mesh.h"
namespace T3D {
	class HoleInWall
		: public Mesh 
	{
	public:
		HoleInWall(
			Vector3 wallSize, // length, height, thickness of wall
			float holeX, // the x position of the centre of the hole
			float holeY, // the y position of the centre of the hole
			float radius, // the radius of the hole
			int density // the density of the hole);
		);
		int Become8(int number,int d);
		virtual ~HoleInWall();
	};
}
