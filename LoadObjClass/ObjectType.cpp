#include "ObjectType.h"
#include "Particle.h"
#include "RigidBody.h"

std::map<char, bool> ObjectType::keys;
std::map<int, bool> ObjectType::specialKeys;

ObjectType::ObjectType()
{
	m = 1;
	body = new Particle(1.0, glm::vec3(0,0,0));
}

ObjectType::ObjectType(float m, glm::vec3 pos, glm::vec3 ori)
{
	this->m = m;
	body = new RigidBody(m, pos, ori);
}

ObjectType::ObjectType(float m, glm::vec3 pos)
{
	this->m = m;
	body = new Particle(m, pos);

}

ObjectType::ObjectType(glm::vec3 pos)
{
	this->m = m;
	body = new Particle(1, pos);

}
ObjectType::~ObjectType()
{
	delete body;
}
/*
SphereCollider* ObjectType::GetCollider()
{
	return collider;
}
*/
void ObjectType::Update(float deltaTime)
{
}