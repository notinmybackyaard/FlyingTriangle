#pragma once
#include "Scene.h"
#include "Light.h"

class CGameScene
	: public CScene
{
	bool DegDir = false;
	bool IsOpening = true;
	float Deg = 0;
	float OpeningCameraR = 1000;
	int CameraState = 0;
	float Movex = 0, Movey = 0,Movez = 0;
	int Timer = 0, TimerMove = 0, TimerGo = 0;
	int MapSize = 1000;
	Vec3 Camera;
	Vec3 Distance;
	Vec2 Box;
	Vec2 TopComplex;
	Vec2 BotComplex;
	int Nowx;
	int Combo;
public:
	CGameScene();
	virtual ~CGameScene();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	virtual void Mouse(int Mouse, int Button, int x, int y);
	virtual void KeyBoard(unsigned char key, int a, int b);
	virtual void SpecialKeyBoard(int key, int a, int b);
	virtual void SetView(int w, int h);
public:
	bool Collision();
	void RenderUI();
	void RenderSkipUI();
	void DrawTop();
	void TorusColl();
	void DrawBottom();
	void DrawTorus();
	void SkipAnimation();
public:
	CLight Light;
};
