#include "ground.h"

Ground::Ground()
{
}

void Ground::Init()
{
	SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
	SetSpecularMaterial(0.0f, 0.0f, 0.0f, 1.0f);
}

void Ground::Draw()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecularMaterial);
	// 开启颜色追踪材质，让光照效果依赖于物体本身的颜色
	glEnable(GL_COLOR_MATERIAL);

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	// 画地面的棋盘格
	for (int z = 0; z < 20; z ++)
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20;  x ++)
		{
			float xStart = x * 10.0f - 100.0f;
			unsigned char color = (z % 2) ^ (x % 2) ? 41 : 200;
			glColor4ub(color, color, color, 255);
			glVertex3f(xStart, -1.0f, zStart);
			glVertex3f(xStart + 10.f, -1.0f, zStart);
			glVertex3f(xStart + 10.f, -1.0f, zStart - 10.0f);
			glVertex3f(xStart, -1.0f, zStart - 10.0f);
		}
	}
	glEnd();
}
