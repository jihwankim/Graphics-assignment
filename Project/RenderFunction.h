#include <gl/glut.h>

#define SLICES 30
#define STACKS 30

void __stdcall SolidSphere(GLdouble radius);
void __stdcall SolidCube(GLdouble size);
void __stdcall SolidTeapot(GLdouble size);
void __stdcall SolidTorus(GLdouble innerRadius);

void __stdcall WireSphere(GLdouble radius);
void __stdcall WireCube(GLdouble size);
void __stdcall WireTeapot(GLdouble size);
void __stdcall WireTorus(GLdouble innerRadius);