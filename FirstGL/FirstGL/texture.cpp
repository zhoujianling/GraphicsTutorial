#include  "scene.h"
#include  "utils.h"

GLuint texture;

// 这个文件记录了 OpenGL 的纹理贴图的实现

// 在 Init() 函数最后面加载纹理
void DoAfterInit()
{
	// 加载图片纹理
	texture = CreateTexture2DFromBmp("Res/Texture.bmp");
}

void DrawModelWithUV()
{
	glBegin(GL_QUADS); 
	// 第一个点的坐标， 颜色，纹理坐标
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(-0.0f, -0.0f, -2.5f); 
	glTexCoord2f(0.0f, 0.0f);
	// 第二个点的坐标， 颜色，纹理坐标
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(-0.0f, +0.2f, -2.5f); 
	glTexCoord2f(0.0f, 1.0f);
	// 第三个点的坐标， 颜色，纹理坐标
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(0.2f, +0.2f, -2.5f); 
	glTexCoord2f(1.0f, 1.0f);
	// 第四个点的坐标， 颜色，纹理坐标
	glColor4ub(255, 255, 255, 255); 
	glVertex3d(0.2f, 0.0f, -2.5f); 
	glTexCoord2f(1.0f, 0.0f);
	glEnd(); 
}


void DrawWithTexture()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D); // 开启纹理
	glBindTexture(GL_TEXTURE_2D, texture);
	// 模型表面的颜色需要是白色，否则会变成颜色和纹理混合
	DrawModelWithUV();
}

