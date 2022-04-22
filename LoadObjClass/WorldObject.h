#pragma once
#include "Model.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "vertex.h"
#include "ObjectType.h"
using namespace glm;
class WorldObject : public ObjectType
{
private:
public:
	bool isCue;
	WorldObject(const char*);
	WorldObject(const char*, vec3 pos, vec3 ori);
	~WorldObject();

	void SetPosition(vec3 newPos);
	vec3 GetPosition(void);

	void SetOri(vec3 newOri);
	vec3 GetOri();

	void SetIDs(unsigned int, unsigned int, unsigned int);
	void updateModelMatrix(unsigned int, float, float, vec3, vec3, vec3, vec3); //(MatrixLoc, camera offset,scale, Object Position);

	void Setup();
	void Draw();
	void Update(float, glm::vec3 offset);
};