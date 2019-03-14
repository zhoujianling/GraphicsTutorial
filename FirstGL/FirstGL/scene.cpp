#include  "scene.h"

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
}


void Draw()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES); // 表明要绘制图形：三角形
	glColor4ub(255, 255, 255, 255); // 第一个点的颜色
	glVertex3d(-0.2f, -0.2f, -1.5f); // 第一个点的坐标
	glColor4ub(255, 0, 0, 255); // 第二个点的颜色
	glVertex3d(0.2f, -0.2f, -1.5f); // 第二个点的坐标
	glColor4ub(0, 255, 0, 255);
	glVertex3d(0.f, 0.2f, -1.5f);
	glEnd(); // 如果给 3 个点，绘制一个三角形，给6个点，绘制两个三角形, 逆时针方向
	// 区分正反面：逆时针方向则为图形的正面
}