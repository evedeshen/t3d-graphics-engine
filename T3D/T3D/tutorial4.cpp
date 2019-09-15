#include "tutorial4.h"
#include "WinGLApplication.h"
#include "Camera.h"
#include "Cube.h"
#include "KeyboardController.h"
#include "cylinder.h"
#include "HoleInWall.h"
#include "Chip.h"
#include "ball.h"
using namespace T3D;

tutorial4::tutorial4()
{
}


tutorial4::~tutorial4()
{
}

bool tutorial4::init() {
	WinGLApplication::init();
	// more code to come...
	GameObject *lightObj = new GameObject(this);
	Light *light = new Light(Light::DIRECTIONAL);
	light->setAmbient(1, 1, 1);
	light->setDiffuse(1, 1, 1);
	light->setSpecular(1, 1, 1);
	lightObj->setLight(light);
	lightObj->getTransform()->
		setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
	lightObj->getTransform()->setParent(root);

	GameObject *camObj = new GameObject(this);
	renderer->camera =
		new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
	camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
	camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
	camObj->setCamera(renderer->camera);
	camObj->getTransform()->setParent(root);
	camObj->addComponent(new KeyboardController());
	Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
	green->setDiffuse(0, 1, 0, 1);

	Vector3 test;
	test.x = 1;
	test.y = 1;
	test.z = 0.1;
	GameObject *cube = new GameObject(this);
	cube->setMesh(new Chip(test, 0.2, 0.2, 0.3, 0.1, 40));
	//cube->setMesh(new HoleInWall(test,0.1,0.1,0.2,20));
	//cube->setMesh(new ball(1.0, 16));
	cube->setMaterial(green);
	cube->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	cube->getTransform()->setParent(root);
	cube->getTransform()->name = "Cube";

	return true;
}
