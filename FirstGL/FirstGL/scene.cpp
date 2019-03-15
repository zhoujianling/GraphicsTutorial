#include  "scene.h"
#include  "utils.h"

GLuint texture;

/**
 * 屏幕正中心是世界坐标系原点
 * z 轴指向屏幕外面, 所以 z 坐标要设负值
 */
void Init()
{
	// OpenGl 存在当前矩阵的概念，通过 glMatrixMode 设置当前矩阵的 模式
	glMatrixMode(GL_PROJECTION);
	// ?, 画布的宽高比， 最近可以看到的距离，最远可以看到的距离 
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.f);
	glMatrixMode(GL_MODELVIEW); // 切换当前矩阵到模型视口矩阵
	glLoadIdentity();

	//// 加载图片纹理
	//int nFileSize = 0;
	//unsigned char *bmpFileContent = LoadFile("Res/Texture.bmp", nFileSize);
	//int bmpWidth = 0, bmpHeight = 0;
	//unsigned char *bmpImageData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);

	//if (bmpWidth > 0 && bmpHeight > 0)
	//{
	//	fprintf(stdout, "Init OK.");
	//	texture = CreateTexture2D(bmpImageData, bmpWidth, bmpHeight, GL_RGB);
	//} else
	//{
	//	fprintf(stderr, "Cannot decode bmp file.\n");
	//}
	texture = CreateTexture2DFromBmp("Res/Texture.bmp");
}

void DrawModel()
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


void Draw()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D); // 开启纹理
	glBindTexture(GL_TEXTURE_2D, texture);
	// 模型表面的颜色需要是白色，否则会变成颜色和纹理混合
	DrawModel();
}
