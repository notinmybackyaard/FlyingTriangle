#pragma once
#include "Object.h"

class CStar : public CObject
{
public:
	CStar();
	virtual ~CStar();

public:
	virtual void Initialize();
	virtual void Render();
	virtual void Update() {};
	void Update(bool Type);

public:
	Vec3 Pos[STAR_NUM];
};