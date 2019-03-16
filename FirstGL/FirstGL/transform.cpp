#include "scene.h"

// 这个文件记录了 OpenGL 的矩阵变换

void DrawTriangleZero()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES); // 表明要绘制图形：三角形
	glColor4ub(255, 255, 255, 255); // 第一个点的颜色
	glVertex3d(-0.2f, -0.2f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 0, 0, 255); // 第二个点的颜色
	glVertex3d(0.2f, -0.2f, -2.5f); // 第二个点的坐标
	glColor4ub(0, 255, 0, 255);
	glVertex3d(0.f, 0.2f, -2.5f);
	glEnd(); // 如果给 3 个点，绘制一个三角形，给6个点，绘制两个三角形, 逆时针方向
	// 区分正反面：逆时针方向则为图形的正面
}


void Draw2()
{
	DrawTriangleZero();
	glLoadIdentity();
	// 物体初始有一个坐标轴和世界坐标轴平行，此时将物体的坐标旋转（坐标轴也旋转），沿
	// 原坐标系的 (0, 0, 1) 旋转30°，遵循右手定则
	glRotatef(30.0, 0, 0, 1.); 

	glTranslatef(0.5f, 0.9f, 0.f); // 平移物体
}
