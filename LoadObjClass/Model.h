#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "vertex.h"

using namespace glm;

class Model
{
private:

	glm::vec3 position;

	VertexWithAll* VerticesData;  //Data with vertices, normal, texCoords

	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO; //for triangle indices buffer
	int NumVert;
	mat4 ModelMatrix;

	
public:
	 Model() {};
	 Model(const char*);
	~Model();

	void CreateObject(const char*);

	void SetPosition(vec3 newPos);
	vec3 GetPosition(void);


	//void SetOri(vec3 newOri);
	//vec3 GetOri(void);

	void SetIDs(unsigned int, unsigned int, unsigned int);
	void updateModelMatrix(unsigned int, float, float, vec3, vec3, vec3, vec3); //(MatrixLoc, camera offset,scale, Object Position);

	void Setup();
	void Draw();
};

