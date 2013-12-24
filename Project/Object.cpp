#include "Object.h"

CObject::CObject(int num)
: mShapeType(SOLID_SPHERE), mSize(0.f), mAngle(0.f), mNowAngle(0.f)
{
	mObjectNum = num;
}
CObject::~CObject()
{
}

GLvoid CObject::render(bool stop)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_GEN_R);
	//glEnable(GL_TEXTURE_GEN_Q);

	glBindTexture(GL_TEXTURE_2D, GetTexID());
	//gluQuadricTexture(gluNewQuadric(), 1);
	glTranslatef(mStartPosition.GetX(), mStartPosition.GetY(), mStartPosition.GetZ());

	glRotatef(mNowAngle, mRotate.GetX(), mRotate.GetY(), mRotate.GetZ());
	glTranslatef(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());

	glColor3ub(mColor.GetX(), mColor.GetY(), mColor.GetZ());
	Shape[mShapeType](mSize);

	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	//glDisable(GL_TEXTURE_GEN_R);
	//glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);

	if (stop == false)
		mNowAngle += mAngle;

	if (mNowAngle >= 360.f)
		mNowAngle = 0.f;

	glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);

	glPopMatrix();
}

