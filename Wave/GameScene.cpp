#include "GameScene.h"
#include "Star.h"
#include "Player.h"

void LoadMapdata();

double DegToRad(double degree) {
	return degree * PIE / 180;
};

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	PlaySound(0, 0, 0);
}

void CGameScene::Initialize()
{
	PlaySound(0, 0, 0);
	PlaySound("GameBGM.wav", NULL, SND_ASYNC | SND_NOSTOP);

	if (!m_vecObj[OBJ_PLAYER].capacity())
	{
		CObject* pObj = new CPlayer;
		m_vecObj[OBJ_PLAYER].push_back(pObj);
		pObj = new CStar;
		m_vecObj[OBJ_STAR].push_back(pObj);
		LoadMapdata();
	}
	dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Initialize();
	
	for (auto iter = TData.begin(); iter < TData.end(); iter++)
		iter->IsPassed = NONPASS;

	start = std::chrono::system_clock::now();
	Light.LightSetting();
	Score = 0.0f;
	Timer = 0;
	TimerMove = 0;
	TimerGo = 0;
	TopComplex.x = 0;
	Combo = 0;
}

void CGameScene::DrawTop()
{
	auto Iter = MapData[TOP].begin();
	
	Nowx = dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x;
	glPushMatrix();
	while ((Iter + 1) != MapData[TOP].end())
	{
		// 범위의 이유 (밑의 줄) = x축이 오프닝동안 9586 증가하기 때문
		if ((Iter->x < Nowx + 5000) &&
			(Iter->x > Nowx - 5000))
		{
			if (Iter->x <= Nowx && (Iter + 1)->x >= Nowx)
			{
				// 기울기 ( y=ax+b중 ) a
				TopComplex.x = ((Iter + 1)->y - Iter->y) / ((Iter + 1)->x - Iter->x);
				TopComplex.y = Iter->y - TopComplex.x * Iter->x;
			}
			glColor4f(1.0, 0.5, 0.3, 1.0);
			glBegin(GL_QUADS); // 앞면
			glNormal3d(0.0, 0.0, 1.0);
			glVertex3d(Iter->x, 2000, 200);
			glVertex3d(Iter->x, Iter->y, 200);
			glVertex3d((Iter + 1)->x, (Iter + 1)->y, 200);
			glVertex3d((Iter + 1)->x, 2000, 200);
			glEnd();

			//glColor3f(0.9, 0.7, 0.5);
			glBegin(GL_QUADS); // 왼쪽면
			glNormal3d(-1.0, 0, 0);
			glVertex3d(Iter->x, 2000, -200);
			glVertex3d(Iter->x, Iter->y, -200);
			glVertex3d((Iter)->x, (Iter)->y, +200);
			glVertex3d((Iter)->x, 2000, +200);

			glColor4f(0.8, 0.3, 0.3, 1.0);
			glBegin(GL_QUADS); // 밑면
			glNormal3d(0, -1.0, 0);
			glVertex3d(Iter->x, Iter->y, 200);
			glVertex3d(Iter->x, Iter->y, -200);
			glVertex3d((Iter + 1)->x, (Iter + 1)->y, -200);
			glVertex3d((Iter + 1)->x, (Iter + 1)->y, 200);
			glEnd();
		}
		Iter++;
	}
	glPopMatrix();
}

void CGameScene::DrawBottom()
{
	glLineWidth(4);
	Nowx = dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x;
	auto Iter = MapData[BOTTOM].begin();

	glPushMatrix();
	
	while ((Iter + 1) != MapData[BOTTOM].end())
	{
		if ((Iter->x < Nowx + 5000) &&
			(Iter->x > Nowx - 5000))
		{
			if (Iter->x <= Nowx && (Iter + 1)->x >= Nowx)
			{
				// 기울기 ( y=ax+b중 ) a
				BotComplex.x = ((Iter + 1)->y - Iter->y) / ((Iter + 1)->x - Iter->x);
				BotComplex.y = Iter->y - BotComplex.x * Iter->x;
			}
			glColor4f(1.0, 0.5, 0.3, 1.0);
			glBegin(GL_QUADS); // 앞면
			glNormal3d(0.0, 0.0, 1.0);
			glVertex3d(Iter->x, Iter->y, 200);
			glVertex3d(Iter->x, -2000, 200);
			glVertex3d((Iter + 1)->x, -2000, 200);
			glVertex3d((Iter + 1)->x, (Iter + 1)->y, 200);
			glEnd();

			//glColor3f(0.7, 0.4, 0.9);
			glBegin(GL_QUADS); // 옆면
			glNormal3d(-1.0, 0, 0);
			glVertex3d(Iter->x, Iter->y, 200);
			glVertex3d((Iter)->x, (Iter)->y, -200);
			glVertex3d(Iter->x, -2000, -200);
			glVertex3d((Iter)->x, -2000, 200);
			glEnd();

			glColor4f(0.8, 0.3, 0.3, 1.0);
			glBegin(GL_QUADS); // 윗면
			glNormal3d(0.0, 1.0, 0.0);
			glVertex3d(Iter->x, Iter->y, 200);
			glVertex3d((Iter + 1)->x, (Iter + 1)->y, 200);
			glVertex3d((Iter + 1)->x, (Iter + 1)->y, -200);
			glVertex3d(Iter->x, Iter->y, -200);
			glEnd();
		}
		Iter++;
	}
	glPopMatrix();
}
void CGameScene::DrawTorus()
{
	auto Iter = TData.begin();

	while ((Iter + 1) != TData.end())
	{
		// 범위의 이유 (밑의 줄) = x축이 오프닝동안 9586 증가하기 때문
		if ((Iter->x < dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x + 5000) &&
			(Iter->x > dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x - 5000))
		{
			glPushMatrix();
			glTranslatef(Iter->x, Iter->y, 0);
			glScaled(2.0, 1.0, 1.0);
			glRotatef(90, 0, 1, 0);
			if ((*Iter).IsPassed == PASS)
			{
				glColor4f(0.7, 0.4, 0.5, 1.0);
				glScaled(0.9, 0.9, 0.9);
			}
			else if ((*Iter).IsPassed == COREPASS)
			{
				if (Combo >= 2)
				{
					glColor3f(1.0, 0.0, 0.0);
					String = "Combo!";			
					glRasterPos3f((*Iter).x / 2.0 + 50, (*Iter).y + 50, 0.0f);
					len = String.length();
					for (int i = 0; i < len; i++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
					glColor3f(1.0, 0.0, 0.0);
				}
				else
				{
					glColor3f(1.0, 1.0, 0.5);
					String = "Perfect!";
					glRasterPos3f((*Iter).x / 2.0 + 50, (*Iter).y + 50, 0.0f);
					len = String.length();
					for (int i = 0; i < len; i++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
					glColor3f(1.0, 1.0, 1.0);
				}
				glScaled(1.1, 1.1, 1.1);
			}
			else
				glColor4f(0.5, 0.7, 0.9, 1.0);
			glutSolidTorus(15, 120, 20, 20);
			glPopMatrix();
		}
		Iter++;
	}
}
void CGameScene::SkipAnimation()
{
	if (!IsOpening)
		return;

	dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x = 100.05;
	IsOpening = false;
	dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->LookDeg = 0.0;
	dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsLookUp = false;
	dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsStart = true;
}

void CGameScene::TorusColl()
{
	for (auto i = TData.begin(); i != TData.end(); ++i)
	{
		if ((float((*i).x) < float(dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox().x) + 10.0) &&
			(float((*i).x) > float(dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox().x) - 10.0))
		{
			//if ((*i).IsPassed == NONPASS) // 오류있음
			//{
			if (sqrt(pow((*i).x - (dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox().x), 2) + 
				pow((*i).y - (dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox().y), 2)) <= 40.0)
			{
				Combo++;
				if(Combo >= 3)
					Score += 4;
				else
					Score += 2;
				(*i).IsPassed = COREPASS;
			}
			else if (sqrt(pow((*i).x - (dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox().x), 2) + 
				pow((*i).y - (dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox().y), 2)) <= 130.0)
			{
				Score += 1;
				(*i).IsPassed = PASS;
				Combo = 0;
			}
			else
				Combo = 0;
			//}8443.05
		}
	}
}

void LoadMapdata()
{
	vector<Vec2> vempty[VERTEX_END];
	swap(MapData, vempty);

	ifstream In;
	string FileName;
	Vec2 Pos;
	Torus T;

	//cout << "불러올 파일 이름을 입력해주세요 : ";
	//cin >> FileName;
	FileName = "Map";
	In.open(FileName + ".TopData", ios::in);
	if (In.is_open())
	{
		while (In >> Pos.x >> Pos.y)
			MapData[TOP].push_back(Pos);
	}
	else
	{
		cout << "파일이 존재하지 않습니다" << endl;
		system("pause");
		return;
	}
	In.close();

	In.open(FileName + ".BottomData", ios::in);
	if (In.is_open())
	{
		while (In >> Pos.x >> Pos.y)
			MapData[BOTTOM].push_back(Pos);
	}
	else
	{
		cout << "파일이 존재하지 않습니다" << endl;
		system("pause");
		return;
	}
	In.close();

	In.open(FileName + ".TorusData", ios::in);
	if (In.is_open())
	{
		while (In >> T.x >> T.y)
		{
			T.IsPassed = NONPASS;
			TData.push_back(T);
		}
		//for(auto i = TData.begin(); i != TData.end(); ++i)
			
	}
	else
	{
		cout << "파일이 존재하지 않습니다" << endl;
		system("pause");
		return;
	}
	In.close();
	for (int j = 0; j < 3; ++j)
		for (auto i = MapData[j].begin(); i < MapData[j].end(); ++i)
			i->x += 9586;

}

bool CGameScene::Collision()
{
	if (TopComplex.x == 0)
		return true;
	Box = dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox();
	if ((Box.x * TopComplex.x + TopComplex.y) <= Box.y)
	{
		dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsColl = true;
		return false;
	}
	if ((Box.x * BotComplex.x + BotComplex.y) >= Box.y)
	{
		dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsColl = true;
		return false;
	}
	return true;
}
void CGameScene::Update()
{
	TorusColl();
	Collision();
	Box = dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->GetBox();
	if (dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsColl)
	{
		for (size_t j = 0; j < m_vecObj[OBJ_PLAYER].size(); ++j)
		{
			Light.Update();
			auto iter = m_vecObj[OBJ_PLAYER].begin();
			if (m_vecObj[OBJ_PLAYER][j] != NULL)
				m_vecObj[OBJ_PLAYER][j]->Update();
		}
	}
	else
	{
		if (IsOpening && CameraState == TURN)
		{
			if ((Timer % 100) < 44)
				dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsLookUp = true;
			else
				dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsLookUp = false;
		}
		if (CameraState == TURN || !IsOpening)
			for (size_t j = 0; j < m_vecObj[OBJ_PLAYER].size(); ++j)
			{
				Light.Update();
				auto iter = m_vecObj[OBJ_PLAYER].begin();
				if (m_vecObj[OBJ_PLAYER][j] != NULL)
					m_vecObj[OBJ_PLAYER][j]->Update();
			}
		for (size_t j = 0; j < m_vecObj[OBJ_STAR].size(); ++j)
		{
			Light.Update();
			auto iter = m_vecObj[OBJ_STAR].begin();
			if (m_vecObj[OBJ_STAR][j] != NULL)
				if (CameraState == TURN || CameraState == MOVE)
					dynamic_cast<CStar*>(m_vecObj[OBJ_STAR][j])->Update(false);
				else
					dynamic_cast<CStar*>(m_vecObj[OBJ_STAR][j])->Update(true);
		}
	}
}

void CGameScene::Render()
{
	if (!IsOpening)
	{
		DrawTop();
		DrawBottom();
		DrawTorus();
	}
	
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			auto iter = m_vecObj[i].begin();
			if (m_vecObj[i][j] != NULL)
				m_vecObj[i][j]->Render();
		}
	}
	switch(CameraState)
	{
	case GO:
		Timer++;
		TimerGo++;
		if (TimerGo > 20)
		{
			CameraState = TURN;
			TimerGo = 0;
		}
		break;
	case TURN:
		Deg++;
		Timer++;
		if (Deg == 180)
			CameraState = GO;
		if (Deg == 360)
			CameraState = GO;
		if (Deg == 500)
			CameraState = MOVE;
		break;
	case MOVE:
		Timer++;
		if (!Movex)
		{
			TimerMove = 0;
			Movex = OpeningCameraR * sin(DegToRad(Deg)) + dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x;
			Movey = 1500;
			Movez = OpeningCameraR * cos(DegToRad(Deg));
			
			Distance.x = (float)(Camera.x - Movex) / 150;
			Distance.y = (float)(Camera.y - Movey) / 150;
			Distance.z = (float)(Camera.z - Movez) / 150;
		}

		TimerMove++;
		Movex += Distance.x;
		Movey += Distance.y;
		Movez += Distance.z;
		
		if (TimerMove == 150)
		{
			dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsLookUp = false;
			IsOpening = false;
		}
		break;
	}
	
	if (!IsOpening)
	{
		dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsStart = true;
		RenderUI();
	}
	else
		RenderSkipUI();
}

void CGameScene::Release()
{
}

void CGameScene::Mouse(int Mouse, int Button, int x, int y)
{
	if (!IsOpening)
	{
		if (Mouse == GLUT_LEFT_BUTTON && Button == GLUT_DOWN)
			dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsLookUp = true;
		else
			dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->IsLookUp = false;
	}
}

void CGameScene::KeyBoard(unsigned char key, int a, int b)
{
	if (key == 's' || key == 'S')
		SkipAnimation();
}

void CGameScene::SpecialKeyBoard(int key, int a, int b)
{
}

void CGameScene::SetView(int w, int h)
{
	gluPerspective(VIEWANGLE, w / h, 1, 10000000);

	Camera = { (float)-500.0 + (float)dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x , (float)100.0, (float)2000.0 };
	
	if (IsOpening)
		if (Movex && CameraState == MOVE)
			gluLookAt(Movex, Movey, Movez,
				200.0 + dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x, 80.0, 0.0,
				0.0, 1.0, 0.0);
		else
			gluLookAt(OpeningCameraR * sin(DegToRad(Deg)) + dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x,
				1500, OpeningCameraR * cos(DegToRad(Deg)),
				200.0 + dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x, 80.0, 0.0,
				0.0, 1.0, 0.0);
	else
		gluLookAt(Camera.x, Camera.y, Camera.z,
			200.0 + dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x, 0.0, 0.0,
			0.0, 1.0, 0.0);
}

void CGameScene::RenderUI()
{

	String = "Start!";
	glRasterPos3f(10500.0f, 200.f, 0.0f);
	len = String.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
	String = to_string(Score);
	glRasterPos3f(dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x + 100.0, dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.y + 100.0, 200.0f);
	 len = String.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
}

void CGameScene::RenderSkipUI()
{
	glColor4d(0.8, 0.8, 0.8, 1.0 /*- float(Timer/100.0)*/);
	String = "Press 'S' to Skip";
	glRasterPos3f(dynamic_cast<CPlayer*>(m_vecObj[OBJ_PLAYER][0])->Pos.x, -3000.0, 0.0f);
	len = String.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, String[i]);
}
