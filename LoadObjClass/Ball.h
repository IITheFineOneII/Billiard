#pragma once
#include "Model.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Collider.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "vertex.h"
#include <string>
#include "ObjectType.h"

using namespace glm;

class Ball : public ObjectType
{
private:
public:
	bool isCue;
	bool isDestructor;
	int collisionball;
	Ball(const char*);
	Ball(const char*, bool isCue);
	Ball(const char*, vec3 pos, vec3 ori);
	Ball(const char*, vec3 pos, vec3 ori, bool isCue);
	Ball(const char*, int collisionball);
	~Ball();

	void SetPosition(vec3 newPos);
	vec3 GetPosition(void);

	void SetOri(vec3 newOri);
	vec3 GetOri();
	vec3 GetVel();
	void SetIDs(unsigned int, unsigned int, unsigned int);
	void updateModelMatrix(unsigned int, float, float, vec3, vec3, vec3, vec3); //(MatrixLoc, camera offset,scale, Object Position);
	void Bounce(vec3 velo);
	void Setup();
	void Draw();
	void AddForce(vec3 force);
	void PassForce();
	void Update(float, glm::vec3 offset);
};