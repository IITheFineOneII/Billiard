#pragma once
#include "Ball.h"
#include "WorldObject.h"
#include "Collider.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "vertex.h"
#include "ObjectType.h"
#include <string>
class GameObject
{
protected:
	Ball* ball;
	WorldObject* worldObject;
	Collider* collider;
private:
	int procedure;
public:
	GameObject(const char*, string type, bool isCue);
	GameObject(const char*, string type);
	GameObject(const char*, vec3 pos, vec3 ori, string type);
	GameObject(const char*, vec3 pos, vec3 ori, string type, bool isCue);
	~GameObject();
	void SetPosition(vec3 newPos);
	vec3 GetPosition(void);

	void SetOri(vec3 newOri);
	vec3 GetOri();
	void SetIDs(unsigned int, unsigned int, unsigned int);
	void updateModelMatrix(unsigned int, float, float, vec3, vec3, vec3, vec3); //(MatrixLoc, camera offset,scale, Object Position);
	void Setup();
	void Draw();
	int GetType();
	void SetType(int newtype);
	Ball* GetBall() { return ball; };
	WorldObject* GetWorldObject() { return worldObject; };
	void Update(float, glm::vec3 offset);
};

