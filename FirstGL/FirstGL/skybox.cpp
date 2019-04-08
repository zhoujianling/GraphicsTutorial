#include "skybox.h"
#include "utils.h"

SkyBox::SkyBox():
textures_{0, 0, 0, 0, 0, 0},
fast_draw_call_(0),
curr_camera_(nullptr)
{
}

void SkyBox::Init(const char* image_dir, Camera *c)
{
	this->curr_camera_ = c;

	char temp[256];
	strcpy(temp, image_dir);
	strcat(temp, "Front.bmp");
	textures_[0] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Back.bmp");
	textures_[1] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Left.bmp");
	textures_[2] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Right.bmp");
	textures_[3] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Top.bmp");
	textures_[4] = CreateTexture2DFromBmp(temp);

	strcpy(temp, image_dir);
	strcat(temp, "Bottom.bmp");
	textures_[5] = CreateTexture2DFromBmp(temp);

	fast_draw_call_ = CreateDisplayList([this]() -> void {DrawCommand();});
}

/**
 */
void SkyBox::DrawCommand()
{
	glDisable(GL_DEPTH_TEST); // 如果不禁用， 可能挡住别的物体
	glDisable(GL_LIGHTING); // 如果不禁用，光照可能导致天空盒变黑
	glEnable(GL_TEXTURE_2D);

	// Front
	glBindTexture(GL_TEXTURE_2D, textures_[0]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[1]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[2]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[3]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[4]);
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
	glBindTexture(GL_TEXTURE_2D, textures_[5]);
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

	glEnable(GL_DEPTH_TEST); // 如果不禁用， 可能挡住别的物体
	glEnable(GL_LIGHTING); // 如果不禁用，光照可能导致天空盒变黑
	glEnable(GL_TEXTURE_2D);
}

/*
 * 把绘制过程存储下载，Init() 里做初始化，储存到一个过程里
 * 但是不调用，得到一个 GLuint 类型的描述符xx，Draw() 阶段通过 glCallList(xx) 调用
 * 显示列表可以优化绘图性能
 */
void SkyBox::Draw()
{
	glPushMatrix();
	glTranslatef(curr_camera_->GetPosition().v1,
		curr_camera_->GetPosition().v2, 
		curr_camera_->GetPosition().v3);
	glCallList(fast_draw_call_);
	glPopMatrix();
	//glLoadIdentity();


}