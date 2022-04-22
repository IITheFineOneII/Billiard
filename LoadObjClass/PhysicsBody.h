#pragma once
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

class PhysicsBody
{
private:
public:
	virtual void Update(float) = 0;
	virtual void ResetTotalForce() = 0;
	virtual void AddForce(vec3 force, vec3 angforce = vec3(0, 0, 0)) = 0;
	virtual void SetPos(vec3 pos) = 0;
	virtual vec3 GetPos() = 0;
	virtual vec3 GetVel() = 0;
	virtual void ReverseForce(vec3 velo) = 0;
	virtual void SetOri(vec3 ori) = 0;
	virtual vec3 GetOri() = 0;
	~PhysicsBody() {};

};

