// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.h
//
// Class to manage all information relating to objects in the scene.  Includes link to Transform and all Components

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"


namespace T3D
{
	class T3DApplication;
	class Transform;
	class Component;
	class Camera;
	class Light;

	//! Generic class for all objects that exist in the world
	/*! A GameObject's location is defined by the attached Transform.  The behaviour of a GameObject is customised by adding one or more Component's.  
	    Special Component's such as Light's, Camera's and Material's, should be added using the appropriate method.
	  \author  Robert Ollington
	  */

	class GameObject
	{
	public:
		GameObject(T3DApplication *app);
		~GameObject(void);

		void setTransform(Transform *t);
		Transform* getTransform();
		
		void setCamera(Camera *s);
		Camera* getCamera();
		
		void setLight(Light *l);
		Light* getLight();

		void setMaterial(Material *m);
		static void setStaticMaterial(Material* m, GameObject* t);
		Material* getMaterial();
		//void setAnimatedTexture(Material* m[], int *time, bool loop);
		//static void temp(Material* m[], int* time, bool loop, GameObject* t);
		
		void setMesh(Mesh *m);
		Mesh* getMesh();

		T3DApplication* getApp(){return app; }

		void addComponent(Component *component);
		void update(float dt);
		void setAnimateTexture(float speed);

		void setDistanceToCamera(float distance) { distanceToCamera = distance; }
		float getDistanceToCamera() const { return distanceToCamera; }

		void setVisible(bool visible) { this->visible = visible; }
		bool isVisible() { return visible; }

		void setAlpha(float alpha) { this->alpha = alpha; }		// 
		float getAlpha() { return alpha; }
       
		float backToOne(float a,float b);// if a is greater than 1, let it smaller than one 

	protected:
		T3DApplication *app;
		Transform* transform;
		Camera* camera;
		Light* light;
		bool loop;
		float SpeedOfTexture;
	
		//Renderer* renderer;
		Mesh* mesh;
		float alpha;			// override material alpha if < 1.0
        Material* material;
	private:		
		std::vector<Component*> components;

		bool visible;						// object drawn or not
		float distanceToCamera;				// this is a temp value for sorted draw order only

	};
}

#endif