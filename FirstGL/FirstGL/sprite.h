#pragma once
#include "ggl.h"

class Sprite
{
protected:
	GLfloat ambient_material_[4];

	GLfloat diffuse_material_[4];

	GLfloat specular_material_[4];

public:

	Sprite();

	virtual ~Sprite() = default;

	// 设置模型表面材质的环境光反射系数
	void SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// 设置材质的漫反射反射系数
	void SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	// 设置镜面反射的反射系数
	void SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Draw() = 0;
};
