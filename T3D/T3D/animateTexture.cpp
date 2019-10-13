#include "animateTexture.h"
#include "T3DApplication.h"
#include "Task.h"

using namespace T3D;

animateTexture::~animateTexture()
{
}

void animateTexture::update(float dt)
{
	elapsedTime += dt;
	for (int i = 0; i < sizeof(time); i++)
	{
		if (elapsedTime>time[i])
		{
			Aobject->setStaticMaterial(m[i], Aobject);	
		}
	}

}
