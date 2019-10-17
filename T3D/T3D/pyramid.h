#pragma once
#include "mesh.h"

namespace T3D {
	class pyramid
		: public Mesh
	{
	public:
		pyramid(float size, float height);
		virtual ~pyramid();
	};
}

