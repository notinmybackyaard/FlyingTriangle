#include "GameOverScene.h"
#include "SceneMgr.h"

CGameOverScene::CGameOverScene()
{
}

CGameOverScene::~CGameOverScene()
{
}

void CGameOverScene::Initialize()
{
	LoadRanking();
	SaveRanking();
	IsDrawRanking = false;
	start = std::chrono::system_clock::now();
}

void CGameOverScene::Update()
{
	if (elapsed_seconds.count() >= 10.0)
		return;

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
}

void CGameOverScene::Render()
{
	if (elapsed_seconds.count() >= 1)
	{
		if (!IsDrawRanking)
		{
			glPushMatrix();
			glColor4d(1.0, 1.0, 1.0, (elapsed_seconds.count() - 1) / 2);
			String = "Game Over";
			glRasterPos3f(-50.f, 0.f, 0.0f);
			len = String.length();
			for (int i = 0; i < len; i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
			glPopMatrix();
		}
	}
	if (elapsed_seconds.count() >= 2)
	{
		IsDrawRanking = true;
		glPushMatrix();

		int Cnt = 0;
		glColor4d(1.0, 1.0, 1.0, 1.0);
		String = "RankBoard";
		glRasterPos3f(-65.f, 370.0f, 0.0f);
		len = String.length();
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);

		glColor4d(1.0, 1.0, 1.0, 1.0);
		String = "Press 'R' to Restart";
		glRasterPos3f(-100.f, -370.0f, 0.0f);
		len = String.length();
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);


		glColor4d(1.0, 1.0, 1.0, 1.0);
		String = "Press 'Q' to Exit";
		glRasterPos3f(-100.f, -330.0f, 0.0f);
		len = String.length();
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);

		for (auto i = VecRankInfo.begin(); i != VecRankInfo.end(); ++i)
		{
			if(i->GetName() == PlayerName && i->RScore == Score)
				glColor4d(1.0, 1.0, 0.5, 1.0);
			else
				glColor4d(1.0, 1.0, 1.0, 1.0);
			String = i->GetName();
			glRasterPos3f(-100.f, 300.0f - 50.0*Cnt, 0.0f);
			len = String.length();
			for (int i = 0; i < len; i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
			String = to_string(i->RScore);
			glRasterPos3f(30.f, 300.0f - 50.0*Cnt, 0.0f);
			len = String.length();
			for (int i = 0; i < len; i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
			Cnt++;
		}

		glPopMatrix();
	}
}

void CGameOverScene::Release()
{
}

void CGameOverScene::Mouse(int Mouse, int Button, int x, int y)
{
}

void CGameOverScene::KeyBoard(unsigned char key, int a, int b)
{
	if(key == 'q' || key == 'Q') // 씬이 바뀔때  extern 전역변수 정보 그대로 남아있음 초기화 해줘야함
		SceneMgr::GetInstance()->SetScene(SCENE_LOGIN);
	if (key == 'r' || key == 'R')
		SceneMgr::GetInstance()->SetScene(SCENE_STAGE);
}

void CGameOverScene::SpecialKeyBoard(int key, int a, int b)
{
}

void CGameOverScene::SetView(int w, int h)
{
	gluPerspective(VIEWANGLE, w / h, 1, 2000);

	gluLookAt(0, 0, 750,
		0, 0, 0,
		0, 1, 0);
}

void CGameOverScene::SaveRanking()
{
	ofstream Out;
	RankInfo tmpR;
	string FileName = "Ranking";
	tmpR.SetName(PlayerName);
	tmpR.RScore = Score;
	VecRankInfo.push_back(tmpR);

	sort(VecRankInfo.begin(), VecRankInfo.end(), [](const RankInfo& a, const RankInfo& b) {
		return a.RScore > b.RScore;
	});

	Out.open(FileName + ".txt", ios::out, ios::trunc);
	for (auto i = VecRankInfo.begin(); i != VecRankInfo.end(); ++i)
		Out << i->GetName() << "	" << i->RScore << endl;
	Out.close();

}


void CGameOverScene::LoadRanking()
{
	RankInfo tmpR;
	string tmp;
	ifstream In;

	In.open("Ranking.txt", ios::in);
	if (In.is_open())
	{
		while (In >> tmp >> tmpR.RScore)
		{
			tmpR.SetName(tmp);
			VecRankInfo.push_back(tmpR);
		}
	}
	else
	{
		cout << "파일이 존재하지 않습니다" << endl;
		system("pause");
		return;
	}
	In.close();

}
