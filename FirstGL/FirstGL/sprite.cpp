#include "sprite.h"

Sprite::Sprite()
:
ambient_material_{0, 0, 0, 0}, 
diffuse_material_{0, 0, 0, 0}, 
specular_material_{0, 0, 0, 0}
{
}

void Sprite::SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	ambient_material_[0] = r;
	ambient_material_[1] = g;
	ambient_material_[2] = b;
	ambient_material_[3] = a;
}

void Sprite::SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	diffuse_material_[0] = r;
	diffuse_material_[1] = g;
	diffuse_material_[2] = b;
	diffuse_material_[3] = a;
}


void Sprite::SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	specular_material_[0] = r;
	specular_material_[1] = g;
	specular_material_[2] = b;
	specular_material_[3] = a;
}
