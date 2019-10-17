#include "tutuorial5.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Sphere.h"
#include "GLShader.h"
#include "pyramid.h"
using namespace T3D;

tutuorial5::tutuorial5()
{
}


tutuorial5::~tutuorial5()
{
}

bool tutuorial5::init(){
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
	
	Material *assignmentGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
	assignmentGreen->setDiffuse(0.0, 0.6, 0, 1);
	assignmentGreen->setShininess(30);

	

	GLShader *phongShader = new GLShader("Resources/assignmentVert.shader", "Resources/assignmentFrag.shader");
	phongShader->compileShader();
	assignmentGreen->setShader(phongShader);

	GameObject *ball1 = new GameObject(this);
	ball1->setMesh(new pyramid(2, 1));
	ball1->setMaterial(assignmentGreen);
	ball1->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	ball1->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));
	ball1->getTransform()->setParent(root);

	GameObject *ball2 = new GameObject(this);
	ball2->setMesh(new pyramid(2, 1));
	ball2->setMaterial(assignmentGreen);
	ball2->getTransform()->setLocalPosition(Vector3(1.5, 1.5, 1.5));
	ball2->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));
	ball2->getTransform()->setParent(root);

	GameObject *ball3 = new GameObject(this);
	ball3->setMesh(new pyramid(2, 1));
	ball3->setMaterial(assignmentGreen);
	ball3->getTransform()->setLocalPosition(Vector3(-1.5, -1.5, -1.5));
	ball3->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));
	ball3->getTransform()->setParent(root);
	

	return true;
}

