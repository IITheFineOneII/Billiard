#include "Collider.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>

Collider::Collider(vec3 pos, float rad, bool isDestructor, colliderType type)
{
	position = pos;
	size = rad;
	this->type = type;
	this->isDestructor = isDestructor;
}
Collider::Collider(vec3 pos,vec3 ori, vec3 offset, colliderType type)
{
	position = pos;
	orientation = ori;
	this->offset = offset;
	this->type = type;

}
Collider::~Collider()
{

}

void Collider::SetPosition(vec3 newPos)
{

	position = newPos;
}


vec3 Collider::GetPosition(void)
{

	return position;
}


bool Collider::CollideCheck(Collider& other, CollisionData& collisionData)
{
	if ((type == SPHERE && other.type == SPHERE) && ((isDestructor == true && other.isDestructor == false) || (isDestructor == false && other.isDestructor == true)))
	{
		float dist = distance(position, other.position);
		float distRad = size + other.size;
		if (dist <= distRad)
		{
			vec3 norm = normalize(position - other.position); //normal
			float depth = distRad - dist; //depth
			vec3 point = other.position + norm * size; //touch point
			collisionData.normal = norm;
			collisionData.depth = depth;
			collisionData.point = point;
			collisionData.destructor1 = isDestructor;
			collisionData.destructor2 = other.isDestructor;
			cout << position.x << " " << position.y << " " << position.z << " Type:" << type << " other: " << other.position.x << " " << other.position.y << " " << other.position.z << " Type:" << other.type << endl;
			return true;
		}
		else {
			//cout << " didn't collide with " << endl;
			return false;
		}
	}
	if ((type == SPHERE && other.type == BOX) && isDestructor == false)
	{
		vec3 v = position - (other.position + other.offset);
		vec3 normal = normalize(other.orientation);
		float distancee = dot(normal, v) / sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		if (distancee <= size)
		{
			vec3 norm = normalize(v);
			vec3 point = (other.position + other.offset) + norm * size;
			collisionData.normal = norm;
			collisionData.depth = distancee;
			collisionData.point = point;
			cout << position.x << " " << position.y << " " << position.z << " Type:" << type << " other: " << other.position.x << " " << other.position.y << " " << other.position.z << " Type:" << other.type << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	
	if (type == SPHERE && other.type == SPHERE && (isDestructor == false && other.isDestructor == false))
	{
		float dist = distance(position, other.position);
		float distRad = size + other.size;
		if (dist <= distRad)
		{
			vec3 norm = normalize(other.position- position); //normal
			float depth = distRad - dist; //depth
			vec3 point = other.position + norm * size; //touch point
			collisionData.normal = norm;
			collisionData.depth = depth;
			collisionData.point = point;
			cout << position.x << " " << position.y << " " << position.z << " Type:" << type << " other: " << other.position.x << " " << other.position.y << " " << other.position.z << " Type:" << other.type << endl;
			return true;
		}
		else {
			//cout << " didn't collide with " << endl;
			return false;
		}
	}
		

}