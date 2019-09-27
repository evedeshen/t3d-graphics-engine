#include "dog.h"
#include "Camera.h"
#include "Cube.h"
#include "KeyboardController.h"
#include "cylinder.h"
#include "AnimationTest.h"
#include "Animation.h"

using namespace T3D;
dog::dog()
{
}


dog::~dog()
{
}

bool dog::init() {
	WinGLApplication::init();

	GameObject *legJoint1 = new GameObject(this);
	GameObject *legJoint2 = new GameObject(this);
	GameObject *legJoint3 = new GameObject(this);
	GameObject *legJoint4 = new GameObject(this);
	GameObject *headJoint = new GameObject(this);
	GameObject *tailJoint = new GameObject(this);
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
	Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
	grey->setDiffuse(0.8, 0.8, 0.9, 1);

	GameObject *body = new GameObject(this);
	body->setMesh(new cylinder(1, 4, 20));
	body->setMaterial(grey);
	body->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	body->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 2)));
	body->getTransform()->setParent(root);
	body->getTransform()->name = "body";

	//let's works on legs 
	GameObject *leg1 = new GameObject(this);
	leg1->setMesh(new cylinder(0.3, 1.3, 20));
	leg1->setMaterial(green);
	leg1->getTransform()->setLocalPosition(Vector3(-1.3,0,0));
	leg1->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg1->getTransform()->setParent(legJoint1->getTransform());
	leg1->getTransform()->name = "leg1";

	GameObject *leg2 = new GameObject(this);
	leg2->setMesh(new cylinder(0.3, 1.3, 20));
	leg2->setMaterial(green);
	leg2->getTransform()->setLocalPosition(Vector3(-1.3, 0, 0));
	leg2->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg2->getTransform()->setParent(legJoint2->getTransform());
	leg2->getTransform()->name = "leg2";

	GameObject *leg3 = new GameObject(this);
	leg3->setMesh(new cylinder(0.3, 1.3, 20));
	leg3->setMaterial(green);
	leg3->getTransform()->setLocalPosition(Vector3(-1.3,0,0));
	leg3->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg3->getTransform()->setParent(legJoint3->getTransform());
	leg3->getTransform()->name = "leg3";

	GameObject *leg4 = new GameObject(this);
	leg4->setMesh(new cylinder(0.3, 1.3, 20));
	leg4->setMaterial(green);
	leg4->getTransform()->setLocalPosition(Vector3(-1.3, 0, 0));
	leg4->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg4->getTransform()->setParent(legJoint4->getTransform());
	leg4->getTransform()->name = "leg4";

	legJoint1->getTransform()->setLocalPosition(Vector3(0.1, 2, -0.7));
	legJoint1->getTransform()->setParent(body->getTransform());
	legJoint1->getTransform()->name = "legJoint1";

	legJoint2->getTransform()->setLocalPosition(Vector3(0.1, 2, 0.7));
	legJoint2->getTransform()->setParent(body->getTransform());
	legJoint2->getTransform()->name = "legJoint2";

	legJoint3->getTransform()->setLocalPosition(Vector3(0.1, -2, 0.7));
	legJoint3->getTransform()->setParent(body->getTransform());
	legJoint3->getTransform()->name = "legJoint3";

	legJoint4->getTransform()->setLocalPosition(Vector3(0.1, -2, -0.7));
	legJoint4->getTransform()->setParent(body->getTransform());
	legJoint4->getTransform()->name = "legJoint4";


	//rip my dog, so ugly lol 
	legJoint1->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 4)));
	legJoint2->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 4)));
	legJoint3->getTransform()->setLocalRotation(Quaternion(Vector3(0 ,0, Math::PI / 4)));
	legJoint4->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 4)));

	//tail time 
	GameObject *tail = new GameObject(this);
    tail->setMesh(new cylinder(0.1, 0.5, 20));
	tail->setMaterial(green);
	tail->getTransform()->setLocalPosition(Vector3(0, -0.5, 0));
	tail->getTransform()->setParent(tailJoint->getTransform());
	tail->getTransform()->name = "tail";

	tailJoint->getTransform()->setLocalPosition(Vector3(0, -3.9, 0));
	tailJoint->getTransform()->setParent(body->getTransform());
	tailJoint->getTransform()->name = "tailJoint";

	tailJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 4)));
	//the final part, which is head
	//prepare a ball object but your ball object is not working so i choose to use an ugly cube object 
	GameObject *head = new GameObject(this);
	head->setMesh(new Cube(1.0));
	head->setMaterial(green);
	head->getTransform()->setLocalPosition(Vector3(0, 1, 0));
	head->getTransform()->setParent(headJoint->getTransform());
	head->getTransform()->name = "head";

	headJoint->getTransform()->setLocalPosition(Vector3(0, 4, 0));
	headJoint->getTransform()->setParent(body->getTransform());
	headJoint->getTransform()->name = "headJoint";
	/*
	AnimationTest *animTask = new AnimationTest(this);
	animTask->lamp = body->getTransform();
	addTask(animTask);
	*/

	Animation *anim = new Animation(10.0);
	body->addComponent(anim);
	anim->addKey("legJoint1", 0, Quaternion(Vector3(0, 0, -Math::PI / 4)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 5.0, Quaternion(Vector3(0, 0, Math::PI / 4)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 10.0, Quaternion(Vector3(0, 0, -Math::PI / 4)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint2", 0, Quaternion(Vector3(0, 0, -Math::PI / 4)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 5.0, Quaternion(Vector3(0, 0, Math::PI / 4)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 10.0, Quaternion(Vector3(0, 0, -Math::PI / 4)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint3", 0, Quaternion(Vector3(0, 0, Math::PI / 4)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 5.0, Quaternion(Vector3(0, 0, -Math::PI / 4)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 10.0, Quaternion(Vector3(0, 0, Math::PI / 4)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint4", 0, Quaternion(Vector3(0, 0, Math::PI / 4)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 5.0, Quaternion(Vector3(0, 0, -Math::PI / 4)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 10.0, Quaternion(Vector3(0, 0, Math::PI / 4)), Vector3(0.1, -2, -0.7));
	anim->loop(true);
	anim->play();

	return true;
}