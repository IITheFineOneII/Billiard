#include "WorldObject.h"
#include "OBJloader.h"
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
WorldObject::WorldObject(const char* name, vec3 pos, vec3 ori) : ObjectType(100000, pos, ori)
{
	model = new Model;
	model->CreateObject(name);
	isCue = false;
	collider = new BoxCollider(pos, vec3(0,1,0), vec3 (0, -2.5, 0));
}

WorldObject::WorldObject(const char* name) : ObjectType(10000, vec3(0), vec3(0))
{
	model = new Model;
	model->CreateObject(name);
	isCue = false;
	body->SetPos(glm::vec3(0, 0, 0));
	body->SetOri(glm::vec3(0, 0, 0));
	collider = new BoxCollider(vec3(0), vec3(0,1,0), vec3 (0, -2.5, 0));
}
WorldObject::~WorldObject()
{

}

void WorldObject::SetPosition(vec3 newPos)
{
	body->SetPos(newPos);
	model->SetPosition(body->GetPos());
	collider->SetPosition(body->GetPos());
}


vec3 WorldObject::GetPosition(void)
{
	return body->GetPos();
}

void WorldObject::SetOri(vec3 newOri)
{
	body->SetOri(newOri);
}

vec3 WorldObject::GetOri()
{
	return body->GetOri();
}

void WorldObject::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	model->SetIDs(vao, vbo, ibo);
}

void WorldObject::Setup()
{
	model->Setup();

}

void WorldObject::updateModelMatrix(unsigned int modelViewMatLoc, float d, float scale, vec3 offsetPos, vec3 ori, vec3 curCam, vec3 curEye)
{
	model->updateModelMatrix(modelViewMatLoc, d, scale, offsetPos, ori, curCam, curEye);
}

void WorldObject::Draw()
{
	model->Draw();
}

void WorldObject::Update(float deltaTime, glm::vec3 offset)
{
	model->SetPosition(body->GetPos());
	body->Update(deltaTime);
	//collider->Update(deltaTime, position, offset);
}