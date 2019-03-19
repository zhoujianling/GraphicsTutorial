#include "sprite.h"

Sprite::Sprite()
:
mAmbientMaterial{0, 0, 0, 0}, 
mDiffuseMaterial{0, 0, 0, 0}, 
mSpecularMaterial{0, 0, 0, 0}
{
}

void Sprite::SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	mAmbientMaterial[0] = r;
	mAmbientMaterial[1] = g;
	mAmbientMaterial[2] = b;
	mAmbientMaterial[3] = a;
}

void Sprite::SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	mDiffuseMaterial[0] = r;
	mDiffuseMaterial[1] = g;
	mDiffuseMaterial[2] = b;
	mDiffuseMaterial[3] = a;
}


void Sprite::SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	mSpecularMaterial[0] = r;
	mSpecularMaterial[1] = g;
	mSpecularMaterial[2] = b;
	mSpecularMaterial[3] = a;
}
