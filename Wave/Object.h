#pragma once
#include "Header.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	virtual void Initialize() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

public:
	Vec3 Pos;
	float Size;
	Vec4 Color;
};