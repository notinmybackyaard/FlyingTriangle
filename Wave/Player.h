#pragma once
#include "Object.h"

class CPlayer : public CObject
{
	int Timer = 0;
	int Ef = 0;
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize();
	virtual void Render();
	virtual void Update();

public:
	Vec2& GetBox();
	double CPlayer::DegToRad(double&);
	bool CollEffect(bool);

public:
	// 플레이어 이동 가속도(고정값)
	const double ACC = 0.4;
	// 플레이어 최대 이동 속도
	const double MAX_SPEED = 19.0;
	// 플레이어의 방향벡터 추락하는 가속도
	const double LOOKFALL_ACC = 0.7;
	// 플레이어의 방향벡터 추락하는 최대속도
	const double MAX_LOOKSPEED = 2.0;

public:
	// 플레이어의 방향벡터 회전각
	double LookDeg;
	// 플레이어의 방향벡터 추락하는 속도
	double LookSpeed;
	// 플레이어의 방향벡터가 위로 올라가고 있는가
	bool IsLookUp;
	bool IsColl;
	bool IsStart;
	double Speed;
	Vec2 Temp;
};
