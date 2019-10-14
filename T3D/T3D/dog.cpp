#include "dog.h"
#include "Camera.h"
#include "Cube.h"
#include "KeyboardController.h"
#include "cylinder.h"
#include "AnimationTest.h"
#include "Animation.h"
#include "Tcylinder.h"
#include "animateTexture.h"
#include <thread>
using namespace T3D;
dog::dog()
{
}


dog::~dog()
{
}

void T3D::dog::legSweep()
{




	// Make a profile
	
	points.push_back(Vector3(1, 0, 0.));
	points.push_back(Vector3(0.92, 0.38, 0));
	points.push_back(Vector3(0.7, 0.7, 0));
	points.push_back(Vector3(0.38, 0.92, 0));
	points.push_back(Vector3(0, 1, 0));
	points.push_back(Vector3(-0.38, 0.92, 0));
	points.push_back(Vector3(-0.7, 0.7, 0));
	points.push_back(Vector3(-0.92, 0.38, 0));
	points.push_back(Vector3(-1, 0, 0));
	points.push_back(Vector3(-0.92, -0.38, 0));
	points.push_back(Vector3(-0.7, -0.7, 0));
	points.push_back(Vector3(-0.38, -0.92, 0));
	points.push_back(Vector3(0, -1, 0));
	points.push_back(Vector3(0.38, -0.92, 0));
	points.push_back(Vector3(0.7, -0.7, 0));
	points.push_back(Vector3(0.92, -0.38, 0));


	t.setLocalPosition(Vector3(0, 0, 0));
	t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
	t.setLocalScale(Vector3(0, 0, 0));
	sp.addTransform(t);

	t.setLocalPosition(Vector3(0, -0.5, 0));
	t.setLocalRotation(Quaternion(Vector3(Math::PI / 2, 0, 0)));
	t.setLocalScale(Vector3(0.63, 0.63, 0.63));
	sp.addTransform(t);
	t.setLocalPosition(Vector3(0, -1, 0));
	t.setLocalRotation(Quaternion(Vector3(Math::PI / 2, 0, 0)));
	t.setLocalScale(Vector3(0.9, 0.9, 0.9));

	sp.addTransform(t);

	t.setLocalPosition(Vector3(0, -5, 0));
	t.setLocalScale(Vector3(0.9, 0.9, 0.9));
	sp.addTransform(t);


	t.setLocalPosition(Vector3(-1.5, -7, 0));
	t.setLocalScale(Vector3(1, 1, 1));
	sp.addTransform(t);


	t.setLocalPosition(Vector3(-1.5, -7, 0));
	t.setLocalScale(Vector3(1.5, 1.5, 1.5));
	sp.addTransform(t);
	
	t.setLocalPosition(Vector3(-2, -8, 0));
	t.setLocalScale(Vector3(1.5, 1.5, 1.5));
	sp.addTransform(t);

	t.setLocalPosition(Vector3(-2, -8, 0));
	t.setLocalScale(Vector3(0, 0, 0));
	sp.addTransform(t);
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
	camObj->getTransform()->name = "camera";
	camObj->addComponent(new KeyboardController());
	Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
	green->setDiffuse(0, 1, 0, 1);
	Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
	grey->setDiffuse(0.8, 0.8, 0.9, 1);

	Texture *cratetex = new Texture("Resources/fur-texture-seamless-free-thumb25.jpg", true, true);
	renderer->loadTexture(cratetex);
	Material *cratemat = renderer->createMaterial(Renderer::PR_OPAQUE);
	cratemat->setTexture(cratetex);

	Texture* cratetex2 = new Texture("Resources/moose-coat_1426-350.jpg", true, true);
	renderer->loadTexture(cratetex);
	Material* cratemat2 = renderer->createMaterial(Renderer::PR_OPAQUE);
	cratemat->setTexture(cratetex);

	Material** animatedMaterial;// [4];
	animatedMaterial = new Material*[4];
	animatedMaterial[0] = cratemat;
	animatedMaterial[1] = green;
	animatedMaterial[2] = grey;
	animatedMaterial[3] = cratemat2;


	//string filename[2];
	//filename[0] = "Resources/fur-texture-seamless-free-thumb25.jpg";
	//filename[1] = "Resources/moose-coat_1426-350.jpg";
	int cTime[4] = { 0,10,20,30 };
	

	GameObject *body = new GameObject(this);
	body->setMesh(new Tcylinder(1, 4, 20));
	body->setMaterial(cratemat);
	body->setAnimateTexture(0.002, 0.2);
	//body->setAnimatedTexture(animatedMaterial, cTime, false);
	body->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	body->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 2)));
	body->getTransform()->setParent(root);
	body->getTransform()->name = "body";

	legSweep();//initial the sweeeeeep
	//let's works on legs 
	GameObject *leg1 = new GameObject(this);
	leg1->setMesh(new Sweep(points, sp, true));
	leg1->setMaterial(green);
	leg1->getTransform()->setLocalPosition(Vector3(0,0,0));
	leg1->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg1->getTransform()->setLocalScale(Vector3(0.4, 0.4, 0.4));
	leg1->getTransform()->setParent(legJoint1->getTransform());
	leg1->getTransform()->name = "leg1";

	GameObject *leg2 = new GameObject(this);
	leg2->setMesh(new Sweep(points, sp, true));
	leg2->setMaterial(green);
	leg2->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	leg2->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg2->getTransform()->setLocalScale(Vector3(0.4, 0.4, 0.4));
	leg2->getTransform()->setParent(legJoint2->getTransform());
	leg2->getTransform()->name = "leg2";

	GameObject *leg3 = new GameObject(this);
	leg3->setMesh(new Sweep(points, sp, true));
	leg3->setMaterial(green);
	leg3->getTransform()->setLocalPosition(Vector3(0,0,0));
	leg3->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg3->getTransform()->setLocalScale(Vector3(0.4, 0.4, 0.4));
	leg3->getTransform()->setParent(legJoint3->getTransform());
	leg3->getTransform()->name = "leg3";

	GameObject *leg4 = new GameObject(this);
	leg4->setMesh(new Sweep(points, sp, true));
	leg4->setMaterial(green);
	leg4->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	leg4->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, -Math::PI / 2)));
	leg4->getTransform()->setLocalScale(Vector3(0.4, 0.4, 0.4));
	leg4->getTransform()->setParent(legJoint4->getTransform());
	leg4->getTransform()->name = "leg4";

	legJoint1->getTransform()->setLocalPosition(Vector3(0.1, 2, 0));
	legJoint1->getTransform()->setParent(body->getTransform());
	legJoint1->getTransform()->name = "legJoint1";

	legJoint2->getTransform()->setLocalPosition(Vector3(0.1, 2, 0));
	legJoint2->getTransform()->setParent(body->getTransform());
	legJoint2->getTransform()->name = "legJoint2";

	legJoint3->getTransform()->setLocalPosition(Vector3(0.1, -2, 0));
	legJoint3->getTransform()->setParent(body->getTransform());
	legJoint3->getTransform()->name = "legJoint3";

	legJoint4->getTransform()->setLocalPosition(Vector3(0.1, -2, 0));
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

	GameObject* pee = new GameObject(this);
	pee->setMesh(new cylinder(0.2, 1, 20));
	pee->getTransform()->setLocalPosition(Vector3(-8,-1.8, -1));
	pee->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 3 * Math::PI / 4, -Math::PI / 2)));
	pee->getTransform()->setParent(root);
	pee->getTransform()->name = "pee";
	pee->setVisible(false);
	pee->setMaterial(grey);
	
	
    Animation *anim = new Animation(30.0);
	body->addComponent(anim);
	anim->addKey("legJoint1", 0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 5.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 10.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 12.5, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 25.0, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 26.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 28.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, 2, -0.7));
	anim->addKey("legJoint1", 30.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, -0.7));

	anim->addKey("legJoint2", 0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 5.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 10.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 12.5, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 25.0, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 26.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 28.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, 2, 0.7));
	anim->addKey("legJoint2", 30.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, 2, 0.7));

	anim->addKey("legJoint3", 0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 5.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 10.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 12.5, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 25.0, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 26.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 28.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, -2, 0.7));
	anim->addKey("legJoint3", 30.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, 0.7));

	anim->addKey("legJoint4", 0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 5.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 10.0, Quaternion(Vector3(0, 0, Math::PI /5)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 12.5, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 15.0, Quaternion(Vector3(0, -3*Math::PI / 4, 0)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 22.5, Quaternion(Vector3(0, -3 * Math::PI / 4, 0)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 25.0, Quaternion(Vector3(0, 0, 0)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 26.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 28.0, Quaternion(Vector3(0, 0, -Math::PI / 5)), Vector3(0.1, -2, -0.7));
	anim->addKey("legJoint4", 30.0, Quaternion(Vector3(0, 0, Math::PI / 5)), Vector3(0.1, -2, -0.7));

	anim->addKey("body", 0.0, Quaternion(Vector3(0, 0, Math::PI / 2)), Vector3(0, 0, 0));
	anim->addKey("body", 12.5, Quaternion(Vector3(0, 0, Math::PI / 2)), Vector3(-10, 0, 0));
	anim->addKey("body", 25.0, Quaternion(Vector3(0, 0, Math::PI / 2)), Vector3(-10, 0, 0));
	anim->addKey("body", 30.0, Quaternion(Vector3(0, 0, Math::PI / 2)), Vector3(-20, 0, 0));

	anim->loop(false);

	
	AnimationTest *animTask = new AnimationTest(this);
	animTask->Aobject = pee;
	animTask->anima = anim;
	animTask->m = cratemat;
	animTask->Bobject = body;

	animateTexture* animTexture = new animateTexture(this);
	animTexture->Aobject = body;
	animTexture->m = animatedMaterial;
	animTexture->time = cTime;

	
	//addTask(animTexture);
	addTask(animTask);
	

	

	return true;
}