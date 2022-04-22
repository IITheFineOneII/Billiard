#include "Model.h"
#include "OBJloader.h"
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>

Model::Model(const char* name)
{
	VAO = VBO = 0;
	VerticesData = NULL;
	NumVert = 0;
	CreateObject(name);
}

Model::~Model()
{
	free(VerticesData);
}

void Model::CreateObject(const char* name)
{
	std::vector<VertexWithAll> mesh = loadOBJ(name); //Import OBJ file data into a vector array
	NumVert = mesh.size();

	this->VerticesData = new VertexWithAll[NumVert];
	for (size_t i = 0; i < NumVert; i++)
	{
		this->VerticesData[i] = mesh[i];
	}
}

void Model::SetPosition(vec3 newPos)
{
	position = newPos;
}

vec3 Model::GetPosition(void)
{
	return position;
}

void Model::SetIDs(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	VAO = vao;
	VBO = vbo;
	IBO = ibo;
}

void Model::Setup()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWithAll) * NumVert, VerticesData, GL_STATIC_DRAW);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, VertexWithAll::position));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, VertexWithAll::normal));
	glEnableVertexAttribArray(5);

	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(VertexWithAll), (GLvoid*)offsetof(VertexWithAll, VertexWithAll::textcoord));
	glEnableVertexAttribArray(6);

}

void Model::updateModelMatrix(unsigned int modelViewMatLoc, float d, float scale, vec3 offsetPos, vec3 ori, vec3 curcam, vec3 cureye)
{
	ModelMatrix = mat4(1.0);
	ModelMatrix = lookAt(curcam, cureye, vec3(0.0, 1.0, 0.0)); //camera matrix, apply first
	ModelMatrix = glm::scale(ModelMatrix, vec3(scale, scale, scale));  //scale down the model
	ModelMatrix = glm::translate(ModelMatrix, offsetPos);
	ModelMatrix = glm::translate(ModelMatrix, GetPosition());
	ModelMatrix = glm::rotate(ModelMatrix, ori.z, glm::vec3(0, 0, 1));
	ModelMatrix = glm::rotate(ModelMatrix, ori.y, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, ori.x, glm::vec3(1, 0, 0));
	//ModelMatrix = glm::translate(ModelMatrix, GetOri().z);
	glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, value_ptr(ModelMatrix));  //send modelview matrix to the shader
}

void Model::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, NumVert);
}
