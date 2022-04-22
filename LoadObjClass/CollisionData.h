#pragma once

class GameObject;

struct CollisionData
{
	GameObject* object1;
	GameObject* object2;
	vec3 normal;
	float depth;
	vec3 point;
	bool destructor1;
	bool destructor2;
};

