#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#pragma comment(lib,"winmm.lib")

#include <tchar.h>
#include <random>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <GL/glut.h> 
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#include <string> // 비트맵 파일 관련 자료 저장
#include "Defines.h"
#include "Macro.h"

using namespace std;

class CObject;
extern vector<CObject*> m_vecObj[OBJ_END];
extern vector<Vec2> MapData[VERTEX_END];
extern vector<Torus> TData;
extern default_random_engine dre;
extern string PlayerName;
extern int Score;

struct RankInfo
{
	int RScore;
	string Name;

	string GetName() {
		return Name;
	}
	void SetName(string& a) {
		Name = a;
	}
};