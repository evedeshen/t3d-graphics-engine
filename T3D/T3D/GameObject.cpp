// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.cpp
//
// Class to manage all information relating to objects in the scene.  Includes link to Transform and all Components

#include "GameObject.h"
#include "T3DApplication.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "Terrain.h"
#include <thread>
#include "animateTexture.h"



namespace T3D
{
	/*! Creates a game object and assigns the parent application
	  \param app	The application that spawned this game object
	  */
	GameObject::GameObject(T3DApplication *app)
	{
		this->app = app;
		setTransform(new Transform());
		camera = NULL;
		mesh = NULL;
		material = NULL;
		light = NULL;
		visible = true;
		alpha = 1.0f;
		loop = false;
		speed = 0.0;
		sizeOfAnimte = 0.0;
	}

	/*! Destructor
	  The destructor is responsible for freeing all components
	  \remark	Note that the Transform is not deleted, it is the Transform's responsibility to delete attached game objects not the other waya round
	  \todo		Finish deleting components
	  */
	GameObject::~GameObject(void)
	{
		if (camera) delete camera;
		if (mesh) delete mesh;
		if (light) delete light; // TODO: should make sure that this is removed from renderer's list of lights

		std::vector<Component*>::iterator ci;
		for (ci = components.begin(); ci != components.end(); ci++) {
			delete (*ci);
		}

		// don't delete transform - normally gameobject delete will be called from transform delete
	}

	/*! Sets the Transform for this component
	  Set's the new Transform and updates the corrsponding link for the new Transform
	  \param t		The new Transform
	  \todo			Should this method also update the gameObject of the old Transform?
	  */
	void GameObject::setTransform(Transform *t){
		transform = t;
		t->gameObject = this;
	}

	/*! Returns the Trasform
	  \return	The current Transform
	  */
	Transform* GameObject::getTransform(){
		return transform;
	}	
	
	/*! Attaches a Camera to this game object
	  Sets the camera variable for this object and also the gameObject link for the Camera
	  \param c		The Camera
	  \todo			Should the camera also be added to the list of Component's?  If not, why is Camera a Component?
	  */
	void GameObject::setCamera(Camera *c){
		camera = c;
		camera->gameObject = this;
	}

	/*! Returns the Camera
	  Will return NULL if no camera is attached
	  \return	The current Camera attached to this game object
	  */
	Camera* GameObject::getCamera(){
		return camera;
	}

	/*! Attaches a Light to this game object
	  Sets the light variable for this object and also the gameObject link for the Light, and adds the light to the list in the Renderer
	  \param l		The Light
	  \todo			Should the light also be added to the list of Component's?  If not, why is Light a Component?
	  */
	void GameObject::setLight(Light *l){
		light = l;
		light->gameObject = this;
		app->getRenderer()->lights.push_back(light);
	}

	/*! Returns the Light
	  Will return NULL if no light is attached
	  \return	The current Light attached to this game object
	  */
	Light* GameObject::getLight(){
		return light;
	}

	/*! Attaches a Material to this game object
	  Sets the material variable for this object
	  \param m		The Material
	  \todo			Should Material be a Component?
	  */
	void GameObject::setMaterial(Material *m){
		material = m;
	}

	void GameObject::setStaticMaterial(Material* m, GameObject* t)
	{
		t->material = m;
	}
	
	/*! Returns the Material
	  Will return NULL if no material is attached
	  \return	The current Material attached to this game object
	  */
	Material* GameObject::getMaterial(){
		return material;
	}

	/*
	void GameObject::setAnimatedTexture(Material* m[], int* time, bool loop)
	{
		
		//animateTexture* animTexture = new animateTexture(g);
		//animTexture->Aobject = this;
		//animTexture->m = m;
		//animTexture->time = time;
		//g->addTask(animTexture);
		

		//std::thread thread_object(temp, m, time, loop, this);
		//thread_object.join();
		
		
		std::thread thread_object([](Material* m[], int* time, GameObject *t) {
			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					t->setStaticMaterial(m[i], t);

				}
				else
				{
					_sleep(time[i] - time[i - 1]);
					t->setStaticMaterial(m[i], t);

				}
			}
		}, m, time, this);
		
	}

	void GameObject::temp(Material* cratemate[], int* time, bool loop, GameObject *t)
	{
		for (int i = 0; i < sizeof(time); i++)
		{
			if (i == 0)
			{
				t->setStaticMaterial(cratemate[i], t);

			}
			else
			{
				printf("sleeep \n");
				_sleep(100*(time[i] - time[i - 1]));
				printf("sleeeped \n");
				t->setStaticMaterial(cratemate[i], t);

			}
		}
	}
	*/

	/*! Attaches a Mesh to this game object
	  Sets the mesh variable for this object and also the gameObject link for the Mesh
	  \param m		The Mesh
	  \todo			Should the mesh also be added to the list of Component's?  If not, why is Mesh a Component?
	  */
	void GameObject::setMesh(Mesh *m){
		mesh = m;
		mesh->gameObject = this;
	}

	/*! Returns the Mesh
	  Will return NULL if no mesh is attached
	  \return	The current Mesh attached to this game object
	  */
	Mesh* GameObject::getMesh(){
		return mesh;
	}	

	/*! Add a Component to this game object
	  And also initialise the Component (components should not be initialised before attaching to a game object)
	  \param component	The Component to attach
	  */
	void GameObject::addComponent(Component *component){
		components.push_back(component);
		component->init(this);
	}

	/*! Update all Component's attached to this game object
	  \param dt		The time that has passed since the last update (in seconds)
	  */
	void GameObject::update(float dt){
		std::vector<Component*>::iterator it;

		for ( it=components.begin() ; it < components.end(); it++ )
		{
			(*it)->update(dt);
		}

		//new update for texture
		if (loop)
		{
			float* tempUV = getMesh()->getUVs();
			for (int i = 0; i < getMesh()->getNumVerts(); i++)
			{
				getMesh()->setUV(i, backToOne(tempUV[2 * i],speed), tempUV[2 * i + 1]);
			}
		}
		
	}
	void GameObject::setAnimateTexture(float speeds, float s)
	{
		loop = true;
		speed = speeds;
		sizeOfAnimte = s;
	}



	float GameObject::backToOne(float a,float b)
	{
		

		if (a+b >=1 )
		{
			return a+b - 1;
		}

		return a+b;
	}
}
