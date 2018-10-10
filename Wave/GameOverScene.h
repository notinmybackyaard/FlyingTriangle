#pragma once
#include "Scene.h"

class CGameOverScene
	: public CScene
{
public:
	CGameOverScene();
	virtual ~CGameOverScene();
public:
	void SaveRanking();
	void LoadRanking();
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
	vector<RankInfo> VecRankInfo;
	bool IsDrawRanking;
};
