#include "AnimationTest.h"
#include "T3DApplication.h"
#include "Task.h"

using namespace T3D;
	


	AnimationTest::~AnimationTest()
	{
	}

	void AnimationTest::update(float dt) {
		if (start == false)
		{
        anima->play();
        start = true;
		tempUV = Bobject->getMesh()->getUVs();
		
		}

		
		 //get the UVs
		elapsedTime += dt;
		
		if (elapsedTime > 15.0) {
			if (elapsedTime<22.5)
			{
              Aobject->setVisible(true);
			  //Bobject->setMaterial(m);
			 
			}
			else
			{
			  Aobject->setVisible(false);
			}
		}

		/*
		if (elapsedTime<30)
		{
			for (int i = 0; i < Bobject->getMesh()->getNumVerts(); i++)
			{
				//tempUV[2 * i] = backToOne(tempUV[2 * i] + 0.002*elapsedTime);
				Bobject->getMesh()->setUV(i, backToOne((0.002 )+tempUV[2 * i]),  tempUV[2 * i + 1]);
			}
		}
		
		*/






		/*if (elapsedTime<5)
		{
            lamp->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), elapsedTime / 5));
		}
		else if (elapsedTime <10)
		{
            lamp->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(1, 1, 0), (elapsedTime / 5) -1));
		}
		else
		{
			//elapsedTime = 0;
		}
		*/
		
	}

	float AnimationTest::smoothedLerp(float startPos, float endPos, float time, float accelerationTime) {
		float dist = endPos - startPos;
		float acceleration = dist / (accelerationTime*(1 - accelerationTime));
		float velocity = acceleration * accelerationTime;

		
		if (time<0)
		{
			return startPos;
		}
		else if (time < accelerationTime) {
			return startPos + 0.5*acceleration*time*time;
		}
		else if (time <  1 - accelerationTime)
		{
			return startPos + 0.5 * acceleration * accelerationTime * accelerationTime + velocity * (time - accelerationTime);
		}
		else if (time <= 1)
		{
			return startPos + 0.5 * acceleration * accelerationTime * accelerationTime + velocity * (1 - 2 * accelerationTime) + velocity * (time - 1 + accelerationTime) - 0.5 * acceleration * (time - 1 + accelerationTime) * (time - 1 + accelerationTime);
		}

		return endPos;
	}

	float T3D::AnimationTest::backToOne(float a)
	{
		if (a>=1.0)
		{
			return a - 1.0;
		}
		return a;
	}

