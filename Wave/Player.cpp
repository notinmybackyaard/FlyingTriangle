#include "Player.h"
#include "SceneMgr.h"

CPlayer::CPlayer()
{
	Initialize();
}

CPlayer::~CPlayer()
{
}

Vec2& CPlayer::GetBox()
{
	Temp.x = (m_vecObj[OBJ_PLAYER][0])->Pos.x + Size * 3.5 * cos(DegToRad(LookDeg));
	Temp.y = (m_vecObj[OBJ_PLAYER][0])->Pos.y;
	return Temp;
}

double CPlayer::DegToRad(double& degree) {
	return degree * M_PI / 180;
};

void CPlayer::Initialize()
{
	IsColl = false;
	IsStart = false;
	Timer = 0;
	LookDeg = 0;
	Size = 30;
	Pos = { 0 };
	Color = { 1.0, 0.5, 0.5, 1.0 };
	Speed = 0;
	Timer = 0;
	LookSpeed = 0;

	IsLookUp = false;

}

void CPlayer::Render()
{

	glPushMatrix();
	{
		glTranslatef((m_vecObj[OBJ_PLAYER][0])->Pos.x, (m_vecObj[OBJ_PLAYER][0])->Pos.y, 0);
		glRotatef(dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->LookDeg, 0, 0, 1);

		// Player
		glLineWidth(4);
		glColor4f(0.6, 0.5, 0.7, 1.0);

		glBegin(GL_TRIANGLES); // 앞면
		glNormal3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, -Size, Size);
		glVertex3d(Size*3.5, 0.0, 0.0);
		glVertex3d(0.0, Size, Size);
		glEnd();
		glBegin(GL_TRIANGLES); // 윗면
		glNormal3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, Size, Size);
		glVertex3d(Size*3.5, 0.0, 0.0);
		glVertex3d(0.0, Size, -Size);
		glEnd();
		glBegin(GL_TRIANGLES); // 뒷면
		glNormal3d(0.0, 0.0, -1.0);
		glVertex3d(0.0, Size, -Size);
		glVertex3d(Size*3.5, 0.0, 0.0);
		glVertex3d(0.0, -Size, -Size);
		glEnd();
		glBegin(GL_TRIANGLES); // 아랫면
		glNormal3d(0.0, -1.0, 0.0);
		glVertex3d(0.0, -Size, -Size);
		glVertex3d(Size*3.5, 0.0, 0.0);
		glVertex3d(0.0, -Size, Size);
		glEnd();
		glBegin(GL_QUADS); // 꼬리면
		glNormal3d(-1.0, 0.0, 0.0);
		glVertex3d(0.0, -Size, Size);
		glVertex3d(0.0, Size, Size);
		glVertex3d(0.0, Size, -Size);
		glVertex3d(0.0, -Size, -Size);
		glEnd();

		// Bounding Box
		//glLineWidth(1);
		//glColor3f(1, 0, 0);
		//glTranslatef(Size*3.5, 0, 0);
		//glutWireCube(15);
	}glPopMatrix();

	if (IsColl)
		CollEffect(IsColl);
}

void CPlayer::Update()
{
	Ef++;
	if (IsColl == false)      // 충돌 시엔 안 움직이게
	{
		Ef = 0;
		if (!IsLookUp) // 플레이어가 위로 올라가고 있지않으면 가속도에 따라 룩벡터가 떨어짐
		{
			LookSpeed += LOOKFALL_ACC;
			if (LookSpeed >= MAX_LOOKSPEED)
				LookSpeed = MAX_LOOKSPEED;
			LookDeg -= LookSpeed;
		}
		else // 플레이어가 위로 올라가고 있으면 룩벡터도 올라감
		{
			LookDeg += 2.0;
			LookSpeed = 10.0;
		}

		if (LookDeg <= -60.0)
			LookDeg = -60.0;
		if (LookDeg >= 60.0)
			LookDeg = 60.0;

		if (IsStart)
		{
			Timer++;
			if (Timer > 300)
			{
				if (Speed < MAX_SPEED)
					Speed += ACC;
				else
					Speed = MAX_SPEED;

				Pos.y += Speed * sin(DegToRad(LookDeg));
			}
			else
			{
				Speed += 0.187;
				LookDeg = -10;
				Pos.y = 0;
			}
		}
		Pos.x += Speed;
	}
}

bool CPlayer::CollEffect(bool b)
{
	if (b)
	{
		glPushMatrix();
		glTranslatef((m_vecObj[OBJ_PLAYER][0])->Pos.x, (m_vecObj[OBJ_PLAYER][0])->Pos.y, 300);
		if (Ef < 50)
		{
			glColor3f(1, 1, 1);
			for (int i = 0; i < 20; ++i)
			{
				glPushMatrix();
				glRotatef(i * 36, 1, 0, 0);
				glTranslatef(Ef * 3, Ef * 3, Ef * 3);
				glutWireCube(i + 30);
				glPopMatrix();

				glPushMatrix();
				glRotatef(i * 36, 0, 1, 0);
				glTranslatef(Ef * 3, Ef * 3, Ef * 3);
				glutWireCube(i + 25);
				glPopMatrix();
			}
			return true;
		}
		else
		{			
			Sleep(1000);
			SceneMgr::GetInstance()->SetScene(SCENE_OVER);
			return false;
		}
		glPopMatrix();
	}
	return true;
}