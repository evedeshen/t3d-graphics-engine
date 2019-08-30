#pragma once
#include "Mesh.h"
namespace T3D {
	// ... class declaration ...

	class cylinder
		:public Mesh
	{
	public:
		cylinder(float radius,float height,int density);
		virtual ~cylinder();
	};
}
