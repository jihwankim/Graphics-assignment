#include "RenderFunction.h"

void __stdcall SolidSphere(GLdouble radius)
{
	glutSolidSphere(radius, SLICES, STACKS);
}

void __stdcall SolidCube(GLdouble size)
{
	glutSolidCube(size);
}

void __stdcall SolidTeapot(GLdouble size)
{
	glutSolidTeapot(size);
}

void __stdcall SolidTorus(GLdouble innerRadius)
{
	glutSolidTorus(innerRadius, innerRadius * 2.f, SLICES, STACKS);
}

void __stdcall WireSphere(GLdouble radius)
{
	glutWireSphere(radius, SLICES, STACKS);
}

void __stdcall WireCube(GLdouble size)
{
	glutWireCube(size);
}

void __stdcall WireTeapot(GLdouble size)
{
	glutWireTeapot(size);
}

void __stdcall WireTorus(GLdouble innerRadius)
{
	glutWireTorus(innerRadius, innerRadius * 2.f, SLICES, STACKS);
}
