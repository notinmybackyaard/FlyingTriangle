#pragma once
#include "Header.h"

class CLight
{
public:
	CLight();
	virtual ~CLight();

public:
	void Update();
	void LightSetting();

public:
	LightPara Set1;
	LightPara Set2;
	float Specref[4];
	float AmbientGlobal[4];
};