#pragma once
#include "Scene.h"

class CLoginScene
	: public CScene
{
public:
	CLoginScene();
	virtual ~CLoginScene();

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
	void TextureSetup();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info); // BMP파일 로드 함수
public:
	GLubyte * pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
	GLuint textures[1];
	bool IsLoginUIOn;
	int Index;
	bool IsPress;
};