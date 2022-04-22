/////////////////////////////////////////////////////////////////////////////////          
// CreateSphere.cpp
//
// Forward-compatible core GL 4.3 version 
//
// Interaction:
// Press the up and down arrow keys to move the viewpoint over the field.
//
//
///////////////////////////////////////////////////////////////////////////////// 

#include <cmath>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "shader.h"
#include "vertex.h"
#include "GameObject.h"
#include "Ball.h"
#include "Model.h"
#include "CollisionData.h"
#include "soil/SOIL.h"
#include <vector>

using namespace std;
using namespace glm;

static enum object { FIELD, SKY, SPHERE, TABLE, BALL1, BALL2, BALL3, BALL4, BALL5, BALL6, BALL7, BALL8, BALL9, BALL10, BALL11, BALL12, BALL13, BALL14, BALL15, CUEBALL, TABLEGREEN, TABLEBLACK, TABLEBROWN, COLLIDERVISUAL, FLOOR, WALL, CUE }; // VAO ids.
static enum buffer { FIELD_VERTICES, SKY_VERTICES, SPHERE_VERTICES, SPHERE_INDICES, TABLE_VERTICES, BALL1_VERTICES, TABLEGREEN_VERTICES, TABLEBLACK_VERTICES, TABLEBROWN_VERTICES, FLOOR_VERTICES, WALL_VERTICES, CUE_VERTICES, COLLIDERVISUAL_VERTICES }; // VBO ids.



struct Material
{
	vec4 ambRefl;
	vec4 difRefl;
	vec4 specRefl;
	vec4 emitCols;
	float shininess;
};

struct Light
{
	vec4 ambCols;
	vec4 difCols;
	vec4 specCols;
	vec4 coords;
};

// Globals.
static Vertex fieldVertices[] =  
{	{vec4(100.0, 0.0, 100.0, 1.0), vec2(8.0, 0.0)},
	{vec4(100.0, 0.0, -100.0, 1.0), vec2(8.0, 8.0)},
	{vec4(-100.0, 0.0, 100.0, 1.0), vec2(0.0, 0.0)},
	{vec4(-100.0, 0.0, -100.0, 1.0), vec2(0.0, 8.0)}
}; 

static Vertex skyVertices[4] =
{
	{vec4(100.0, 120.0, -70.0, 1.0), vec2(1.0, 0.0)},
	{vec4(100.0, 0.0, -70.0, 1.0), vec2(1.0, 1.0)},
	{vec4(-100.0, 120.0, -70.0, 1.0), vec2(0.0, 0.0)},
	{vec4(-100.0, 0.0, -70.0, 1.0), vec2(0.0, 1.0)}
};

static GameObject objects[] = 
{
	GameObject("Textures/Table.obj", "WorldObject"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball"),
	GameObject("Textures/Ball.obj", "Ball", true),
	GameObject ("Textures/Table.obj", "WorldObject"),
	GameObject ("Textures/TableBlack.obj", "WorldObject"),
	GameObject ("Textures/TableGreen.obj", "WorldObject"),
	GameObject("Textures/BallPlaceholder.obj", "SphereEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "SphereEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "SphereEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "SphereEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "SphereEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "SphereEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "PlaneEmpty"),
	GameObject("Textures/BallPlaceholder.obj", "PlaneEmpty2"),
	GameObject("Textures/BallPlaceholder.obj", "PlaneEmpty3"),
	GameObject("Textures/BallPlaceholder.obj", "PlaneEmpty4")
};
	GameObject Floor ("Textures/Floor.obj", "WorldObject");
	GameObject Wall ("Textures/Wall.Obj", "WorldObject");
	GameObject Cue ("Textures/Cue.obj", "WorldObject");
/*
static GameObject MyModel("Textures/Table.obj", "WorldObject");
static GameObject Ball1("Textures/Ball.obj", "Ball");
static GameObject Ball2("Textures/Ball.obj", "Ball") ;
static GameObject Ball3("Textures/Ball.obj", "Ball");
static GameObject Ball4("Textures/Ball.obj", "Ball");
static GameObject Ball5("Textures/Ball.obj", "Ball");
static GameObject Ball6("Textures/Ball.obj", "Ball");
static GameObject Ball7("Textures/Ball.obj", "Ball");
static GameObject Ball8("Textures/Ball.obj", "Ball");
static GameObject Ball9("Textures/Ball.obj", "Ball");
static GameObject Ball10("Textures/Ball.obj", "Ball");
static GameObject Ball11("Textures/Ball.obj", "Ball");
static GameObject Ball12("Textures/Ball.obj", "Ball");
static GameObject Ball13("Textures/Ball.obj", "Ball");
static GameObject Ball14("Textures/Ball.obj", "Ball");
static GameObject Ball15("Textures/Ball.obj", "Ball");
static GameObject CueBall("Textures/Ball.obj", "Ball", true);
static GameObject TableGreen("Textures/Table.obj", "WorldObject");
static GameObject TableBlack("Textures/TableBlack.obj", "WorldObject");
static GameObject TableBrown("Textures/TableGreen.obj", "WorldObject");
*/
static mat4 modelViewMat = mat4(1.0);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);  ///create normal matrix

static const vec4 globAmb = vec4(0.2, 0.2, 0.2, 1.0);
// Front and back material properties.
static const Material sphereFandB =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	50.0f
};

static const Light light0 =
{
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 0.0, 0.0)
};
vector<CollisionData> CollisionHandler;

vec3 curCam = { 0.0, 25.0, 10.0 };
vec3 curEye = { 0.0, 0.0, -10.0 };

vec3 cameraPositions[]{vec3(0.0, 18.0, 16.0), vec3 (0.0, 25.0, 10.0) };
vec3 eyePositions[]{ vec3(0.0, 10.0, 0.0), vec3 (0.0, 0.0, -10.0)};


static unsigned int
   programId,
   vertexShaderId,
   fragmentShaderId,
   modelViewMatLoc,
   projMatLoc,
   objectLoc,
   grassTexLoc,  //for grass texture 
   skyTexLoc,
	oneTexLoc,
	twoTexLoc,
	threeTexLoc,
	fourTexLoc,
	fiveTexLoc,
	sixTexLoc,
	sevenTexLoc,
	eightTexLoc,
	nineTexLoc,
	tenTexLoc,
	elevenTexLoc,
	twelveTexLoc,
	thirteenTexLoc,
	fourteenTexLoc,
	fifteenTexLoc,
	cueBallTexLoc,
	playingFieldTexLoc,
	woodTexLoc,
	blackPlasticTexLoc,
	floorTexLoc,
	wallTexLoc,
   buffer[13], ///add one more object
   vao[28], ///add one more object
	texture[23];   //Texture List


float zVal = 0; // Z Co-ordinates of the ball.
float d = 0.0; //Camera position

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Create shader program executable.
	vertexShaderId = setShader("vertex", "vertexShader.glsl");
	fragmentShaderId = setShader("fragment", "fragmentShader.glsl");
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glUseProgram(programId);

	//codes for OpenGL lighting
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.ambRefl"), 1, &sphereFandB.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.difRefl"), 1, &sphereFandB.difRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.specRefl"), 1, &sphereFandB.specRefl[0]);
	glUniform4fv(glGetUniformLocation(programId, "sphereFandB.emitCols"), 1, &sphereFandB.emitCols[0]);
	glUniform1f(glGetUniformLocation(programId, "sphereFandB.shininess"), sphereFandB.shininess);

	glUniform4fv(glGetUniformLocation(programId, "globAmb"), 1, &globAmb[0]);

	glUniform4fv(glGetUniformLocation(programId, "light0.ambCols"), 1, &light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.difCols"), 1, &light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.specCols"), 1, &light0.specCols[0]);
	glUniform4fv(glGetUniformLocation(programId, "light0.coords"), 1, &light0.coords[0]);


	///// Create a field  ///////////

	//Create VAO and VBO
	glGenVertexArrays(1, &vao[FIELD]);
	glGenBuffers(1, &buffer[FIELD_VERTICES]);
	glBindVertexArray(vao[FIELD]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[FIELD_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fieldVertices), fieldVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), 0);  //layout(location=0) in vec4 fieldCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), (void*)(sizeof(fieldVertices[0].coords)));  //layout(location=1) in vec2 fieldTexCoords;
	glEnableVertexAttribArray(1);

	///// Create a Sky /////////////

	//Create VAO and VBO
	glGenVertexArrays(1, &vao[SKY]);
	glGenBuffers(1, &buffer[SKY_VERTICES]);
	glBindVertexArray(vao[SKY]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[SKY_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), 0);  //layout(location=2) in vec4 skyCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), (void*)(sizeof(skyVertices[0].coords))); //layout(location=3) in vec2 skyTexCoords;
	glEnableVertexAttribArray(1);

	/////Create a sphere /////

	//Create VAO and VBO
	glGenVertexArrays(1, &vao[SPHERE]);
	glGenBuffers(1, &buffer[SPHERE_VERTICES]);

	//Binding VAO and VBO
	//Create the Table
	glGenVertexArrays(1, &vao[TABLE]);
	glGenBuffers(1, &buffer[TABLE_VERTICES]);
	//Binding Track VAO and VBO
	objects[1].SetIDs(vao[TABLE], buffer[TABLE_VERTICES], 0);
	objects[1].Setup();

	glGenVertexArrays(1, &vao[TABLEGREEN]);
	glGenBuffers(1, &buffer[TABLEGREEN_VERTICES]);
	//Binding Track VAO and VBO
	objects[19].SetIDs(vao[TABLEGREEN], buffer[TABLEGREEN_VERTICES], 0);
	objects[19].Setup();

	glGenVertexArrays(1, &vao[TABLEBLACK]);
	glGenBuffers(1, &buffer[TABLEBLACK_VERTICES]);
	//Binding Track VAO and VBO
	objects[18].SetIDs(vao[TABLEBLACK], buffer[TABLEBLACK_VERTICES], 0);
	objects[18].Setup();


	glGenVertexArrays(1, &vao[TABLEBROWN]);
	glGenBuffers(1, &buffer[TABLEBROWN_VERTICES]);
	//Binding Track VAO and VBO
	objects[17].SetIDs(vao[TABLEBROWN], buffer[TABLEBROWN_VERTICES], 0);
	objects[17].Setup();

	glGenVertexArrays(1, &vao[FLOOR]);
	glGenBuffers(1, &buffer[FLOOR_VERTICES]);
	//Binding Track VAO and VBO
	Floor.SetIDs(vao[FLOOR], buffer[FLOOR_VERTICES], 0);
	Floor.Setup();

	glGenVertexArrays(1, &vao[WALL]);
	glGenBuffers(1, &buffer[WALL_VERTICES]);
	//Binding Track VAO and VBO
	Wall.SetIDs(vao[WALL], buffer[WALL_VERTICES], 0);
	Wall.Setup();


	glGenVertexArrays(1, &vao[CUE]);
	glGenBuffers(1, &buffer[CUE_VERTICES]);
	//Binding Track VAO and VBO
	Cue.SetIDs(vao[CUE], buffer[CUE_VERTICES], 0);
	Cue.Setup();
	/*
	for (int i = 0; i < 16; i++)
	{
		Ball1.PosX[i] = 0;
		Ball1.PosY[i] = 0;
	}



	   objects[11].SetPosition(glm::vec3(-10, 0, 0));
	objects[2].SetPosition(glm::vec3(-5, 0, 0));
	objects[13].SetPosition(glm::vec3(0, 0, 0));
	objects[4].SetPosition(glm::vec3(5, 0, 0));
	objects[5].SetPosition(glm::vec3(10, 0, 0));
	objects[6].SetPosition(glm::vec3(-7.5, 0, 5));
	objects[10].SetPosition(glm::vec3(-2.5, 0, 5));
	objects[3].SetPosition(glm::vec3(2.5, 0, 5));
	objects[14].SetPosition(glm::vec3(7.5, 0, 5));
	objects[15].SetPosition(glm::vec3(-5, 0, 10));
	objects[8].SetPosition(glm::vec3(0, 0, 10));
	objects[1].SetPosition(glm::vec3(5, 0, 10));
	objects[7].SetPosition(glm::vec3(-2.5, 0, 15));
	objects[12].SetPosition(glm::vec3(2.5, 0, 15));
	objects[9].SetPosition(glm::vec3(0, 0, 20));
	objects[16].SetPosition(glm::vec3(0, 0, 30));

	   objects[11].SetPosition(glm::vec3(-5, 0, 0));
	objects[2].SetPosition(glm::vec3(-2.5, 0, 0));
	objects[13].SetPosition(glm::vec3(0, 0, 0));
	objects[4].SetPosition(glm::vec3(2.5, 0, 0));
	objects[5].SetPosition(glm::vec3(5, 0, 0));
	objects[6].SetPosition(glm::vec3(-3.75, 0, 2.5));
	objects[10].SetPosition(glm::vec3(-1.25, 0, 2.5));
	objects[3].SetPosition(glm::vec3(1.25, 0, 2.5));
	objects[14].SetPosition(glm::vec3(3.75, 0, 2.5));
	objects[15].SetPosition(glm::vec3(-2.5, 0, 5));
	objects[8].SetPosition(glm::vec3(0, 0, 5));
	objects[1].SetPosition(glm::vec3(2.5, 0, 5));
	objects[7].SetPosition(glm::vec3(-1.25, 0, 7.5));
	objects[12].SetPosition(glm::vec3(1.25, 0, 7.5));
	objects[9].SetPosition(glm::vec3(0, 0, 10));
	objects[16].SetPosition(glm::vec3(0, 0, 30));
	*/
	objects[11].SetPosition(glm::vec3(-5, 0, 0));
	objects[2].SetPosition(glm::vec3(-2.5, 0, 0));
	objects[13].SetPosition(glm::vec3(0, 0, 0));
	objects[4].SetPosition(glm::vec3(2.5, 0, 0));
	objects[5].SetPosition(glm::vec3(5, 0, 0));
	objects[6].SetPosition(glm::vec3(-3.75, 0, 2.5));
	objects[10].SetPosition(glm::vec3(-1.25, 0, 2.5));
	objects[3].SetPosition(glm::vec3(1.25, 0, 2.5));
	objects[14].SetPosition(glm::vec3(3.75, 0, 2.5));
	objects[15].SetPosition(glm::vec3(-2.5, 0, 5));
	objects[8].SetPosition(glm::vec3(0, 0, 5));
	objects[1].SetPosition(glm::vec3(2.5, 0, 5));
	objects[7].SetPosition(glm::vec3(-1.25, 0, 7.5));
	objects[12].SetPosition(glm::vec3(1.25, 0, 7.5));
	objects[9].SetPosition(glm::vec3(0, 0, 10));
	objects[16].SetPosition(glm::vec3(0, 0, 30));


	//Empties for colliders
	objects[20].SetPosition(glm::vec3(-12, 0, 35));  //BOTTOM LEFT HOLE
	objects[21].SetPosition(glm::vec3(12, 0, 35)); //BOTTOM RIGHT HOLE
	objects[22].SetPosition(glm::vec3(12, 0, 14)); //MIDDLE LEFT HOLE
	objects[23].SetPosition(glm::vec3(-12, 0, 14)); //MIDDLE RIGHT HOLE
	objects[24].SetPosition(glm::vec3(12, 0, -12)); //TOP LEFT HOLE
	objects[25].SetPosition(glm::vec3(-12, 0, -12)); //TOP RIGHT HOLE
	objects[26].SetPosition(glm::vec3(-12, 0, 11)); //WALL
	objects[27].SetPosition(glm::vec3(12, 0, 11)); //WALL
	objects[28].SetPosition(glm::vec3(0, 0, -12)); //WALL
	objects[29].SetPosition(glm::vec3(0, 0, 35)); //WALL


	Floor.SetPosition(glm::vec3(0, -50, 0)); //WALL
	Wall.SetPosition(glm::vec3(0, -50, -80)); //WALL

	//Create the Ball 1
	glGenVertexArrays(1, &vao[BALL1]);
	glGenBuffers(1, &buffer[BALL1_VERTICES]);
	//Binding Track VAO and VBO
	objects[1].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[1].Setup();

	objects[2].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[2].Setup();

	objects[3].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[3].Setup();

	objects[4].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[4].Setup();

	objects[5].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[5].Setup();

	objects[6].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[6].Setup();

	objects[7].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[7].Setup();

	objects[8].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[8].Setup();

	objects[9].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[9].Setup();

	objects[10].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[10].Setup();

	objects[11].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[11].Setup();

	objects[12].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[12].Setup();

	objects[13].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[13].Setup();

	objects[14].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[14].Setup();

	objects[15].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[15].Setup();

	objects[16].SetIDs(vao[BALL1], buffer[BALL1_VERTICES], 0);
	objects[16].Setup();

	//COLLIDER EMPTIES
	objects[20].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[20].Setup();

	objects[21].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[21].Setup();

	objects[22].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[22].Setup();

	objects[23].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[23].Setup();

	objects[24].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[24].Setup();

	objects[25].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[25].Setup();

	objects[26].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[26].Setup();

	objects[27].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[27].Setup();

	objects[28].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[28].Setup();

	objects[29].SetIDs(vao[COLLIDERVISUAL], buffer[COLLIDERVISUAL_VERTICES], 0);
	objects[29].Setup();

	Floor.SetIDs(vao[FLOOR], buffer[FLOOR_VERTICES], 0);
	Floor.Setup();


	Wall.SetIDs(vao[WALL], buffer[WALL_VERTICES], 0);
    Wall.Setup();
   // Obtain projection matrix uniform location and set value.
   projMatLoc = glGetUniformLocation(programId,"projMat");   //uniform mat4 projMat;
   projMat = frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0); 
   glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));
   
   // Obtain modelview matrix uniform and object uniform locations.
   modelViewMatLoc = glGetUniformLocation(programId,"modelViewMat");   //uniform mat4 modelViewMat;
   objectLoc = glGetUniformLocation(programId, "object");  //uniform uint object;

   // Load the images.
   std::string TexNames[] = {
		"Textures/grass.bmp",
		"Textures/sky.png",
		"Textures/1.png",
		"Textures/2.png",
		"Textures/3.png",
		"Textures/4.png",
		"Textures/5.png",
		"Textures/6.png",
		"Textures/7.png",
		"Textures/8.png",
		"Textures/9.png",
		"Textures/10.png",
		"Textures/11.png",
		"Textures/12.png",
		"Textures/13.png",
		"Textures/14.png",
		"Textures/15.png",
		"Textures/CueBall.png",
		"Textures/Wood.png",
		"Textures/PlayingField.png",
		"Textures/BlackPlastic.png",
		"Textures/Floor.png",
		"Textures/Wall.png"
   };

   // Create texture ids.
   glGenTextures(22, texture);

   int width, height;
   unsigned char* data;

   // Bind grass image.
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture[0]);

   //load image data using SOIL library
   data = SOIL_load_image(TexNames[0].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   grassTexLoc = glGetUniformLocation(programId, "grassTex");
   glUniform1i(grassTexLoc, 0); //send texture to shader

   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, texture[1]);

   data = SOIL_load_image(TexNames[1].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   skyTexLoc = glGetUniformLocation(programId, "skyTex");
   glUniform1i(skyTexLoc, 1); //send texture to shader

   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D, texture[2]);

   data = SOIL_load_image(TexNames[2].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   oneTexLoc = glGetUniformLocation(programId, "oneTex");
   glUniform1i(oneTexLoc, 2); //send texture to shader

   glActiveTexture(GL_TEXTURE3);
   glBindTexture(GL_TEXTURE_2D, texture[3]);

   data = SOIL_load_image(TexNames[3].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   twoTexLoc = glGetUniformLocation(programId, "twoTex");
   glUniform1i(twoTexLoc, 3); //send texture to shader

   glActiveTexture(GL_TEXTURE4);
   glBindTexture(GL_TEXTURE_2D, texture[4]);

   data = SOIL_load_image(TexNames[4].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   threeTexLoc = glGetUniformLocation(programId, "threeTex");
   glUniform1i(threeTexLoc, 4); //send texture to shader

   glActiveTexture(GL_TEXTURE5);
   glBindTexture(GL_TEXTURE_2D, texture[5]);

   data = SOIL_load_image(TexNames[5].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   fourTexLoc = glGetUniformLocation(programId, "fourTex");
   glUniform1i(fourTexLoc,5); //send texture to shader

   glActiveTexture(GL_TEXTURE6);
   glBindTexture(GL_TEXTURE_2D, texture[6]);

   data = SOIL_load_image(TexNames[6].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   fiveTexLoc = glGetUniformLocation(programId, "fiveTex");
   glUniform1i(fiveTexLoc, 6); //send texture to shader


   glActiveTexture(GL_TEXTURE7);
   glBindTexture(GL_TEXTURE_2D, texture[7]);

   data = SOIL_load_image(TexNames[7].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   sixTexLoc = glGetUniformLocation(programId, "sixTex");
   glUniform1i(sixTexLoc, 7); //send texture to shader


   glActiveTexture(GL_TEXTURE8);
   glBindTexture(GL_TEXTURE_2D, texture[8]);

   data = SOIL_load_image(TexNames[8].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   sevenTexLoc = glGetUniformLocation(programId, "sevenTex");
   glUniform1i(sevenTexLoc,8); //send texture to shader


   glActiveTexture(GL_TEXTURE9);
   glBindTexture(GL_TEXTURE_2D, texture[9]);

   data = SOIL_load_image(TexNames[9].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   eightTexLoc = glGetUniformLocation(programId, "eightTex");
   glUniform1i(eightTexLoc, 9); //send texture to shader


   glActiveTexture(GL_TEXTURE10);
   glBindTexture(GL_TEXTURE_2D, texture[10]);

   data = SOIL_load_image(TexNames[10].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   nineTexLoc = glGetUniformLocation(programId, "nineTex");
   glUniform1i(nineTexLoc, 10); //send texture to shader


   glActiveTexture(GL_TEXTURE11);
   glBindTexture(GL_TEXTURE_2D, texture[11]);

   data = SOIL_load_image(TexNames[11].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   tenTexLoc = glGetUniformLocation(programId, "tenTex");
   glUniform1i(tenTexLoc, 11); //send texture to shader


   glActiveTexture(GL_TEXTURE12);
   glBindTexture(GL_TEXTURE_2D, texture[12]);

   data = SOIL_load_image(TexNames[12].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   elevenTexLoc = glGetUniformLocation(programId, "elevenTex");
   glUniform1i(elevenTexLoc, 12); //send texture to shader


   glActiveTexture(GL_TEXTURE13);
   glBindTexture(GL_TEXTURE_2D, texture[13]);

   data = SOIL_load_image(TexNames[13].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   twelveTexLoc = glGetUniformLocation(programId, "twelveTex");
   glUniform1i(twelveTexLoc, 13); //send texture to shader


   glActiveTexture(GL_TEXTURE14);
   glBindTexture(GL_TEXTURE_2D, texture[14]);

   data = SOIL_load_image(TexNames[14].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   thirteenTexLoc = glGetUniformLocation(programId, "thirteenTex");
   glUniform1i(thirteenTexLoc, 14); //send texture to shader


   glActiveTexture(GL_TEXTURE15);
   glBindTexture(GL_TEXTURE_2D, texture[15]);

   data = SOIL_load_image(TexNames[15].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   fourteenTexLoc = glGetUniformLocation(programId, "fourteenTex");
   glUniform1i(fourteenTexLoc, 15); //send texture to shader


   glActiveTexture(GL_TEXTURE16);
   glBindTexture(GL_TEXTURE_2D, texture[16]);

   data = SOIL_load_image(TexNames[16].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   fifteenTexLoc = glGetUniformLocation(programId, "fifteenTex");
   glUniform1i(fifteenTexLoc, 16); //send texture to shader


   glActiveTexture(GL_TEXTURE17);
   glBindTexture(GL_TEXTURE_2D, texture[17]);

   data = SOIL_load_image(TexNames[17].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   cueBallTexLoc = glGetUniformLocation(programId, "cueBallTex");
   glUniform1i(cueBallTexLoc, 17); //send texture to shader

   glActiveTexture(GL_TEXTURE18);
   glBindTexture(GL_TEXTURE_2D, texture[18]);

   data = SOIL_load_image(TexNames[18].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   playingFieldTexLoc = glGetUniformLocation(programId, "playingFieldTex");
   glUniform1i(playingFieldTexLoc, 18); //send texture to shader

   glActiveTexture(GL_TEXTURE19);
   glBindTexture(GL_TEXTURE_2D, texture[19]);

   data = SOIL_load_image(TexNames[19].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   woodTexLoc = glGetUniformLocation(programId, "woodTex");
   glUniform1i(woodTexLoc, 19); //send texture to shader
   
   glActiveTexture(GL_TEXTURE20);
   glBindTexture(GL_TEXTURE_2D, texture[20]);
   data = SOIL_load_image(TexNames[20].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   blackPlasticTexLoc = glGetUniformLocation(programId, "blackPlasticTex");
   glUniform1i(blackPlasticTexLoc, 20); //send texture to shader

 
   glActiveTexture(GL_TEXTURE21);
   glBindTexture(GL_TEXTURE_2D, texture[21]);
   data = SOIL_load_image(TexNames[21].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   floorTexLoc = glGetUniformLocation(programId, "floorTex");
   glUniform1i(floorTexLoc, 21); //send texture to shader

   glActiveTexture(GL_TEXTURE22);
   glBindTexture(GL_TEXTURE_2D, texture[22]);
   data = SOIL_load_image(TexNames[22].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   SOIL_free_image_data(data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   wallTexLoc = glGetUniformLocation(programId, "wallTex");
   glUniform1i(wallTexLoc, 22); //send texture to shader


}

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Calculate and update modelview matrix.
   modelViewMat = mat4(1.0);
   modelViewMat = lookAt(curCam, curEye, vec3(0.0, 1.0, 0.0));
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, value_ptr(modelViewMat)); 

   // Draw field.
   //glUniform1ui(objectLoc, FIELD);  //if (object == FIELD)
   //glBindVertexArray(vao[FIELD]);
   //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // Draw sky.
   //glUniform1ui(objectLoc, SKY);  //if (object == SKY)
   //glBindVertexArray(vao[SKY]);
   //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   
   //Draw my Model
   vec3 posTable = vec3(0.0, 0.0, 0.0f);
   objects[0].updateModelMatrix(modelViewMatLoc, d, 0.2f, posTable, vec3(0, 0, 0), curCam, curEye);
   glUniform1ui(objectLoc, TABLE);  //if (object == MYMODEL)
   objects[0].Draw();
   
   //Draw my Model
   vec3 posTableGreen = vec3(0.0, 25.0, 0.0f);
   objects[19].updateModelMatrix(modelViewMatLoc, d, 0.2f, posTableGreen, vec3(0,0,0), curCam, curEye);
   glUniform1ui(objectLoc, TABLEGREEN);  //if (object == MYMODEL)
   objects[19].Draw();

   //Draw my Model
   vec3 posTableBlack = vec3(0.0, 25.0, 0.0f);
   objects[18].updateModelMatrix(modelViewMatLoc, d, 0.2f, posTableBlack, vec3(0, 0, 0), curCam, curEye);
   glUniform1ui(objectLoc, TABLEBLACK);  //if (object == MYMODEL)
   objects[18].Draw();

   //Draw my Model
   vec3 posTableBrown = vec3(0.0, 25.0, 0.0f);
   objects[17].updateModelMatrix(modelViewMatLoc, d, 0.2f, posTableBrown, vec3(0, 0, 0), curCam, curEye);
   glUniform1ui(objectLoc, TABLEBROWN);  //if (object == MYMODEL)
   objects[17].Draw();

   //Draw my Model
   vec3 posCue = vec3(1.0, 25.0, 0.0f);
   Cue.updateModelMatrix(modelViewMatLoc, d, 0.2f, posCue, vec3(0, 0, 0), curCam, curEye);
   glUniform1ui(objectLoc, CUE);  //if (object == MYMODEL)
   Cue.Draw();
   //glUniform3fv(glGetUniformLocation(programId, "PosX"), 16*3, &Ball1.PosX[0]);
   //lUniform1f(glGetUniformLocation(programId, "PosX"), Ball1.PosX[0]);
   //glUniform4f(glGetUniformLocation(programId, "PosX"), Ball1.PosX[0], Ball1.PosX[1], Ball1.PosX[2], Ball1.PosX[3]);

	vec3 posBall = vec3(-10.0 + (5.0 * 2), 30.0, -20.0f);
	objects[1].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[1].GetPosition(), objects[1].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL1);  //if (object == MYMODEL)
	objects[1].Draw();

	objects[2].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[2].GetPosition(), objects[2].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL2);  //if (object == MYMODEL)
	objects[2].Draw();

	objects[3].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[3].GetPosition(), objects[3].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL3);  //if (object == MYMODEL)
	objects[3].Draw();

	objects[4].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[4].GetPosition(), objects[4].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL4);  //if (object == MYMODEL)
	objects[4].Draw();

	objects[5].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[5].GetPosition(), objects[5].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL5);  //if (object == MYMODEL)
	objects[5].Draw();

	objects[6].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[6].GetPosition(), objects[6].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL6);  //if (object == MYMODEL)
	objects[6].Draw();

	objects[7].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[7].GetPosition(), objects[7].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL7);  //if (object == MYMODEL)
	objects[7].Draw();

	objects[8].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[8].GetPosition(), objects[8].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL8);  //if (object == MYMODEL)
	objects[8].Draw();

	objects[9].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[9].GetPosition(), objects[9].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL9);  //if (object == MYMODEL)
	objects[9].Draw();

	objects[10].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[10].GetPosition(), objects[10].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL10);  //if (object == MYMODEL)
	objects[10].Draw();

	objects[11].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[11].GetPosition(), objects[11].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL11);  //if (object == MYMODEL)
	objects[11].Draw();

	objects[12].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[12].GetPosition(), objects[12].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL12);  //if (object == MYMODEL)
	objects[12].Draw();

	objects[13].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[13].GetPosition(), objects[13].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL13);  //if (object == MYMODEL)
	objects[13].Draw();

	objects[14].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[14].GetPosition(), objects[14].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL14);  //if (object == MYMODEL)
	objects[14].Draw();

	objects[15].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[15].GetPosition(), objects[15].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, BALL15);  //if (object == MYMODEL)
	objects[15].Draw();

	objects[16].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[16].GetPosition(), objects[16].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, CUEBALL);  //if (object == MYMODEL)
	objects[16].Draw();

	objects[20].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[20].GetPosition(), objects[20].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[20].Draw();

	objects[21].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[21].GetPosition(), objects[21].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[21].Draw();

	objects[22].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[22].GetPosition(), objects[22].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[22].Draw();

	objects[23].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[23].GetPosition(), objects[23].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[23].Draw();

	objects[24].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[24].GetPosition(), objects[24].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[24].Draw();

	objects[25].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[25].GetPosition(), objects[25].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[25].Draw();

	objects[26].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[26].GetPosition(), objects[26].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[26].Draw();

	objects[27].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[27].GetPosition(), objects[27].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[27].Draw();

	objects[28].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[28].GetPosition(), objects[28].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[28].Draw();

	objects[29].updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + objects[29].GetPosition(), objects[29].GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, COLLIDERVISUAL);  //if (object == MYMODEL)
	objects[29].Draw();

	Floor.updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + Floor.GetPosition(), Floor.GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, FLOOR);  //if (object == MYMODEL)
	Floor.Draw();


	Wall.updateModelMatrix(modelViewMatLoc, d, 0.2f, posBall + Wall.GetPosition(), Wall.GetOri(), curCam, curEye);
	glUniform1ui(objectLoc, WALL);  //if (object == MYMODEL)
	Wall.Draw();

   glutSwapBuffers();
}
void collisionManager()
{
	CollisionData data;
	bool reverse = true;
	for (int goloop = 0; goloop < 30; goloop++)
	{
		for (int subloop = goloop + 1; subloop < 30; subloop++)
		{
			if (goloop != subloop)
			{
				if (objects[goloop].GetType() == 0 && objects[subloop].GetType() == 0)
				{
					//This needs to go only if True
					
					bool isCollision = objects[goloop].GetBall()->GetCollider()->CollideCheck(*objects[subloop].GetBall()->GetCollider(), data);
					if (isCollision == true)
					{
						data.object1 = &objects[goloop];
						data.object2 = &objects[subloop];
						CollisionHandler.push_back(data);
						
					}

				}
				if (objects[goloop].GetType() == 0 && objects[subloop].GetType() == 1)
				{
					bool isCollision = objects[goloop].GetBall()->GetCollider()->CollideCheck(*objects[subloop].GetWorldObject()->GetCollider(), data);
					if (isCollision == true)
					{
						data.object1 = &objects[goloop];
						data.object2 = &objects[subloop];
						CollisionHandler.push_back(data);

					}
				}

				if (objects[goloop].GetType() == 1 && objects[subloop].GetType() == 0)
					//objects[goloop].GetWorldObject()->GetCollider()->CollideCheck(*objects[subloop].GetBall()->GetCollider());
					;
				if (objects[goloop].GetType() == 1 && objects[subloop].GetType() == 1)
					//objects[goloop].GetWorldObject()->GetCollider()->CollideCheck(*objects[subloop].GetWorldObject()->GetCollider());
					;
			}
		}
	}
	for (int h = 0; h < CollisionHandler.size(); h++)
	{

		CollisionData curdata = CollisionHandler[h];
		if (curdata.depth >= 0)
		{
			if (curdata.object1->GetType() == 0 && curdata.object2->GetType() == 0) //BALL x BALL
			{

				if ((curdata.object1->GetBall()->m > 800 && curdata.object1->GetBall()->collisionball == 0) && curdata.object2->GetBall()->m < 100) //Holes
				{
					curdata.object2->SetPosition(vec3(1000, 1000, 1000));
					curdata.object2->SetType(2);
					CollisionHandler.erase(CollisionHandler.begin()+h);
					h--;
				}
				if ((curdata.object2->GetBall()->m > 800 && curdata.object2->GetBall()->collisionball ==0) && curdata.object1->GetBall()->m < 100) //Holes
				{
					curdata.object1->SetPosition(vec3(1000, 1000, 1000));
					curdata.object1->SetType(2);
					CollisionHandler.erase(CollisionHandler.begin() + h);
					h--;
				}
				if ((curdata.object1->GetBall()->m > 800 && curdata.object1->GetBall()->collisionball != 0) && curdata.object2->GetBall()->m < 100) //Boundaries
				{
					curdata.object2->SetPosition(curdata.object2->GetPosition() + curdata.normal * curdata.depth);
					curdata.object2->GetBall()->Bounce(curdata.object1->GetBall()->GetVel());
					CollisionHandler.erase(CollisionHandler.begin() + h);
					h--;
				}
				if ((curdata.object2->GetBall()->m > 800 && curdata.object2->GetBall()->collisionball != 0) && curdata.object1->GetBall()->m < 100) //Boundaries
				{
					curdata.object1->SetPosition(curdata.object1->GetPosition() + curdata.normal * curdata.depth);
					curdata.object1->GetBall()->Bounce(curdata.object1->GetBall()->GetVel());
					CollisionHandler.erase(CollisionHandler.begin() + h);
					h--;
				}
				if ((curdata.object1->GetBall()->m < 100 && curdata.object1->GetBall()->collisionball == NULL) && (curdata.object2->GetBall()->m < 100 && curdata.object2->GetBall()->collisionball == NULL)) 
				{
					//curdata.object2->GetBall()->Bounce(curdata.object1->GetBall()->GetVel());
					//curdata.object2->SetPosition(curdata.object2->GetPosition() + curdata.normal * curdata.depth);
					
					
					//curdata.object1->GetBall()->Bounce(curdata.object1->GetBall()->GetVel());
					//curdata.object2->GetBall()->Bounce(curdata.object1->GetBall()->GetVel() * vec3(-1, -1, -1));

					
					//curdata.object1->SetPosition(curdata.object1->GetPosition() - curdata.depth/ 2 * curdata.normal  );
					//curdata.object2->SetPosition(curdata.object2->GetPosition() + curdata.depth/ 2 * curdata.normal  );

					//curdata.object2->GetBall()->AddForce(-curdata.object1->GetBall()->GetVel() - curdata.depth / 2 * curdata.normal);
					//curdata.object2->GetBall()->AddForce(curdata.object1->GetBall()->GetVel() + curdata.depth / 2 * curdata.normal);

					/*
					curdata.object2->SetPosition(curdata.object2->GetPosition() - curdata.normal * curdata.depth);
					curdata.object1->SetPosition(curdata.object1->GetPosition() - curdata.depth / 2 * curdata.normal);
					curdata.object2->SetPosition(curdata.object2->GetPosition() + curdata.depth / 2 * curdata.normal);
					*/

					//curdata.point - curdata.object1->GetPosition();
					CollisionHandler.erase(CollisionHandler.begin() + h);

					h--;
				}





				else //Bounce the balls
				{

					//curdata.object1->SetPosition((curdata.object1->GetPosition() + curdata.normal * curdata.depth) * vec3(0.5, 0.5, 0.5));
					//curdata.object2->SetPosition((curdata.object2->GetPosition() + curdata.normal * curdata.depth) * vec3(0.5, 0.5, 0.5));
					//collision resolution, changing velocity
				}
				CollisionHandler.erase(CollisionHandler.begin() + h);
				h--;
			}
			if (curdata.object1->GetType() == 0 && curdata.object2->GetType() == 1) //BALL X PLANE (Floor only)
			{

			}
		}
	}

}


void animate() {;
	zVal = zVal - 0.2;
	if (zVal < -25.0) zVal = 0.0;
	objects[1].Update(0.1f, glm::vec3(0, 0, 0));
	objects[2].Update(0.1f, glm::vec3(0, 0, 0));
	objects[3].Update(0.1f, glm::vec3(0, 0, 0));
	objects[4].Update(0.1f, glm::vec3(0, 0, 0));
	objects[5].Update(0.1f, glm::vec3(0, 0, 0));
	objects[6].Update(0.1f, glm::vec3(0, 0, 0));
	objects[7].Update(0.1f, glm::vec3(0, 0, 0));
	objects[8].Update(0.1f, glm::vec3(0, 0, 0));
	objects[9].Update(0.1f, glm::vec3(0, 0, 0));
	objects[10].Update(0.1f, glm::vec3(0, 0, 0));
	objects[11].Update(0.1f, glm::vec3(0, 0, 0));
	objects[12].Update(0.1f, glm::vec3(0, 0, 0));
	objects[13].Update(0.1f, glm::vec3(0, 0, 0));
	objects[14].Update(0.1f, glm::vec3(0, 0, 0));
	objects[15].Update(0.1f, glm::vec3(0, 0, 0));
	objects[16].Update(0.1f, glm::vec3(0, 0, 0));
	collisionManager();

	// refresh screen 
	glutPostRedisplay();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h); 
}

// Keyboard input processing routine.
void KeyInputDown(unsigned char key, int x, int y)
{
	ObjectType::keys[key] = true;
	std::cout << "Key pressed: " << key << " : " << ObjectType::keys[key] << std::endl;

   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

void KeyInputUp(unsigned char key, int x, int y)
{
	ObjectType::keys[key] = false;
	std::cout << "Key de-pressed: " << key << " : " << ObjectType::keys[key] << std::endl;
}

// Callback routine for non-ASCII key entry.
void SpecialKeyInputDown(int key, int x, int y)
{
	ObjectType::specialKeys[key] = true;
	std::cout << "Special key pressed: " << key << " : " << ObjectType::specialKeys[key] << std::endl;

   if (key == 104) 
   {
	   curCam = cameraPositions[1];
	   curEye = eyePositions[1];
   }
   if (key == 105) 
   {
	   curCam = cameraPositions[0];
	   curEye = eyePositions[0];
   }
   //glutPostRedisplay();
}

void SpecialKeyInputUp(int key, int x, int y)
{
	ObjectType::specialKeys[key] = false;
	std::cout << "Special key de-pressed: " << key << " : " << ObjectType::specialKeys[key] << std::endl;
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the left and right arrow keys to move the viewpoint over the field." << endl; 
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_CORE_PROFILE);
   glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("model loading example");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutIdleFunc(animate); ///animation function
   glutKeyboardFunc(KeyInputDown);
   glutKeyboardUpFunc(KeyInputUp);
   glutSpecialFunc(SpecialKeyInputDown);
   glutSpecialUpFunc(SpecialKeyInputUp);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}

