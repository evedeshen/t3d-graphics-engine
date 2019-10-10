#pragma once
#include "WinGLApplication.h"
#include "Sweep.h"
namespace T3D {
	class dog
		:public WinGLApplication
	{
	public:
		dog();
		bool init();
		virtual ~dog();
		void legSweep();
		vector<Transform> path;
		//start to build sweep 
		SweepPath sp;
		Transform t;
		vector<Vector3> points;
	};

}

