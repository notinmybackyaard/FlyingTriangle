#include "LoginScene.h"
#include "SceneMgr.h"

CLoginScene::CLoginScene()
{
}

CLoginScene::~CLoginScene()
{
}

void CLoginScene::Initialize()
{
	PlaySound(0, 0, 0);
	PlaySound("LoginBGM.wav", NULL, SND_ASYNC | SND_NOSTOP);
	start = std::chrono::system_clock::now();
	TextureSetup();
	PlayerName = "";
	IsLoginUIOn = false;
	IsPress = false;
	Index = 0;
}

void CLoginScene::Update()
{
	if (elapsed_seconds.count() >= 10.0)
		return;

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
}

void CLoginScene::Render()
{

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3d(-(MAPSIZE_W / 2), -(MAPSIZE_H / 2), -100);
	glTexCoord2f(1, 0);
	glVertex3d((MAPSIZE_W / 2), -(MAPSIZE_H / 2), -100);
	glTexCoord2f(1, 1);
	glVertex3d((MAPSIZE_W / 2), (MAPSIZE_H / 2), -100);
	glTexCoord2f(0, 1);
	glVertex3d(-(MAPSIZE_W / 2), (MAPSIZE_H / 2), -100);
	glEnd();
	glPopMatrix();

	//glPushMatrix();
	//glColor3d(.0, 0.0, 0.0);
	//glTranslated(-300, 100.0, 0.0);
	//Text = "Hello!";
	//int len = Text.length();
	//for (int i = 0; i < len; i++)
	//   glutStrokeCharacter(GLUT_STROKE_ROMAN, Text[i]);
	//glPopMatrix();
	//string = to_string(Score);

	if (elapsed_seconds.count() >= 1 || IsLoginUIOn)
	{
		glPushMatrix();
		if (!IsLoginUIOn)
			glColor4d(0.0, 0.0, 0.0, (elapsed_seconds.count() - 1) / 2);
		if (IsLoginUIOn)
			glColor4d(0.0, 0.0, 0.0, 1.0);
		String = "Hello!";
		glRasterPos3f(-100.f, 80.f, 0.0f);
		len = String.length();
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
		glPopMatrix();
	}

	if (elapsed_seconds.count() >= 2 || IsLoginUIOn)
	{
		glPushMatrix();
		if(!IsLoginUIOn)
			glColor4d(0.0, 0.0, 0.0, (elapsed_seconds.count() - 2) / 2);
		if (IsLoginUIOn)
			glColor4d(0.0, 0.0, 0.0, 1.0);
		String = "What's Your Name?";
		glRasterPos3f(-100.f, 40.0f, 0.0f);
		 len = String.length();
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
		glPopMatrix();
	}
	if (IsLoginUIOn)
	{
		String = "Hi I'm ";
		glColor4f(0.2f, 0.5f, 1.0f, 1.0f);
		glRasterPos2f(-100.f, -50.f);

		len = String.length();

		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);

		len = PlayerName.length();

		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, PlayerName[i]);

		char* value;
		if (IsPress)
		{
			value = "Wait...";
			SceneMgr::GetInstance()->SetScene(SCENE_STAGE);
		}
		else
			value = "Press Enter When You Ready";
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glRasterPos2f(-100.f, -200.f);
		len = strlen(value);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, value[i]);
	}
}

void CLoginScene::Release()
{
}

void CLoginScene::Mouse(int Mouse, int Button, int x, int y)
{
}

void CLoginScene::KeyBoard(unsigned char key, int a, int b)
{

	IsLoginUIOn = true;

	if (IsPress)
		return;

	if (key == 13)
		IsPress = true;

	if (key == 8)
	{
		if(PlayerName.size() > 0)
			PlayerName.pop_back();
		return;
	}
	if (PlayerName.length() >= MAX_LEN)
		return;
	PlayerName.push_back(key);
}

void CLoginScene::SpecialKeyBoard(int key, int a, int b)
{
}

void CLoginScene::SetView(int w, int h)
{

	gluPerspective(VIEWANGLE, w / h, 1, 2000);

	gluLookAt(0, 0, 750,
		0, 0, 0,
		0, 1, 0);

}

void CLoginScene::TextureSetup()
{
	glGenTextures(1, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	pBytes = LoadDIBitmap("LoginTexture.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 500, 500, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

GLubyte * CLoginScene::LoadDIBitmap(const char * filename, BITMAPINFO ** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}