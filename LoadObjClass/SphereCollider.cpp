#include "SphereCollider.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
SphereCollider::SphereCollider(vec3 pos, float rad, bool isDestructor) : Collider(pos, rad, isDestructor, SPHERE)
{
}

SphereCollider::~SphereCollider()
{

}
