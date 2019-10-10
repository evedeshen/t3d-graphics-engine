#include "AssignmentSweep.h"
#include "Camera.h"
#include "Cube.h"
#include "KeyboardController.h"
#include "Sweep.h"
#include "SweepPath.h"

using namespace T3D;

AssignmentSweep::AssignmentSweep()
{
}


AssignmentSweep::~AssignmentSweep()
{
}

bool AssignmentSweep::init() {
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

	vector<Transform> path;
	//start to build sweep 
	SweepPath sp;
	Transform t;
	
	
	
	// Make a profile
	vector<Vector3> points;
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

	t.setLocalPosition(Vector3(0, -3, 0));
	t.setLocalScale(Vector3(0.9, 0.9, 0.9));
	sp.addTransform(t);

	t.setLocalPosition(Vector3(-1, -4, 0));
	t.setLocalScale(Vector3(1, 1, 1));
	sp.addTransform(t);

	t.setLocalPosition(Vector3(-1.5, -4.5, 0));
	t.setLocalScale(Vector3(1, 1, 1));
	sp.addTransform(t);


	t.setLocalPosition(Vector3(-1.5,-4.5, 0));
	t.setLocalScale(Vector3(0, 0, 0));
	sp.addTransform(t);

	//t.setLocalPosition(Vector3(-3, 0, 0));
	//t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
	//t.setLocalScale(Vector3(1, 1, 1));
	//sp.addTransform(t);
	
	
	
	//t.setLocalPosition(Vector3(0, -2, 0));
	//t.setLocalScale(Vector3(1, 1, 1));
	//t.setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 2)));
    //sp.addTransform(t);

	//t.setLocalScale(Vector3(0, 0, 1.0));
	//sp.addTransform(t);

	GameObject *torus = new GameObject(this);
	torus->setMesh(new Sweep(points, sp, true));
	torus->setMaterial(green);
	torus->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	torus->getTransform()->setParent(root);
	torus->getTransform()->name = "Torus";
	return true;
}
