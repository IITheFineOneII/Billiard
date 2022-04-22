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

in vec2 texCoordsExport;
in vec3 normalExport;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};

struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};

uniform Light light0;
uniform vec4 globAmb;
uniform Material sphereFandB;

uniform sampler2D grassTex;
uniform sampler2D skyTex;
uniform sampler2D oneTex;
uniform sampler2D twoTex;
uniform sampler2D threeTex;
uniform sampler2D fourTex;
uniform sampler2D fiveTex;
uniform sampler2D sixTex;
uniform sampler2D sevenTex;
uniform sampler2D eightTex;
uniform sampler2D nineTex;
uniform sampler2D tenTex;
uniform sampler2D elevenTex;
uniform sampler2D twelveTex;
uniform sampler2D thirteenTex;
uniform sampler2D fourteenTex;
uniform sampler2D fifteenTex;
uniform sampler2D cueBallTex;
uniform sampler2D playingFieldTex;
uniform sampler2D woodTex;
uniform sampler2D blackPlasticTex;
uniform sampler2D floorTex;
uniform sampler2D wallTex;
uniform uint object;

out vec4 colorsOut;

vec4 fieldTexColor, skyTexColor, oneTexColor, twoTexColor, threeTexColor, fourTexColor, fiveTexColor, sixTexColor, sevenTexColor, eightTexColor, nineTexColor, tenTexColor, elevenTexColor,twelveTexColor, thirteenTexColor, fourteenTexColor, fifteenTexColor, cueBallTexColor, playingFieldTexColor, woodTexColor, blackPlasticTexColor, floorTexColor, wallTexColor;
vec3 normal, lightDirection;
vec4 fAndBDif;

void main(void)
{  
   fieldTexColor = texture(grassTex, texCoordsExport);
   skyTexColor = texture(skyTex, texCoordsExport);
   oneTexColor = texture(oneTex, texCoordsExport);
   twoTexColor = texture(twoTex, texCoordsExport);
   threeTexColor = texture(threeTex, texCoordsExport);
   fourTexColor = texture(fourTex, texCoordsExport);
   fiveTexColor = texture(fiveTex, texCoordsExport);
   sixTexColor = texture(sixTex, texCoordsExport);
   sevenTexColor = texture(sevenTex, texCoordsExport);
   eightTexColor = texture(eightTex, texCoordsExport);
   nineTexColor = texture(nineTex, texCoordsExport);
   tenTexColor = texture(tenTex, texCoordsExport);
   elevenTexColor = texture(elevenTex, texCoordsExport);
   twelveTexColor = texture(twelveTex, texCoordsExport);
   thirteenTexColor = texture(thirteenTex, texCoordsExport);
   fourteenTexColor = texture(fourteenTex, texCoordsExport);
   fifteenTexColor = texture(fifteenTex, texCoordsExport);
   cueBallTexColor = texture(cueBallTex, texCoordsExport);
   playingFieldTexColor = texture(playingFieldTex, texCoordsExport);
   woodTexColor = texture(woodTex, texCoordsExport);
   blackPlasticTexColor = texture(blackPlasticTex, texCoordsExport);
   floorTexColor = texture(floorTex, texCoordsExport);
   wallTexColor = texture(wallTex, texCoordsExport);
   if (object == FIELD) colorsOut = fieldTexColor;
   if (object == SKY) colorsOut = skyTexColor;
   if (object == SPHERE) {
    normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut =  vec4(vec3(min(fAndBDif, vec4(1.0))), 1.0);
   }
   if (object == TABLE) {
    colorsOut = fieldTexColor;
   }
   if (object == BALL1) {
    normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = oneTexColor;
   }
    if (object == BALL2) {
        normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = twoTexColor;
   }
     if (object == BALL3) {
         normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = threeTexColor;
   }
    if (object == BALL4) {
        normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = fourTexColor;
   }
    if (object == BALL5) {
        normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = fiveTexColor;
   }
   if (object == BALL6) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = sixTexColor;
   }
   if (object == BALL7) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = sevenTexColor;
   }
   if (object == BALL8) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = eightTexColor;
   }
   if (object == BALL9) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = nineTexColor;
   }
   if (object == BALL10) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = tenTexColor;
   }
   if (object == BALL11) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = elevenTexColor;
   }
   if (object == BALL12) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = twelveTexColor;
   }
   if (object == BALL13) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = thirteenTexColor;
   }
   if (object == BALL14) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = fourteenTexColor;
   }
   if (object == BALL15) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = fifteenTexColor;
   }
   if (object == CUEBALL) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = fifteenTexColor;
   }

      if (object == TABLEGREEN) {
          normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = woodTexColor;
	//colorsOut = vec4(1,0,1,1);
   }

    if (object == TABLEBLACK) {
        normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = blackPlasticTexColor;
	//colorsOut = vec4(1,0,1,1);
   }

       if (object == TABLEBROWN) {
           normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
    colorsOut = playingFieldTexColor;
	//colorsOut = vec4(1,0,1,1);
   }
   if (object == COLLIDERVISUAL) {
       normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
	colorsOut = vec4(1,0,1,0.1);
   }
      if (object == FLOOR) {
          normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
      colorsOut = floorTexColor;
      	//colorsOut = vec4(1,0,1,1);
   }

         if (object == WALL) {
             normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
        colorsOut = wallTexColor;
	//colorsOut = vec4(0.8,0.8,0.3,1);
   }
            if (object == CUE) {
                normal = normalize(normalExport);
	lightDirection = normalize(vec3(light0.coords));
	fAndBDif = max(dot(normal, lightDirection), 0.0f) * (light0.difCols * sphereFandB.difRefl); 
        colorsOut = playingFieldTexColor;
   }
}