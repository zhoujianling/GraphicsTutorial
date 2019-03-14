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

void DrawTriangle()
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

void DrawTriangleStrip()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_STRIP); // 表明要绘制图形：三角形
	//
	glColor4ub(0, 0, 255, 255); glVertex3d(-0.0f, +0.2f, -1.5f); 
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.0f, -0.0f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.2f, +0.2f, -1.5f); 
	// 截至这行 ，出现了一个三角形
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.3f, -0.1f, -1.5f); 
	// 截至这行 ，出现了两个三角形

	glEnd(); 
}

void DrawTriangleFan()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN); 
	//
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.0f, -0.0f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.2f, +0.0f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.1f, +0.15f, -1.5f); 
	// 截至这行 ，出现了一个三角形
	glColor4ub(0, 255, 255, 255); glVertex3d(-0.1f, +0.15f, -1.5f); 
	// 截至这行 ，出现了两个三角形, 以第一个顶点为中心呈扇形分布

	glEnd(); 
}

/**
 * 绘制方形的点，非原点, 点在默认情况下大小为 1.0
 */
void DrawVertex()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(3); // 默认为1
	glBegin(GL_POINTS); 
	// 
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.0f, -0.0f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.2f, +0.0f, -1.5f); 
	glEnd(); 
}

void DrawLine()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(10.); // 设置线段宽度
	glBegin(GL_LINES); 
	// 每两个点连接一条线段
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	// 画出一条线段
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	// 画出两条线段
	glEnd(); 
	
}

void DrawLineLoop()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(7.); // 设置线段宽度
	glBegin(GL_LINE_LOOP); 
	// 每N个点连接(N)条线段, 自动首尾相接
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	// 画出一条线段
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	// 画出两条线段
	glEnd(); 
}

void DrawLineStrip()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(7.); // 设置线段宽度
	glBegin(GL_LINE_STRIP); 
	// 每N个点连接(N- 1)条线段
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	// 画出一条线段
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	// 画出两条线段
	glEnd(); 
}

/**
 * 绘制四边形
 */
void DrawQuads()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS); 
	// 每N个点连接(N- 1)条线段
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, -0.0f, -1.5f); 
	glColor4ub(0, 255, 255, 255); glVertex3d(-0.2f, -0.1f, -1.5f); 
	glEnd(); 
}

/**
 * 绘制四边形条带
 */
void DrawQuadStrip()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUAD_STRIP); 
	// 每N个点连接(N- 1)条线段
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, -0.2f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.5f, -0.2f, -1.5f); 
	glColor4ub(0, 255, 255, 255); glVertex3d(-0.2f, +0.1f, -1.5f); 
	glColor4ub(0, 0, 255, 255); glVertex3d(+0.7f, +0.1f, -1.5f); 
	// 绘制了一个四边形
	glColor4ub(0, 255, 0, 255); glVertex3d(-0.5f, 0.5f, -1.5f); 
	glColor4ub(255, 0, 0, 255); glVertex3d(+0.4f, 0.5f, -1.5f); 
	// 绘制了两个四边形

	glEnd(); 
}

void Draw()
{
	DrawQuadStrip();
	//glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	//glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_TRIANGLE_STRIP); // 表明要绘制图形：三角形

	//glEnd(); // 如果给 3 个点，绘制一个三角形，给6个点，绘制两个三角形, 逆时针方向
}