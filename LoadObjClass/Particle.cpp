#include "Particle.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
void Particle::Update(float deltaTime)
{
	acceleration = totalLinearForce / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	velocity *= pow(0.9f, deltaTime);
	ResetTotalForce();
	if (glm::length(velocity) < 0.01)
		velocity = glm::vec3(0);
}

Particle::Particle(float m, vec3 pos)
{
	mass = m;
	position = pos;
	acceleration = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);
	totalLinearForce = vec3(0, 0, 0);
}
Particle::~Particle()
{

}

void Particle::ResetTotalForce()
{
	totalLinearForce = vec3(0, 0, 0);
}

void Particle::AddForce(vec3 force, vec3 angforce)
{
	totalLinearForce += force;
}