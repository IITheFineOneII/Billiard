
#include "GameObject.h"
#include "OBJloader.h"
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
GameObject::GameObject(const char* name, string type, bool isCue)
{
	if (type == "Ball")
	{
		ball = new Ball(name, isCue);
		procedure = 0;
	}
}

GameObject::GameObject(const char* name, string type)
{
	if (type == "Ball")
	{
		ball = new Ball(name);
		procedure = 0;
	}
	if (type == "WorldObject")
	{
		worldObject = new WorldObject(name);
		procedure = 1;
	}
	if (type == "SphereEmpty")
	{
		ball = new Ball(name, 0);
		procedure = 0;
	}
	if (type == "PlaneEmpty")
	{
		ball = new Ball(name, 1);
		procedure = 0;
	}
	if (type == "PlaneEmpty2")
	{
		ball = new Ball(name, 2);
		procedure = 0;
	}
	if (type == "PlaneEmpty3")
	{
		ball = new Ball(name, 3);
		procedure = 0;
	}
	if (type == "PlaneEmpty4")
	{
		ball = new Ball(name, 4);
		procedure = 0;
	}
}


GameObject::GameObject(const char* name, vec3 pos, vec3 ori, string type)
{
	if (type == "Ball")
	{
		ball = new Ball(name, pos, ori);
		procedure = 0;
	}
	if (type == "WorldObject")
	{
		worldObject = new WorldObject(name, pos, ori);
		procedure = 1;
	}
}

GameObject::GameObject(const char* name, vec3 pos, vec3 ori, string type, bool isCue)
{
	if (type == "Ball")
	{
		ball = new Ball(name, pos, ori, isCue);
		procedure = 0;
	}
}

GameObject::~GameObject()
{
	if (procedure == 0) 
	{
		delete ball;

	}
	if (procedure  == 1)
	{
		delete worldObject;
	}
}

void GameObject::SetPosition(vec3 newPos)
{
	if (procedure == 0) {
		ball->SetPosition(newPos);
	}
	if (procedure == 1) {
		worldObject->SetPosition(newPos);
	}
}

vec3 GameObject::GetPosition(void)
{
	if (procedure == 0) {
		return ball->GetPosition();
	}
	if (procedure == 1) {
		return worldObject->GetPosition();
	}
}

void GameObject::SetOri(vec3 newOri)
{
	if (procedure == 0) {
		ball->SetOri(newOri);
	}
	if (procedure == 1) {
		worldObject->SetOri(newOri);
	}
}

vec3 GameObject::GetOri()
{
	if (procedure == 0) {
		return ball->GetOri();
	}
	if (procedure == 1) {
		return worldObject->GetOri();
	}
}


void GameObject::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	if (procedure == 0) {
		ball->SetIDs(vao, vbo, ibo);
	}
	if (procedure == 1) {
		worldObject->SetIDs(vao, vbo, ibo);
	}
}

void GameObject::Setup()
{
	if (procedure == 0) {
		ball->Setup();
	}
	if (procedure == 1) {
		worldObject->Setup();
	}
}

void GameObject::updateModelMatrix(unsigned int modelViewMatLoc, float d, float scale, vec3 offsetPos, vec3 ori, vec3 curCam, vec3 curEye)
{
	if (procedure == 0) {
		ball->updateModelMatrix(modelViewMatLoc, d, scale, offsetPos, ori, curCam, curEye);
	}
	if (procedure == 1) {
		worldObject->updateModelMatrix(modelViewMatLoc, d, scale, offsetPos, ori, curCam, curEye);
	}
}

void GameObject::Draw()
{
	if (procedure == 0) {
		ball->Draw();
	}
	if (procedure == 1) {
		worldObject->Draw();
	}
}

int GameObject::GetType()
{
	return procedure;
}

void GameObject::SetType(int newtype)
{
	procedure = newtype;
}

void GameObject::Update(float deltaTime, glm::vec3 offset)
{
	if (procedure == 0) {
		ball->Update(deltaTime, offset);
	}
	if (procedure == 1) {
		worldObject->Update(deltaTime, offset);
	}
}