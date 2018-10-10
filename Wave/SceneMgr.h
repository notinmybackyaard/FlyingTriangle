#pragma once

class CScene;
class CObject;

class SceneMgr
{
	CREATE_SINGLETON(SceneMgr)
private:
	SceneMgr();
public:
	~SceneMgr();

private:
	CScene*			m_Scene;		// ¾À °ü¸®¸¦ À§ÇÑ ¾À
	SceneType		m_CurSceneType;

public:
	void Initialize();
	void Update();
	void Render();
	void Release();
	void Mouse(int Mouse, int Button, int x, int y);
	void KeyBoard(unsigned char key, int a, int b);
	void SpecialKeyBoard(int key, int a, int b);
	void SetView(int w, int h);

public:
	void SetScene(SceneType _SceneType);
	void ChangeScene(SceneType _SceneType);

public:
	SceneType GetCurSceneType()
	{
		return m_CurSceneType;
	}
};