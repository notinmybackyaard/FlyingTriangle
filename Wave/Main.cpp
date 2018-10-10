#include "Header.h"
#include "SceneMgr.h"


// �ݹ� ���� �Լ�
void DrawScene();
void Reshape(int, int);
void KeyBoard(unsigned char, int, int);
void SpecialKeyBoard(int key, int a, int b);
void Timer(int);
void Mouse(int, int, int, int);

// ����� ���� �Լ�
void RenderMode();

vector<CObject*> m_vecObj[OBJ_END];
vector<Vec2> MapData[VERTEX_END];
vector<Torus> TData;
default_random_engine dre{ random_device{}() };
string PlayerName;
int Score = 0;

void main(int argc, char *argv[])
{  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // ���÷��� ��� ���� 
	glutInitWindowPosition(250, 50);   // �������� ��ġ���� 
	glutInitWindowSize(MAPSIZE_W, MAPSIZE_H);    // �������� ũ�� ����
	glutCreateWindow("Wave");   // ������ ���� (������ �̸�) 
	glutTimerFunc(DELAY, Timer, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);
	glutDisplayFunc(DrawScene);    // ��� �Լ��� ����   
	glutReshapeFunc(Reshape);   // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}

// ������ ��� �Լ� 
void DrawScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // ������ ������ ��ü�� ĥ�ϱ� 

	RenderMode();      // ȿ�� ��ĥ

	SceneMgr::GetInstance()->Render();

	glutPostRedisplay();
	glutSwapBuffers();// ȭ�鿡 ����ϱ�
}

void Mouse(int Mouse, int Button, int x, int y)
{
	SceneMgr::GetInstance()->Mouse(Mouse, Button, x, y);
}

void Timer(int n)
{
	SceneMgr::GetInstance()->Update();

	Reshape(MAPSIZE_W, MAPSIZE_H);
	glutTimerFunc(DELAY, Timer, 1);
}

void RenderMode()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GLU_CULLING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_CCW);
}

void KeyBoard(unsigned char key, int a, int b)
{
	SceneMgr::GetInstance()->KeyBoard(key, a, b);
}

void SpecialKeyBoard(int key, int a, int b)
{
	SceneMgr::GetInstance()->SpecialKeyBoard(key, a, b);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	SceneMgr::GetInstance()->SetView(w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}