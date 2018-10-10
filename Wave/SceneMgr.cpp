#include "Header.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "LogInScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

INIT_SINGLETON(SceneMgr)

SceneMgr::SceneMgr()
	: m_Scene(nullptr)
{
	Initialize();
}

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Initialize()
{
	SetScene(SCENE_LOGIN);
}

void SceneMgr::Update()
{
	if (m_Scene)
		m_Scene->Update();
}

void SceneMgr::Render()
{
	if (m_Scene)
		m_Scene->Render();
}

void SceneMgr::Release()
{
	if (m_Scene)
	{
		delete(m_Scene);
		m_Scene = NULL;
	}
}

void SceneMgr::Mouse(int Mouse, int Button, int x, int y)
{
	if (m_Scene)
		m_Scene->Mouse(Mouse, Button, x, y);
}

void SceneMgr::KeyBoard(unsigned char key, int a, int b)
{
	if (m_Scene)
		m_Scene->KeyBoard(key, a, b);
}

void SceneMgr::SpecialKeyBoard(int key, int a, int b)
{
	if (m_Scene)
		m_Scene->SpecialKeyBoard(key, a, b);
}

void SceneMgr::SetView(int w, int h)
{
	if (m_Scene)
		m_Scene->SetView(w, h);
}

void SceneMgr::SetScene(SceneType _SceneType)
{
	if (m_Scene)
	{
		CScene*			Temp;
		swap(m_Scene, Temp);
	}
	//TData.clear();
	//m_vecObj[0].clear();

	m_CurSceneType = _SceneType;

	switch (_SceneType)
	{
	case SCENE_LOGIN:
		m_Scene = new CLoginScene();
		break;

	case SCENE_STAGE:
		m_Scene = new CGameScene();
		break;

	case SCENE_OVER:
		m_Scene = new CGameOverScene();
		break;
	}
	m_Scene->Initialize();
}

void SceneMgr::ChangeScene(SceneType _SceneType)
{
	if (m_CurSceneType == _SceneType)
		return;
	SetScene(_SceneType);
}