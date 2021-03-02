#include <iostream>
#include "GL/freeglut.h"
#include "Box2D/Box2D.h"
#include <vector>
#include "Viewer.h"

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(disable:4996)
#include "stb_image.h"
// #include "Render.h"

using namespace std;

/// <summary>
/// setup 함수들
/// </summary>

// Window screen size
int scr_width = 1024;
int scr_height = 800;
// Viewer class cache
Viewer opengl_viewer;

// texture cache
GLuint mTexture;
// texture info
int width, height, channel;


bool LoadMeshFromFile(const char* texfile) {
	// image loader
	glGenTextures(1, &mTexture);

	FILE* fp = fopen(texfile, "rb");
	if (!fp) {
		printf("ERROR : No %s.\n fail to bind %d\n", texfile, mTexture);
		return false;
	}

	unsigned char* image = stbi_load_from_file(fp, &width, &height, &channel, 4);
	fclose(fp);

	// bind
	glBindTexture(GL_TEXTURE_2D, mTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_REPLACE);

	cout << "image loaded!" << '\n';
	return true;
}

void Mouse(int mouse_event, int state, int x, int y) {
	// mouse 클릭 시 호출됨
	opengl_viewer.Mouse(mouse_event, state, x, y);
}

void Motion(int x, int y) {
	// mouse drag하는 동안 호출됨
	// (x,y)는 현재 drag되고 있는 최신 좌표인듯.
	opengl_viewer.Motion(x, y);
}

void Keyboard(unsigned char key, int x, int y) {
	opengl_viewer.Dokeyboard(key, x, y);
}

void Render()
{
	opengl_viewer.Render();
}

// 프레임당 업데이트
void Update(int value)
{
	opengl_viewer.Update();

	glutPostRedisplay();
	// 10ms 뒤에 다시 호출
	glutTimerFunc(10, Update, 0);	//Recursive function
}

void Reshape(int _width, int _height)
{
	int w = _width, h = _height;
	opengl_viewer.Reshape(w, h);
}

void Initialize(int width, int height)
{
	// glperspective 초기설정
	// world space -> camera space
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, (float)scr_width / scr_height, 0.1, 1000);

	// glLootat
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	// gl_modelview 초기설정
	// object space -> world space
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	opengl_viewer.Initialize(width, height);
}

int main(int argc, char** argv)
{
	// Initialize glut
	// 640 * 640
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	// 중심좌표를 옮겨야 하나..?
	// 주석치면 (0,0)
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(scr_width, scr_height);


	glutCreateWindow("Final_term_project");

	LoadMeshFromFile("Image.jpg");

	Initialize(width, height);
	glutTimerFunc(10, Update, 0);	//Update physics simulation
	glutDisplayFunc(Render);		//If you want to render, Use it.

	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);		//Reshape by window size

	glutKeyboardFunc(Keyboard);	//If you want to use keyborad event,
	// glutKeyboardUpFunc(DoRelasekey);

	//Activate this!
	glutMainLoop();

	return 0;
}