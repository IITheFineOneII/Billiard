#include "RigidBody.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>

void RigidBody::Update(float deltaTime)
{
	acceleration = totalLinearForce/mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	velocity *= pow(0.9, deltaTime);



	angularacceleration = totalAngularForce / inertia; //inertia
	angularvelocity += angularacceleration * deltaTime;
	orientation += angularvelocity * deltaTime;
	angularvelocity *= pow(0.9f, deltaTime);

	//if (velocity != (0,0,0) && angvelocity = (0,0,0))
	
	//std::cout << totalAngularForce.z << std::endl;
	//std::cout << orientation.z << std::endl;
	//std::cout << inertia << std::endl;
	ResetTotalForce();
	if (glm::length(velocity) < 0.01)
		velocity = glm::vec3(0);
	//if (glm::length(angularvelocity) < 0.01)
	//	angularvelocity = glm::vec3(0);
}

RigidBody::RigidBody(float m, vec3 pos, vec3 ori)
{

	mass = m;
	inertia = 2.0f/5.0f*m*2.5f*2.5f;
	position = pos;
	orientation = ori;
	acceleration = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);
	totalLinearForce = vec3(0, 0, 0);
}

RigidBody::~RigidBody()
{
}


void RigidBody::ResetTotalForce()
{
	totalLinearForce = vec3(0, 0, 0);
	totalAngularForce = vec3(0, 0, 0);
}

void RigidBody::AddForce(vec3 force, vec3 forceposition)
{
	totalLinearForce += force;
	vec3 torque = vec3(forceposition.y * force.z - forceposition.z * force.y, forceposition.z * force.x - forceposition.x * force.z, forceposition.x * force.y - forceposition.y * force.x);
	totalAngularForce +=torque; 
	//std::cout << totalLinearForce.z << std::endl;
}
