#pragma once

#include "Mesh.h"

namespace T3D {
	class ball
		:public Mesh
	{
	public:
		ball(float radius,int density);
		virtual ~ball();
	};
}

