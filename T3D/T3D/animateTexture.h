#pragma once
#include "Task.h"
namespace T3D {
	class animateTexture
		:public Task
	{
	public: 
		animateTexture(T3DApplication* app) :Task(app) {
			elapsedTime =0;
			Aobject = NULL;
			m = NULL;
			time = NULL;
		}
		virtual ~animateTexture();
		void update(float dt);


		GameObject* Aobject;
		float elapsedTime;
		Material** m;
		int* time;
	};
}

