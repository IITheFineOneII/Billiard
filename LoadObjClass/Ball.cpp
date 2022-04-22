#include "Ball.h"
#include "OBJloader.h"
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
Ball::Ball(const char* name, vec3 pos, vec3 ori) : ObjectType(1, pos, ori)
{
	model = new Model;
	model->CreateObject(name);
	isCue = false;
	isDestructor = false;
	collider = new SphereCollider(pos, 2.5 * 0.2f, isDestructor);
}
Ball::Ball(const char* name, vec3 pos, vec3 ori, bool isCue) : ObjectType(1, pos, ori)
{
	model = new Model;
	model->CreateObject(name);
	isDestructor = false;
	this->isCue = isCue;
	collider = new SphereCollider(pos, 2.5 * 0.2f, isDestructor);
}

Ball::Ball(const char* name) : ObjectType(1, vec3(0), vec3(0))
{
	model = new Model;
	model->CreateObject(name);
	isCue = false;
	isDestructor = false;
	body->SetPos(glm::vec3(0, 0, 0));
	body->SetOri(glm::vec3(0, 0, 0));
	collider = new SphereCollider(vec3(0), 2.5 * 0.2f, isDestructor);
}

Ball::Ball(const char* name, bool isCue) : ObjectType(1, vec3(0), vec3(0))
{
	model = new Model;
	model->CreateObject(name);
	this->isCue = isCue;
	isDestructor = false;
	body->SetPos(glm::vec3(0, 0, 0));
	body->SetOri(glm::vec3(0, 0, 0));
	collider = new SphereCollider(vec3(0), 2.5 * 0.2f, isDestructor);

}

Ball::Ball(const char* name, int collisionball) : ObjectType(10000, vec3(0), vec3(0))
{
	model = new Model;
	model->CreateObject(name);
	isCue = false;
	isDestructor = true;
	this->collisionball = collisionball;
	body->SetPos(glm::vec3(0, 0, 0));
	body->SetOri(glm::vec3(0, 0, 0));
	if (collisionball == 0)
		collider = new SphereCollider(vec3(0), 15 * 0.2f, isDestructor);


	if (collisionball == 1)
		collider = new BoxCollider(vec3(0), vec3(1,0,0), vec3(0));
	if (collisionball == 2)
		collider = new BoxCollider(vec3(0), vec3(-1, 0, 0), vec3(0)); 
	if (collisionball == 3)
		collider = new BoxCollider(vec3(0), vec3(0, 0, 1), vec3(0));
	if (collisionball == 4)
		collider = new BoxCollider(vec3(0), vec3(0, 0, -1), vec3(0));
}

Ball::~Ball()
{

}

void Ball::SetPosition(vec3 newPos)
{
	body->SetPos(newPos);
	model->SetPosition(newPos);
	collider->SetPosition(newPos);
}

vec3 Ball::GetPosition(void)
{
	return body->GetPos();
}

void Ball::SetOri(vec3 newOri)
{
	body->SetOri(newOri);
}

vec3 Ball::GetOri()
{
	return body->GetOri();
}

vec3 Ball::GetVel()
{
	return body->GetVel();
}

void Ball::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	model->SetIDs(vao, vbo, ibo);
}

void Ball::Setup()
{
	model->Setup();

}

void Ball::updateModelMatrix(unsigned int modelViewMatLoc, float d, float scale, vec3 offsetPos, vec3 ori, vec3 curCam, vec3 curEye)
{
	model->updateModelMatrix(modelViewMatLoc, d, scale, offsetPos, ori, curCam, curEye);
}

void Ball::Draw()
{
	model->Draw();
}

void Ball::Bounce(vec3 velo)
{
	body->ReverseForce(velo);
}

void Ball::PassForce()
{

}
void Ball::AddForce(vec3 force)
{
	body->AddForce(force);
}

void Ball::Update(float deltaTime, glm::vec3 offset)
{
	//model->SetPosition(body->GetPos());
	SetPosition(body->GetPos());
	if (isCue)
	{
		//cout << body->GetPos().x << " " << body->GetPos().y << " " << body->GetPos().z << endl;
		;
	}

	//Ctrl sends them flying rn
	if (ObjectType::specialKeys[101] == true && isCue)
	{
		//cout << "bruh" << endl;
		body->AddForce(vec3(0, 0, -10), vec3(0.0, 1.0, -5.0));
		ObjectType::specialKeys[101] = false;

	}
	if (ObjectType::specialKeys[100] == true && isCue)
	{
		body->AddForce(vec3(-10, 0, 0), vec3(-5.0, 1.0, 0.0));
		ObjectType::specialKeys[100] = false;

	}
	if (ObjectType::specialKeys[103] == true && isCue)
	{
		body->AddForce(vec3(0, 0, 10), vec3(0.0, 1.0, 5.0));
		ObjectType::specialKeys[103] = false;

	}
	if (ObjectType::specialKeys[102] == true && isCue)
	{
		body->AddForce(vec3(10, 0, 0), vec3(5.0, 1.0, 0.0));
		ObjectType::specialKeys[102] = false;

	}
	body->Update(deltaTime);
	//collider->Update(deltaTime, position, offset);
}