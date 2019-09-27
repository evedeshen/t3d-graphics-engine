#pragma once
#include "Task.h"
#include "T3DApplication.h"
namespace T3D {


	class AnimationTest
		:public Task
	{
	public:
		
		AnimationTest(T3DApplication *app) : Task(app) {
			elapsedTime = 0;
			lamp = NULL;
		}
		virtual ~AnimationTest();
		void update(float dt);
		static float smoothedLerp(float startPos, float endPos, float time, float accelerationTime);
		Transform *lamp;
		float elapsedTime;
	};
}
