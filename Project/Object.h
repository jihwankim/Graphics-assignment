#pragma once
#include <gl/glut.h>
#include "RenderFunction.h"

enum axis
{
	X = 0,
	Y = 1,
	Z = 2,
};
enum ShapeType
{
	SOLID_SPHERE = 0, 
	WIRE_SPHERE = 1,
	SOLID_CUBE = 2, 
	WIRE_CUBE = 3,
	SOLID_TORUS = 4,
	WIRE_TORUS = 5,
	SOLID_TEAPOT = 6, 
	WIRE_TEAPOT = 7,
};

class Object3DElement
{
public :
	Object3DElement() { mPosition[X] = 0.f; mPosition[Y] = 0.f; mPosition[Z] = 0.f; }
	Object3DElement(GLfloat x, GLfloat y, GLfloat z) { SetPosition(x, y, z); }
	~Object3DElement() {}

	GLfloat GetX() { return mPosition[X]; }
	GLfloat GetY() { return mPosition[Y]; }
	GLfloat GetZ() { return mPosition[Z]; }

	void SetX(GLfloat value) { mPosition[X] = value; }
	void SetY(GLfloat value) { mPosition[Y] = value; }
	void SetZ(GLfloat value) { mPosition[Z] = value; }
	void SetPosition(GLfloat x, GLfloat y, GLfloat z) { mPosition[X] = x; mPosition[Y] = y; mPosition[Z] = z; }

private:
	GLfloat mPosition[3];
};

class CObject
{
public:
	CObject();
	~CObject();

	void SetAngle(GLfloat value) { mAngle = value; }
	void SetStartPosition(GLfloat x, GLfloat y, GLfloat z) { mStartPosition.SetX(x); mStartPosition.SetY(y); mStartPosition.SetZ(z); }
	void SetRotate(GLfloat x, GLfloat y, GLfloat z) { mRotate.SetX(x); mRotate.SetY(y); mRotate.SetZ(z); }
	void SetPosition(GLfloat x, GLfloat y, GLfloat z) { mPosition.SetX(x); mPosition.SetY(y); mPosition.SetZ(z); }
	void SetColor(GLfloat x, GLfloat y, GLfloat z) { mColor.SetX(x); mColor.SetY(y); mColor.SetZ(z); }
	void SetShapeType(ShapeType value) { mShapeType = value; }
	void SetSize(GLdouble value) { mSize = value; }

	GLfloat GetAngle() { return mAngle; }
	Object3DElement GetStartPosition() { return mStartPosition; }
	Object3DElement GetRotate() { return mRotate; }
	Object3DElement GetPosition() { return mPosition; }
	Object3DElement GetColor() { return mColor; }
	ShapeType GetShapeType() { return mShapeType; }
	GLdouble GetSize() { return mSize; }

	GLvoid render();

private:
	Object3DElement mStartPosition;
	Object3DElement mPosition;
	Object3DElement mRotate;
	GLfloat mAngle;
	GLfloat mNowAngle;
	Object3DElement mColor;
	ShapeType mShapeType;
	GLdouble mSize;
};