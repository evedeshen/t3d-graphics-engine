#include "tutuorial5.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Sphere.h"
#include "GLShader.h"
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
	Material *fixedGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
	fixedGreen->setDiffuse(0.0, 0.6, 0, 1);
	fixedGreen->setShininess(20);
	Material *gouraudGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
	gouraudGreen->setDiffuse(0.0, 0.6, 0, 1);
	gouraudGreen->setShininess(20);
	Material *phongGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
	phongGreen->setDiffuse(0.0, 0.6, 0, 1);
	phongGreen->setShininess(30);
	GLShader *gouraudShader = new GLShader("Resources/vspecular.shader", "Resources/frag.shader");
	gouraudShader->compileShader();
	gouraudGreen->setShader(gouraudShader);

	GLShader *phongShader = new GLShader("Resources/phongVert.shader", "Resources/phongFrag.shader");
	phongShader->compileShader();
	phongGreen->setShader(phongShader);
	GameObject *ball1 = new GameObject(this);
	ball1->setMesh(new Sphere(1, 32));
	ball1->setMaterial(fixedGreen);
	ball1->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	ball1->getTransform()->setParent(root);
	GameObject *ball2 = new GameObject(this);
	ball2->setMesh(new Sphere(1, 32));
	ball2->setMaterial(gouraudGreen);
	ball2->getTransform()->setLocalPosition(Vector3(1.5, 1.5, 1.5));
	ball2->getTransform()->setParent(root);
	GameObject *ball3 = new GameObject(this);
	ball3->setMesh(new Sphere(1, 32));
	ball3->setMaterial(phongGreen);
	ball3->getTransform()->setLocalPosition(Vector3(-1.5, -1.5, -1.5));
	ball3->getTransform()->setParent(root);
	

	return true;
}

