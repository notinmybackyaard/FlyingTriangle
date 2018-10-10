#pragma once
#include "Header.h"

class CObject;

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Mouse(int Mouse, int Button, int x, int y) = 0;
	virtual void KeyBoard(unsigned char key, int a, int b) = 0;
	virtual void SpecialKeyBoard(int key, int a, int b) = 0;
	virtual void SetView(int w, int h) = 0;

public:
	int len;
	string String;

public:
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
};
