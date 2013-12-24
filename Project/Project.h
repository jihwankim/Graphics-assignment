#pragma once

enum PositionState
{
	EMPTY = 0,
	FULL = 1,
};

GLfloat GetWinZ();
void MenuFunc(int button);
void SubMenu();
void SetupRC();
void ChangeSize(int w, int h);
void Draw(GLenum eMode);
void RenderScene(void);
void ContorolKey(int key, int x, int y);
void TimerFunc(int value);
void ProcessHits(unsigned int uiHits, unsigned int *pBuffer);
void SelectObject(int x, int y);
PositionState objectAllocate(int x, int y, Object3DElement *result);
GLvoid Mouse(int button, int state, int x, int y);
