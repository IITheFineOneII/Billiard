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

class BoxCollider : public Collider
{


public:
	BoxCollider(vec3 pos, vec3 ori, vec3 offset);
	~BoxCollider();
	void Draw();
};
