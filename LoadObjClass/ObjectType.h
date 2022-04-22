#pragma once

#include <map>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "PhysicsBody.h"
#include "Collider.h"
#include "Model.h"
#include <map>
//#include "SphereCollider.h" //link to your physics (Sphere collider)

class ObjectType
{
protected:
	//physics stuff here
	//PhysicsBody* physicsBody;
	//SphereCollider* collider;
	//3D position of the object
	PhysicsBody* body;
	Model* model;
	Collider* collider;


public:
	ObjectType();
	ObjectType(float m, glm::vec3 pos, glm::vec3 ori);
	ObjectType(float m, glm::vec3 pos);
	ObjectType(glm::vec3 pos);
	~ObjectType();
	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;
	Collider* GetCollider() { return collider; };
	PhysicsBody* GetBody() { return body; };

	//Get sphere collider 
	//SphereCollider* GetCollider();

	//OpenGL drawing function
	virtual void Draw() = 0;

	///physics update function

	virtual void Update(float);

	float m;
};

