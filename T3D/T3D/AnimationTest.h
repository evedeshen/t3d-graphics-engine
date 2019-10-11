#pragma once
#include "Task.h"
#include "T3DApplication.h"
#include "Animation.h"
namespace T3D {


	class AnimationTest
		:public Task
	{
	public:
		
		AnimationTest(T3DApplication *app) : Task(app) {
			elapsedTime = 0;
			Aobject = NULL;
			anima = NULL;
			start = false;
		}
		virtual ~AnimationTest();
		void update(float dt);
		static float smoothedLerp(float startPos, float endPos, float time, float accelerationTime);
		Transform *lamp;
		GameObject *Aobject;
		bool start;
		Animation* anima;
		float elapsedTime;
	};
}
