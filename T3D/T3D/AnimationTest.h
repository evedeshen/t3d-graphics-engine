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
			Bobject = NULL;
			anima = NULL;
			start = false;
			m = NULL;
			tempUV = NULL;
		}
		virtual ~AnimationTest();
		void update(float dt);
		static float smoothedLerp(float startPos, float endPos, float time, float accelerationTime);
		Material* m;
		GameObject *Aobject;
		GameObject* Bobject;
		bool start;
		Animation* anima;
		float elapsedTime;
		float* tempUV;
	};
}
