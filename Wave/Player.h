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
	// �÷��̾� �̵� ���ӵ�(������)
	const double ACC = 0.4;
	// �÷��̾� �ִ� �̵� �ӵ�
	const double MAX_SPEED = 19.0;
	// �÷��̾��� ���⺤�� �߶��ϴ� ���ӵ�
	const double LOOKFALL_ACC = 0.7;
	// �÷��̾��� ���⺤�� �߶��ϴ� �ִ�ӵ�
	const double MAX_LOOKSPEED = 2.0;

public:
	// �÷��̾��� ���⺤�� ȸ����
	double LookDeg;
	// �÷��̾��� ���⺤�� �߶��ϴ� �ӵ�
	double LookSpeed;
	// �÷��̾��� ���⺤�Ͱ� ���� �ö󰡰� �ִ°�
	bool IsLookUp;
	bool IsColl;
	bool IsStart;
	double Speed;
	Vec2 Temp;
};
