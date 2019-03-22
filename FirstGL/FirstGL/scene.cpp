#include "scene.h"
#include "utils.h"
#include "skybox.h"
#include "model.h"
#include "ground.h"
#include "light.h"
#include "camera.h"
#include "particle.h"
#include <iostream>

DirectionLight light(GL_LIGHT0);
PointLight light1(GL_LIGHT1);
PointLight light2(GL_LIGHT2);
Ground ground;
SkyBox skyBox;
Model model;
Camera camera;
//Particle particle;

/**
 * 屏幕正中心是世界坐标系原点
 * z 轴指向屏幕外面, 所以 z 坐标要设负值
 */
void Init()
{
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	//std::cout << "Render: " << glGetString(GL_RENDER) << std::endl;
	// OpenGl 存在当前矩阵的概念，通过 glMatrixMode 设置当前矩阵的 模式
	glMatrixMode(GL_PROJECTION);
	// ?, 画布的宽高比， 最近可以看到的距离，最远可以看到的距离 
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.f);
	glMatrixMode(GL_MODELVIEW); // 切换当前矩阵到模型视口矩阵
	glLoadIdentity();
	skyBox.Init("Res/", &camera);
	//model.Init("Res/Box.obj");
	model.Init("Res/Dog.ply");
	ground.Init();

	light.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light.SetPosition(0.0f, 1.0f, 0.0f);
	light1.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light1.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	light1.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light1.SetPosition(0.0f, 0.0f, 0.0f); // 点光源放到原点
	light1.SetConstantAttenuation(0.1f);
	light1.SetLinearAttenuation(0.2f);
	// 第二个点光源
	light2.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light2.SetDiffuseColor(0.1f, 0.4f, 0.7f, 1.0f);
	light2.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	light2.SetPosition(0.0f, 0.0f, -20.0f); // 
	light2.SetConstantAttenuation(0.5f);
	light2.SetLinearAttenuation(0.2f);
	model.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	model.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
	model.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);

}



void Draw()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	// 每一帧绘制之前要清除颜色缓冲区和深度缓冲区(初始化为1.0，即最远)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float frameTime = GetFrameTime();
	camera.Update(frameTime);

	//light.Enable();
	light1.Enable();
	light1.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);
	light2.Enable();
	light2.Update(camera.GetPosition().v1, camera.GetPosition().v2, camera.GetPosition().v3);

	skyBox.Draw();
	ground.Draw();
	//glEnable(GL_DEPTH_TEST); // 保证近的物体会挡住远的物体
	model.Draw();
	//particle.Draw();
	// DrawModel();
}

void OnKeyDown(char code)
{
	switch (code)
	{
	case 'A':
		camera.SetMovingLeft(true);
		break;
	case 'S':
		camera.SetMovingBackward(true);
		break;
	case 'D':
		camera.SetMovingRight(true);
		break;
	case 'W':
		camera.SetMovingForward(true);
		break;
	}
}

void OnKeyUp(char code)
{
	switch (code)
	{
	case 'A':
		camera.SetMovingLeft(false);
		break;
	case 'S':
		camera.SetMovingBackward(false);
		break;
	case 'D':
		camera.SetMovingRight(false);
		break;
	case 'W':
		camera.SetMovingForward(false);
		break;
	}
}

void OnMouseMove(float deltaX, float deltaY)
{
	// 在 x 轴滑动，相机沿 y轴转动，位移值近似逼近 yaw 的角度
	float angleRotateByYAxis = deltaX / 1000.0f; 
	// 在 y 轴滑动，相机沿 x轴转动，位移值近似逼近 pitch 的角度
	float angleRotateByXAxis = deltaY / 1000.0f; 
	camera.Yaw(- angleRotateByYAxis);
	camera.Pitch(- angleRotateByXAxis);
}
