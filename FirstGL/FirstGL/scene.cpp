#include "scene.h"
#include "utils.h"
#include "skybox.h"
#include "model.h"

SkyBox skyBox;
Model model;

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
	skyBox.Init("Res/");
	//model.Init("Res/Box.obj");
	model.Init("Res/Dog.ply");
}

void DrawModel()
{
	glBegin(GL_QUADS); 
	glColor4ub(255, 50, 0, 255); glVertex3d(-0.0f, -0.0f, -2.5f); 

	glColor4ub(255, 50, 0, 255); glVertex3d(-0.0f, +0.2f, -2.5f); 

	glColor4ub(255, 50, 0, 255); glVertex3d(0.2f, +0.2f, -2.5f); 

	glColor4ub(255, 50, 0, 255); glVertex3d(0.2f, 0.0f, -2.5f); 
	// 绘制了第一个四边形

	glColor4ub(255, 250, 0, 255); glVertex3d(-0.0f, -0.0f, -3.5f); 

	glColor4ub(255, 250, 0, 255); glVertex3d(-0.0f, +0.2f, -3.5f); 

	glColor4ub(255, 250, 0, 255); glVertex3d(0.2f, +0.2f, -3.5f); 

	glColor4ub(255, 250, 0, 255); glVertex3d(0.2f, 0.0f, -3.5f); 
	// 绘制了第一个四边形
	glEnd(); 
}



void Draw()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	// 每一帧绘制之前要清除颜色缓冲区和深度缓冲区(初始化为1.0，即最远)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	skyBox.DrawCommand();
	glEnable(GL_DEPTH_TEST); // 保证近的物体会挡住远的物体
	model.Draw();
	// DrawModel();
}
