#pragma once
#include "Mesh.h"
namespace T3D {
	class Chip
		: public Mesh
	{
	public:
		Chip(Vector3 wallSize, float chipX, float chipY,float r, float depth,int density);
		int Become8(int number, int d);
		virtual ~Chip();

	};
}