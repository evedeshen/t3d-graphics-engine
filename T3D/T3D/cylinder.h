#pragma once
#include "Mesh.h"
namespace T3D {
	// ... class declaration ...

	class cylinder
		:public Mesh
	{
	public:
		cylinder(int radius,int height,int density);
		virtual ~cylinder();
	};
}
