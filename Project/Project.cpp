// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include <gl/glut.h>
#include "Object.h"
#include <list>
#include <time.h>
#define GL_PI 3.1415f
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static std::list<CObject*> object;
static std::list<CObject*> light;
static CObject *camera;

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

	// Front material ambient and diffuse colors track glColor
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0f, 0.0f, 0.0f,1.0f);
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = -300.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);               //add
	else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);  //add

	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (auto& iter : object)
		(*iter).render();

	glutSwapBuffers();
	/*
	// Earth and Moon angle of revolution
	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;
	static float fMarsRot = 0.0f;
	static float fJupiterRot = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix(); // 초기 메트릭스 저장

	//시점을 뒤로 300만큼 이동해서 관측 시점 지정
	glTranslatef(0.0f, 0.0f, -300.0f);	
	//태양을 그린다
	glColor3ub(255, 255, 0);
	glutSolidCube(15.f);
	//glutSolidSphere(15.0f, 30, 17);

	// 지구
	//y축으로 일정하게 증가해서 회전하는 좌표계를 세팅
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);

	glTranslatef(105.0f,0.0f,0.0f); // x 방향으로 105만큼 평행이동
	//glTranslatef(300.0f, 100.0f, 100.0f); // x 방향으로 105만큼 평행이동
	glColor3ub(0,0,255); 	 // 지구를 그린다
	glutSolidSphere(15.0f, 30, 17);

	// 달
	glRotatef(fMoonRot, 0.0f,1.0f,0.0f);
	glTranslatef(25.0f,0.0f,0.0f);
	glColor3ub (255,255,255);
	glutSolidSphere(8.0f,30,17);

	glPopMatrix();
	fMoonRot+= 15.0f;

	// 화성
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -300.0f);	

	glRotatef(fMarsRot, 0.0f,1.0f,0.0f);
	glTranslatef(200.0f,0.0f,0.0f);
	glColor3ub (255,0,0);
	glutSolidSphere(13.0f,30,17);

	glPopMatrix();
	fMarsRot+= 4.0f;

	// 목성
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -350.0f);	

	glRotatef(fJupiterRot, 0.0f,1.0f,0.0f);
	glTranslatef(250.0f,0.0f,0.0f);
	glColor3ub (0,255,0);
	//glutSolidSphere(30.0f,30,17);
	//glutSolidCone(20.0f, 50.f, 30, 17);

	//glutSolidCube(50.f);

	glPopMatrix();
	fJupiterRot+= 3.0f;

	// Step earth orbit 5 degrees
	fEarthRot += 5.0f;
	if(fEarthRot > 360.0f)
		fEarthRot = 0.0f;

	

	glutSwapBuffers();
	*/
}
void ContorolKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot -=5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot +=5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -=5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot +=5.0f;

	glutPostRedisplay();
}
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}
void Init()
{
	CObject *temp = new CObject();
	object.push_back(temp);

	temp->SetAngle(5.f);
	temp->SetRotate(0.f, 1.f, 0.f);
	temp->SetPosition(100.f, 0.f, 0.f);
	temp->SetShapeType(WIRE_TORUS);
	temp->SetStartPosition(0.f, 0.f, 0.f);
	temp->SetColor(0, 255, 0);
	temp->SetSize(50.f);
}
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		srand((unsigned)time(NULL));
		CObject *temp = new CObject();

		temp->SetAngle(0.01f * (rand()%900) + 1.f);
		temp->SetColor(rand() % 256, rand() % 256, rand() % 256);
		temp->SetStartPosition(0.f, 0.f, 0.f);
		temp->SetRotate(0.1f * (rand()%100), 0.1f * (rand()%100), 0.1f * (rand()%100));
		temp->SetShapeType((ShapeType)(rand() % 8));
		temp->SetSize(rand() % 20 + 10.f);
		temp->SetPosition(rand() % 200, rand() % 200, rand() % 200);

		object.push_back(temp);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Graphics Assignment #131018 kim-jihwan");

	//Init();
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1); //add 
	glutSpecialFunc(ContorolKey);
	glutMouseFunc(Mouse);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}

