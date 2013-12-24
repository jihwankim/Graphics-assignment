// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <gl/glut.h>
#include <list>
#include <time.h>
#include <math.h>
#include "Object.h"
#include "Camera.h"
#include "bmp.h"
#include<iostream>

#include "Project.h"

#define GL_PI 3.14159f
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800
#define UPDATE_RATE 0.05
#define TEXTURE_COUNT 7

static std::list<CObject*> object;
static std::list<CObject*> light;
//static CCamera *camera;
Object3DElement camera;
int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
GLfloat nRange = 200.f;
GLfloat minimumZ = 0.f;

ShapeType SelectedShapeType = ShapeType::SOLID_CUBE;
int ObjectCount = 0;

AUX_RGBImageRec *texRec[TEXTURE_COUNT];
GLuint texID[TEXTURE_COUNT];

double MainMenu;
double SubMenu1, SubMenu2;
int menu;

GLfloat GetWinZ()
{
	GLfloat front = 0.f;
	GLfloat sub = 0.000001f;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble posX, posY, posZ = nRange;
	GLfloat result;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glReadPixels(width/2, height/2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &result);

	while (posZ >= front)
	{
		gluUnProject(width/2, height/2, result, modelview, projection, viewport, &posX, &posY, &posZ);
		result -= sub;
	}

	result += sub;
	return 1.f - result;
}
void MenuFunc(int button)
{
	SelectedShapeType = (ShapeType)button;

	return;

	switch (button)
	{
	case 1:
		menu = 1;
		break;
	case 2:
		menu = 2;
		break;
	case 3:
		menu = 3;
		break;
	case 4:
		menu = 4;
		break;
	}

	glutPostRedisplay();
}
void SubMenu()
{
	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Sphere", 0);
	glutAddMenuEntry("Cube", 2);
	glutAddMenuEntry("Torus", 4);
	glutAddMenuEntry("Teapot", 6);

	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Sphere", 1);
	glutAddMenuEntry("Cube", 3);
	glutAddMenuEntry("Torus", 5);
	glutAddMenuEntry("Teapot", 7);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Solid Object", SubMenu1);
	glutAddSubMenu("Wire Object", SubMenu2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void SetupRC()
{
	// Light values

	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //ambient light
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //ambient light
	GLfloat lightPos[] = { 0.f, 0.f, 0.f , 20.0f }; //ambient light

	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glEnable(GL_CULL_FACE);  // Back face culling
	glFrontFace(GL_CCW);	   // Counter clock-wise polygons face out

	glEnable(GL_LIGHTING);   // Enable lighting	

	// Set light model to use ambient light specified by ambientLight
	glLightfv(GL_LIGHT0,GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

	glEnable(GL_COLOR_MATERIAL);// Enable Material color tracking

	// Load Texture
	glGenTextures(TEXTURE_COUNT, &texID[0]);
	for (int i = 0; i < TEXTURE_COUNT; ++i)
	{
		char buf[256];
		sprintf(buf, "Resource/%d.bmp", i);
		texRec[i] = auxDIBImageLoad(buf);
		
		glBindTexture(GL_TEXTURE_2D, texID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texRec[i]->sizeX, texRec[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data);
	}

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	
	// Front material ambient and diffuse colors track glColor
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0f, 0.0f, 0.0f,1.0f);
}
void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat fAspect = (GLfloat)width / (GLfloat)height;
	gluPerspective(60.0f, fAspect, 1.0f, nRange*2);
	gluLookAt(0.f, 0.f, -nRange, 0.f, 0.f, 0.f, 0, 1, 0);

	// 왜 Ortho를 이렇게 설정하면 제대로 배치되는가??!?!?!?
	//glOrtho(-width/2, width/2, height/2, -height/2, -300.f, 300.f);


// 	if (w <= h) 
// 		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);               //add
// 	else 
// 		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);  //add

	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
}
void Draw(GLenum eMode)
{
	for (auto& iter : object)
	{
		if (eMode == GL_SELECT) glLoadName((*iter).GetObjectNum());

		(*iter).render();
	}
}
void renderString(float x, float y, void *font, const char *string)
{
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}
void DrawStatus()
{
	glPushMatrix();
	glLoadIdentity();

	glColor3f(255.f, 255.f, 255.f);
	char temp[256];

	sprintf(temp, "Selected Shape : ");
	if (SelectedShapeType == SOLID_CUBE) strcat(temp, "SOLID_CUBE");
	else if (SelectedShapeType == WIRE_CUBE) strcat(temp, "WIRE_CUBE");
	else if (SelectedShapeType == SOLID_SPHERE) strcat(temp, "SOLID_SPHERE");
	else if (SelectedShapeType == WIRE_SPHERE) strcat(temp, "WIRE_SPHERE");
	else if (SelectedShapeType == SOLID_TORUS) strcat(temp, "SOLID_TORUS");
	else if (SelectedShapeType == WIRE_TORUS) strcat(temp, "WIRE_TORUS");
	else if (SelectedShapeType == SOLID_TEAPOT) strcat(temp, "SOLID_TEAPOT");
	else if (SelectedShapeType == WIRE_TEAPOT) strcat(temp, "WIRE_TEAPOT");

	//renderString(-100.f, -100.f, GLUT_BITMAP_8_BY_13, temp);
	renderString(-50.f, -110.f, GLUT_BITMAP_8_BY_13, temp);

	glPopMatrix();
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawStatus();	

	if (minimumZ == 0.f) minimumZ = GetWinZ();

	Draw(GL_RENDER);

	glutSwapBuffers();
}
void ContorolKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		camera.SetY(camera.GetY() - 5.f);

	if (key == GLUT_KEY_DOWN)
		camera.SetY(camera.GetY() + 5.f);

	if (key == GLUT_KEY_LEFT)
		camera.SetX(camera.GetX() - 5.f);

	if (key == GLUT_KEY_RIGHT)
		camera.SetX(camera.GetX() + 5.f);

	//printf("%f %f %f\n", eye.GetX(), eye.GetY(), eye.GetZ());
	glutPostRedisplay();
}
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(UPDATE_RATE * 1000, TimerFunc, 1);
}

CObject *SelectedObject = nullptr;

#define SELECT_BUF_SIZE 512
void ProcessHits(unsigned int uiHits, unsigned int *pBuffer)
{
	printf("#### %d\n", pBuffer[3]);
}
void SelectObject(int x, int y)
{
	static unsigned int aSelectBuffer[SELECT_BUF_SIZE];
	static unsigned int uiHits;
	static int aViewport[4];

	glGetIntegerv(GL_VIEWPORT, aViewport);

	glSelectBuffer(SELECT_BUF_SIZE, aSelectBuffer);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// 5x5 Region
	gluPickMatrix((double)x, (double)(aViewport[3] - y), 5.0, 5.0, aViewport);

	// Same Clipping Window as in Reshape()
	GLfloat fAspect = (GLfloat)width / (GLfloat)height;
	gluPerspective(60.0f, fAspect, 1.0f, nRange * 2);
	gluLookAt(0.f, 0.f, -nRange, 0.f, 0.f, 0.f, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	Draw(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	uiHits = glRenderMode(GL_RENDER);
	ProcessHits(uiHits, aSelectBuffer);

	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}
PositionState objectAllocate(int x, int y, Object3DElement *result)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ = 100.f;
	bool isEmpty = false;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;

	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	if (winZ == 1.0f)
		isEmpty = true;

	winZ -= (rand() % (int)(minimumZ * 100000)) / 100000.f;
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	result->SetPosition(posX, posY, posZ);

	if (isEmpty) // is Empty
		return EMPTY;
	return FULL;
}
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Object3DElement pos;
		switch (objectAllocate(x, y, &pos))
		{
		case EMPTY:
		{
					  CObject *temp = new CObject(ObjectCount++);
					  //srand((unsigned)time(NULL));
					  srand(GetTickCount());

					  temp->SetAngle(0.005f * (rand() % 900));
					  temp->SetColor(rand() % 256 + 10, rand() % 256 + 10, rand() % 256 + 10);
					  
					  temp->SetStartPosition(0.f, 0.f, 0.f);
					  //temp->SetPosition((GLfloat)x - width / 2, (GLfloat)y - height / 2, 0.f);

					  temp->SetPosition(pos.GetX(), pos.GetY(), pos.GetZ());

					  temp->SetRotate(0.1f * (rand() % 100) * UPDATE_RATE, 0.1f * (rand() % 100) * UPDATE_RATE, 0.1f * (rand() % 100) * UPDATE_RATE);
					  temp->SetShapeType(SelectedShapeType);
					  temp->SetSize(rand() % 20 + 10.f);
					  temp->SetTexID(texID[rand() % TEXTURE_COUNT]);

					  printf("Object Click : %d/%d\n", x, y);
					  printf("World Click  : %f/%f/%f\n", pos.GetX(), pos.GetY(), pos.GetZ());

					  object.push_back(temp);
		}
					  break;
		case FULL :
			SelectObject(x, y);
			break;
		}
	}
	glutPostRedisplay();
}
void t()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
int _tmain(int argc, _TCHAR* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	glutInitWindowPosition(0,0);
	int a = glutCreateWindow("Graphics Assignment #131018 kim-jihwan");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1); //add 
	glutSpecialFunc(ContorolKey);
	glutMouseFunc(Mouse);
	glutDisplayFunc(RenderScene);
	SetupRC();


	//glutCreateSubWindow(a, WINDOW_WIDTH/2 - 100, 0, 100, 400);
 	//glutDisplayFunc(t);
 	//glutTimerFunc(33, TimerFunc, 1);
	//SetupRC();

	SubMenu();
	glutMainLoop();
	

	return 0;
}

