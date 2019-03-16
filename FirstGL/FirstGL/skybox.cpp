#include "skybox.h"
#include "utils.h"

void SkyBox::Init(const char* imageDir)
{
	char temp[256];
	strcpy(temp, imageDir);
	strcat(temp, "Front.bmp");
	mTextures[0] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Back.bmp");
	mTextures[1] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Left.bmp");
	mTextures[2] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Right.bmp");
	mTextures[3] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Top.bmp");
	mTextures[4] = CreateTexture2DFromBmp(temp);

	strcpy(temp, imageDir);
	strcat(temp, "Bottom.bmp");
	mTextures[5] = CreateTexture2DFromBmp(temp);

	mFastDrawCall = CreateDisplayList([this]() -> void {DrawCommand();});
}

/**
 */
void SkyBox::DrawCommand()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// Front
	glBindTexture(GL_TEXTURE_2D, mTextures[0]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, +.5f, -0.5f);
	glEnd();

	// Back
	glBindTexture(GL_TEXTURE_2D, mTextures[1]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, -.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, +.5f, +0.5f);
	glEnd();

	// Left 面
	glBindTexture(GL_TEXTURE_2D, mTextures[2]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, -.5f, +0.5f);
	glEnd();

	// Right 面
	glBindTexture(GL_TEXTURE_2D, mTextures[3]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(+0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(+0.5f, -.5f, +0.5f);
	glEnd();

	// Top 面
	glBindTexture(GL_TEXTURE_2D, mTextures[4]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, +.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, +.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, +.5f, +0.5f);
	glEnd();

	// Bottom 面
	glBindTexture(GL_TEXTURE_2D, mTextures[5]);
	glBegin(GL_QUADS);
	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(+0.5f, -.5f, -0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(+0.5f, -.5f, +0.5f);

	glColor4ub(255, 255, 255, 255);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-0.5f, -.5f, +0.5f);
	glEnd();
}

/*
 * 把绘制过程存储下载，Init() 里做初始化，储存到一个过程里
 * 但是不调用，得到一个 GLuint 类型的描述符xx，Draw() 阶段通过 glCallList(xx) 调用
 * 显示列表可以优化绘图性能
 */
void SkyBox::Draw()
{
	glCallList(mFastDrawCall);
}