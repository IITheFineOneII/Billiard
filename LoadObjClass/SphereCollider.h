#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "PhysicsBody.h"
#include "CollisionData.h"
#include "Collider.h"

using namespace std;
using namespace glm;

class SphereCollider : public Collider
{

	
public:
	SphereCollider(vec3 pos, float rad, bool isDestructor);
	~SphereCollider();

};

