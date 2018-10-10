#include "Star.h"
#include "Player.h"

CStar::CStar()
{
	Initialize();
}

CStar::~CStar()
{
}

void CStar::Initialize()
{
	uniform_int_distribution<> StarPos_ui(-100000, 100000);
	uniform_int_distribution<> StarPosZ_ui(-100000, -5000);
	uniform_int_distribution<> StarPosZ2_ui(5000, 100000);

	for (int i = 0; i < STAR_NUM/2; ++i)
	{
		Pos[i].x = StarPos_ui(dre);
		Pos[i].y = StarPos_ui(dre);
		Pos[i].z = StarPosZ_ui(dre);
	}
	for (int i = STAR_NUM/2; i < STAR_NUM; ++i)
	{
		Pos[i].x = StarPos_ui(dre);
		Pos[i].y = StarPos_ui(dre);
		Pos[i].z = StarPosZ2_ui(dre);
	}
}

void CStar::Render()
{
	for (int i = 0; i < STAR_NUM; ++i)
	{
		glPushMatrix();
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glTranslatef(Pos[i].x, Pos[i].y, Pos[i].z);
		glutSolidCube(80);
		glPopMatrix();
	}
}

void CStar::Update(bool Type)
{
	if(!Type)
		for (int i = 0; i < STAR_NUM; ++i)
		{
			if (Pos[i].x < dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x - 100000)
				Pos[i].x += 200000;
		}
	else
	{
		for (int i = 0; i < STAR_NUM; ++i)
		{
			if (Pos[i].x < dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x - 100000)
				Pos[i].x += 200000;
			Pos[i].x -= 20;
		}
	}
}
