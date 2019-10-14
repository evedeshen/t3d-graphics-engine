#pragma once
#include "Mesh.h"
namespace T3D {
	// ... class declaration ...

	class Tcylinder
		:public Mesh
	{
	public:
		Tcylinder(float radius, float height, int density);
		virtual ~Tcylinder();
		int become8(int a, int b);
		float beta;
	};
}