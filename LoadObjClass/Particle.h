#pragma once
#include <glm/glm.hpp>
#include "PhysicsBody.h"
using namespace std;
using namespace glm;
class Particle:public PhysicsBody
{
private:
	vec3 orientation;
	float mass;		
	vec3 acceleration;
	vec3 velocity;
	vec3 totalLinearForce;
	vec3 position;

public:
	
	
	void Update(float);

	Particle(float m, vec3 pos);
	~Particle();

	void SetPos(vec3 pos)
	{
		position = pos;
	}

	vec3 GetPos()
	{
		return position;
	}
	void ReverseForce(vec3 velo)
	{
		;
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

	void ResetTotalForce();
	

	void AddForce(vec3 force, vec3 angforce = vec3(0,0,0));
};

