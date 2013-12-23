#pragma once

#include "Object.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void SetEyePosition(GLfloat x, GLfloat y, GLfloat z) { mEyePosition.SetX(x); mEyePosition.SetY(y); mEyePosition.SetZ(z); }
	void SetCenterPosition(GLfloat x, GLfloat y, GLfloat z) { mCenterPosition.SetX(x); mCenterPosition.SetY(y); mCenterPosition.SetZ(z); }
	void SetUpVector(GLfloat x, GLfloat y, GLfloat z) { mUpVector.SetX(x); mUpVector.SetY(y); mUpVector.SetZ(z); }

	void update();
private :
	Object3DElement mEyePosition;
	Object3DElement mCenterPosition;
	Object3DElement mUpVector;
};

