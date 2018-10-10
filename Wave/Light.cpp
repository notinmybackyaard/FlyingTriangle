#include "Light.h"
#include "Player.h"

CLight::CLight()
{
}

CLight::~CLight()
{
}

void CLight::Update()
{
	// 플레이어 위치에 따라 조명 위치 갱신
	Set1.Pos[0] = dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x + 1000;
	Set2.Pos[0] = dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x - 1000;
}

void CLight::LightSetting()
{
	AmbientGlobal[0] = 0.4f;
	AmbientGlobal[1] = 0.4f;
	AmbientGlobal[2] = 0.4f;
	AmbientGlobal[3] = 1.0f;

	Set1.Ambient[0] = 0.1f;
	Set1.Ambient[1] = 0.1f;
	Set1.Ambient[2] = 0.1f;
	Set1.Ambient[3] = 1.0f;

	Set1.Diffuse[0] = 0.6f;
	Set1.Diffuse[1] = 0.6f;
	Set1.Diffuse[2] = 0.6f;
	Set1.Diffuse[3] = 1.0f;

	Set1.Specular[0] = 1.0f;
	Set1.Specular[1] = 1.0f;
	Set1.Specular[2] = 1.0f;
	Set1.Specular[3] = 1.0f;

	Set1.Pos[0] = 0.0f;
	Set1.Pos[1] = 300.0f;
	Set1.Pos[2] = 3000.0f;
	Set1.Pos[3] = 1.0f;

	Set2.Ambient[0] = 0.1f;
	Set2.Ambient[1] = 0.1f;
	Set2.Ambient[2] = 0.1f;
	Set2.Ambient[3] = 1.0f;

	Set2.Diffuse[0] = 0.6f;
	Set2.Diffuse[1] = 0.6f;
	Set2.Diffuse[2] = 0.6f;
	Set2.Diffuse[3] = 1.0f;

	Set2.Specular[0] = 1.0f;
	Set2.Specular[1] = 1.0f;
	Set2.Specular[2] = 1.0f;
	Set2.Specular[3] = 1.0f;

	Set2.Pos[0] = 0.0f;
	Set2.Pos[1] = 0.0f;
	Set2.Pos[2] = 0.0f;
	Set2.Pos[3] = 1.0f;

	Specref[0] = 0.8f;
	Specref[1] = 0.8f;
	Specref[2] = 0.8f;
	Specref[3] = 1.0f;

	glEnable(GL_LIGHTING);
	// 전역조명
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientGlobal);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	//조명1
	{
		glLightfv(GL_LIGHT0, GL_AMBIENT, Set1.Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Set1.Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Set1.Specular);
		glLightfv(GL_LIGHT0, GL_POSITION, Set1.Pos);
		glEnable(GL_LIGHT0);
	}
	//조명2
	{
		glLightfv(GL_LIGHT1, GL_AMBIENT, Set2.Ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Set2.Diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Set2.Specular);
		glLightfv(GL_LIGHT1, GL_POSITION, Set2.Pos);
		glEnable(GL_LIGHT1);
	}

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, Specref);
	glMateriali(GL_FRONT, GL_SHININESS, 60);
};

