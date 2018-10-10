#pragma once

const int MAPSIZE_H = 800;
const int MAPSIZE_W = 800;
const int MAPSIZE_D = 600;
const int VIEWANGLE = 60;
const int DELAY = 10;
const int STAR_NUM = 5000;
const int MAX_LEN = 15;
const int MAX_LOAD_NUM = 30;

const float PIE = 3.1415926535;
const float DEG = PIE / 180;
const float RAD = 180 / PIE;


enum SceneType
{
	SCENE_LOGIN,
	SCENE_STAGE,
	SCENE_OVER,
	SCENE_END,
};

enum ObjType
{
	OBJ_PLAYER,
	OBJ_STAR,
	OBJ_END,
};

enum VERTEX
{ 
	TOP,
	BOTTOM,
	VERTEX_END
};

enum PASS
{
	NONPASS,
	PASS,
	COREPASS,
	PASS_END
};

enum CAMERASTATE { TURN, GO, MOVE };

struct Vec4 {
	float x;
	float y;
	float z;
	float w;
};

struct Vec3 {
	float x;
	float y;
	float z;
};

struct Torus {
	float x;
	float y;
	int IsPassed;
};

struct Vec2 {
	float x;
	float y;
};

struct LightPara
{
	float Ambient[4];
	float Diffuse[4];
	float Specular[4];
	float Pos[4];
};

