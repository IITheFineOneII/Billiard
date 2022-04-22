#pragma once
#include <glm/glm.hpp>
#include "PhysicsBody.h"
using namespace std;
using namespace glm;

class RigidBody:public PhysicsBody
{
private:
	float mass;
	vec3 acceleration;
	vec3 velocity;
	vec3 totalLinearForce;
	vec3 position;
	vec3 orientation;
	//missing the rotational stuff
	vec3 angularacceleration;
	vec3 angularvelocity;
	vec3 totalAngularForce;
	float inertia;
public:
	void Update(float);

	RigidBody(float m, vec3 pos, vec3 ori);
	~RigidBody();

	void ResetTotalForce();


	void AddForce(vec3 force, vec3 angforce);

	void SetPos(vec3 pos)
	{
		position = pos;
	}

	vec3 GetPos()
	{
		return position;
	}

	vec3 GetVel()
	{
		return velocity;
	}
	void SetOri(vec3 ori)
	{
		orientation = ori;
	}

	vec3 GetOri()
	{
		return orientation;
	}
	void ReverseForce(vec3 velo)
	{
		velocity *= -1;
		angularvelocity *= -1;

	}

	
};

