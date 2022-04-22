#include "BoxCollider.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
BoxCollider::BoxCollider(vec3 pos, vec3 ori, vec3 offset) : Collider(pos, ori, offset, BOX)
{
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Draw()
{
	
}
