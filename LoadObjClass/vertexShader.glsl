#version 430 core

#define FIELD 0
#define SKY 1
#define SPHERE 2
#define TABLE 3
#define BALL1 4
#define BALL2 5
#define BALL3 6
#define BALL4 7
#define BALL5 8
#define BALL6 9
#define BALL7 10
#define BALL8 11
#define BALL9 12
#define BALL10 13
#define BALL11 14
#define BALL12 15
#define BALL13 16
#define BALL14 17
#define BALL15 18
#define CUEBALL 19
#define TABLEGREEN 20
#define TABLEBLACK 21
#define TABLEBROWN 22
#define COLLIDERVISUAL 23
#define FLOOR 24
#define WALL 25
#define CUE 26

layout(location=0) in vec4 Coords;
layout(location=1) in vec2 TexCoords;
layout(location=2) in vec4 sphereCoords;
layout(location=3) in vec3 sphereNormals;

layout(location=4) in vec3 objCoords;
layout(location=5) in vec3 objNormals;
layout(location=6) in vec2 objTexCoords;

uniform mat4 modelViewMat;
uniform mat4 projMat;
uniform uint object;
uniform vec4 PosX;

out vec2 texCoordsExport;
out vec3 normalExport;

vec4 coords;

void main(void)
{   
   if (object == FIELD)
   {
      coords = Coords;
      texCoordsExport = TexCoords;
   }
   if (object == SKY)
   {
      coords = Coords;
      texCoordsExport = TexCoords;
   }
   if (object == SPHERE)
   {
      coords = sphereCoords;
      normalExport = sphereNormals;
   }
   	if (object == TABLE)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
	if (object ==BALL1)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
    if (object ==BALL2)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL3)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL4)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL5)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL6)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

    if (object ==BALL7)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL8)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL9)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

        if (object ==BALL10)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

    if (object ==BALL11)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
        if (object ==BALL12)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
        if (object ==BALL13)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
        if (object ==BALL14)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
        if (object ==BALL15)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
        if (object ==CUEBALL)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
	if (object == TABLEGREEN)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
		if (object == TABLEBLACK)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
    		if (object == TABLEBROWN)
    {
      coords = vec4(objCoords, 1.0f);
      normalExport = objNormals;
      texCoordsExport = objTexCoords;
    }
            if (object ==COLLIDERVISUAL)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

     if (object ==FLOOR)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

         if (object ==WALL)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }
             if (object ==CUE)
    {
        coords = vec4(objCoords.x + PosX[gl_InstanceID],objCoords.y,objCoords.z,1.0); //[gl_InstanceID]
        normalExport = objNormals;
        texCoordsExport = objTexCoords;

    }

   gl_Position = projMat * modelViewMat * coords;
}
