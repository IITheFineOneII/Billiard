#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "PhysicsBody.h"
#include <string>
#include "CollisionData.h"

using namespace std;
using namespace glm;

class Collider
{
protected:
	vec3 position;
	vec3 orientation;
	bool isDestructor;
	float size;
	float a;
	float b;
	vec3 offset;
	enum colliderType { SPHERE, BOX, DESTROYED };
	colliderType type;


public:
	Collider(vec3 pos, float rad, bool isDestructor, colliderType type);
	Collider(vec3 pos, vec3 ori, vec3 offset, colliderType type);
	~Collider();

	void SetPosition(vec3 newPos);
	vec3 GetPosition(void);



	bool CollideCheck(Collider&, CollisionData&);

};

