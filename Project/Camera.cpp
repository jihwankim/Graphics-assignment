#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

void CCamera::update()
{
	gluLookAt(
		mEyePosition.GetX(), mEyePosition.GetY(), mEyePosition.GetZ(),
		mCenterPosition.GetX(), mCenterPosition.GetY(), mCenterPosition.GetZ(),
		mUpVector.GetX(), mUpVector.GetY(), mUpVector.GetZ());
}
