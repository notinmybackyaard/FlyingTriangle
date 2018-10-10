#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#include <tchar.h>
#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <GL/glut.h> 
#include <vector>
#include <string>
#include <fstream>
#include <windows.h> // 비트맵 파일 관련 자료 저장
using namespace std;

const int MAPSIZE_W = 800;
const int MAPSIZE_H = 800;
const int MAPSIZE_D = 600;
const int VIEWANGLE = 60;
const int DELAY = 10;

const int MAXY = 900;
const int MINY = -1000;

enum VERTEX { TOP, BOTTOM, TORUS, END};
enum DRAW { DRAWTOP, DRAWBOTTOM, DRAWTORUS, DRAWEND};

struct Vec2 { 
	float x;
	float y;
};

// 콜백 관련 함수
void DrawScene();
void Reshape(int, int);
void KeyBoard(unsigned char, int, int);
void SpecialKeyboard(int key, int	 x, int y);
void Timer(int);
void Mouse(int, int, int, int);

// 사용자 정의 함수
void RenderMode();
void Initialize();
void Reset();
void PrintText();
void Save();
void Load();

vector<Vec2> Vertex[END];
Vec2 Pos;
int DrawMode;
double TransX = 0.0;
double TransY = 0.0;
double MoveX;

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	Initialize();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // 디스플레이 모드 설정 
	glutInitWindowPosition(250, 50);   // 윈도우의 위치지정 
	glutInitWindowSize(MAPSIZE_W, MAPSIZE_H);    // 윈도우의 크기 지정
	glutCreateWindow("MapEditer");   // 윈도우 생성 (윈도우 이름) 
	glutTimerFunc(DELAY, Timer, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene);    // 출력 함수의 지정   
	glutReshapeFunc(Reshape);   // 다시 그리기 함수의 지정 
	glutMainLoop();
}

void Initialize()
{
	DrawMode = DRAWTOP;

	Pos.x = -1000;
	Pos.y = MAXY;
	Vertex[TOP].push_back(Pos);
	Pos.x = 1000;
	Pos.y = MAXY;
	Vertex[TOP].push_back(Pos);
	Pos.x = -1000;
	Pos.y = MINY;
	Vertex[BOTTOM].push_back(Pos);
	Pos.x = 1000;
	Pos.y = MINY;
	Vertex[BOTTOM].push_back(Pos);

	MoveX = 500.0;
}

void Reset()
{
	Vertex[TOP].clear();
	Vertex[BOTTOM].clear();
	Vertex[TORUS].clear();
	Initialize();
}

// 윈도우 출력 함수 
void DrawScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 설정된 색으로 전체를 칠하기 

	RenderMode();      // 효과 떡칠

	PrintText();

	glPointSize(10.0);
	glPushMatrix();
	glColor4d(1.0, 0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (auto iter = Vertex[TOP].begin(); iter != Vertex[TOP].end(); ++iter)
			glVertex2f((*iter).x, (*iter).y);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (auto iter = Vertex[TOP].begin(); iter != Vertex[TOP].end(); ++iter)
			glVertex2f((*iter).x, (*iter).y);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4d(0.0, 0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (auto iter = Vertex[BOTTOM].begin(); iter != Vertex[BOTTOM].end(); ++iter)
		glVertex2f((*iter).x, (*iter).y);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (auto iter = Vertex[BOTTOM].begin(); iter != Vertex[BOTTOM].end(); ++iter)
		glVertex2f((*iter).x, (*iter).y);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4d(1.0, 0.0, 1.0, 1.0);
	for (auto iter = Vertex[TORUS].begin(); iter != Vertex[TORUS].end(); ++iter)
	{
		glPushMatrix();
		glTranslated((*iter).x, (*iter).y, 0.0);
		glRotated(30.0, 0.0, 1.0, 0.0);
		glutSolidTorus(20.0, 100.0, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();

	glutPostRedisplay();
	glutSwapBuffers();// 화면에 출력하기
}

void Mouse(int button, int state, int x, int y)
{

	TransX = (x - MAPSIZE_H / 2)*2.9 + MoveX;
	TransY = (-y + MAPSIZE_H / 2)*2.9;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Pos.x = TransX;
		Pos.y = TransY;
		if (DrawMode == DRAWTOP)
		{
			for (auto iter = Vertex[TOP].begin(); iter != Vertex[TOP].end(); ++iter)
			{
				if ((*iter).x >= Pos.x)
					return;
			}
			if (MAXY <= Pos.y)
				return;
			if (MINY + 150.0 >= Pos.y)
				return;
			Vertex[TOP].push_back(Pos);
		}
		if (DrawMode == DRAWBOTTOM)
		{
			for (auto iter = Vertex[BOTTOM].begin(); iter != Vertex[BOTTOM].end(); ++iter)
			{
				if ((*iter).x >= Pos.x)
					return;
			}
			if (MAXY - 150.0 <= Pos.y)
				return;
			if (MINY >= Pos.y)
				return;
			Vertex[BOTTOM].push_back(Pos);
		}
		if (DrawMode == DRAWTORUS)
		{
			for (auto iter = Vertex[TORUS].begin(); iter != Vertex[TORUS].end(); ++iter)
			{
				if ((*iter).x >= Pos.x)
					return;
			}
			if (MAXY - 200.0 <= Pos.y)
				return;
			if (MINY + 200.0 >= Pos.y)
				return;
			Vertex[TORUS].push_back(Pos);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (DrawMode == DRAWTOP)
			if(Vertex[TOP].size() > 2)
				Vertex[TOP].pop_back();
		if (DrawMode == DRAWBOTTOM)
			if (Vertex[BOTTOM].size() > 2)
			Vertex[BOTTOM].pop_back();
		if (DrawMode == DRAWTORUS)
			if (Vertex[TORUS].size() > 0)
			Vertex[TORUS].pop_back();
	}
	Reshape(MAPSIZE_W, MAPSIZE_H);
}

void Timer(int n)
{
	
	glutTimerFunc(DELAY, Timer, 1);
}

void RenderMode()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_CCW);
}

void KeyBoard(unsigned char key, int a, int b)
{
	if (key == 'r' || key == 'R')
		Reset();
	if (key == 'q' || key == 'Q')
		exit(1);
	if (key == 's' || key == 'S')
		Save();
	if (key == 'l' || key == 'L')
		Load();

	if(key == '1')
		DrawMode = DRAWTOP;
	else if (key == '2')
		DrawMode = DRAWBOTTOM;
	else if (key == '3')
		DrawMode = DRAWTORUS;
	Reshape(MAPSIZE_W, MAPSIZE_H);
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		if(MoveX > 200.0)
		MoveX -= 100.0;
	if (key == GLUT_KEY_RIGHT)
		MoveX += 100.0;
	Reshape(MAPSIZE_W, MAPSIZE_H);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(VIEWANGLE, w / h, 1, 10000000);
	gluLookAt(MoveX, 0.0, 2000.0,
		MoveX, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void PrintText()
{
	string string1;
	string string2;
	string string3;
	string string4;
	string string5;
	string1 = "1 : TopDrawMode     2 : BottomDrawMode     3 : TorusDrawMode";
	string2 = "LeftClick : Make Object     RightClick : Delete Previous Object";
	string3 = "R/r : Reset     S/s : Save & Exit     Q/q : Exit Without Save     L/l : Load MapData";
	string4 = "-> : Move Right";
	string5 = "<- : Move Left";

	glColor3d(0.7, 0.4, 0.1);
	glRasterPos3f(-1070.f + MoveX, 1100.f, 0.0f);
	int len = string1.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);

	glRasterPos3f(-1070.f + MoveX, 1030.f, 0.0f);
	len = string2.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);

	glRasterPos3f(-1070.f + MoveX, 960.f, 0.0f);
	len = string3.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string3[i]);

	glRasterPos3f(300.f + MoveX, -1100.f, 0.0f);
	len = string4.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string4[i]);

	glRasterPos3f(-500.f + MoveX, -1100.f, 0.0f);
	len = string5.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string5[i]);
}

void Save()
{
	ofstream Out;
	string FileName = "Map";
	Out.open(FileName + ".TopData", ios::out, ios::trunc); // 같은 파일명 있으면 덮어쓰기
	for (auto i = Vertex[TOP].begin(); i != Vertex[TOP].end(); ++i)
		Out << i->x << "	" << i->y << endl;
	Out.close();
	Out.open(FileName + ".BottomData", ios::out, ios::trunc); // 같은 파일명 있으면 덮어쓰기
	for (auto i = Vertex[BOTTOM].begin(); i != Vertex[BOTTOM].end(); ++i)
		Out << i->x << "	" << i->y << endl;
	Out.close();
	Out.open(FileName + ".TorusData", ios::out, ios::trunc); // 같은 파일명 있으면 덮어쓰기
	for (auto i = Vertex[TORUS].begin(); i != Vertex[TORUS].end(); ++i)
		Out << i->x << "	" << i->y << endl;
	Out.close();
	cout << "저장 완료" << endl;
	system("pause");
	exit(1);
}

void Load()
{
	vector<Vec2> vempty[END];
	swap(Vertex, vempty);

	ifstream In;
	string FileName = "Map";
	Vec2 Pos;

	In.open(FileName + ".TopData", ios::in);
	if (In.is_open())
	{
		while (In >> Pos.x >> Pos.y)
			Vertex[TOP].push_back(Pos);
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
			Vertex[BOTTOM].push_back(Pos);
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
		while (In >> Pos.x >> Pos.y)
			Vertex[TORUS].push_back(Pos);
	}
	else
	{
		cout << "파일이 존재하지 않습니다" << endl;
		system("pause");
		return;
	}
	In.close();

	cout << "불러오기 완료" << endl;

}