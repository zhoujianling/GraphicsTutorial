#include "scene.h"
#include "utils.h"
#include "io.h"
#include <iostream>
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

using namespace zjl;


Scene::Scene():
	w_pressing(false),
	s_pressing(false),
	a_pressing(false),
	d_pressing(false)
{
}

void Scene::SetViewPortSize(float width, float height)
{
	glViewport(0, 0, width, height);
	camera.Init(width / height);
	// projection_matrix = glm::perspective(60.0f / 180.0f * PI, width / height, 0.1f, 1000.0f);
}

/**
 * 屏幕正中心是世界坐标系原点
 * z 轴指向屏幕外面, 所以 z 坐标要设负值
 */
void Scene::Init()
{
	ground.Init();
	//meshes.push_back(TriMesh());
	//meshes[0].Init("Res/Dog.Normal.ply");
	//meshes[0].MoveBy({ 0.0f, 0.0f, -2.9f }).RotateBy({ 0.0f, 1.0f, 0.0f }, PI / 2.0);
	LoadObj("Res/01Alocasia.obj", meshes);

	meshes.push_back(TriMesh());
	//wire_frame.Init("Res/Dog.Normal.ply");

	ElementBuffer element_buffer_temp;
	VertexBuffer vertex_buffer_temp;
	ElementBuffer element_buffer_edge;

	meshes.back().Init("Res/wall.obj");
	meshes.back().MoveBy({ 0.0f, 0.0f, -0.9f });
	meshes.back().SetTransparent(true);

	//ConvertFaces2Edges(element_buffer_temp, element_buffer_edge);
	//wire_frame.Init(vertex_buffer_temp, element_buffer_edge);
	// meshes[0].GetBoundingBox().ToWireframe(vertex_buffer_temp, element_buffer_temp);
	// wire_frame.Init(vertex_buffer_temp, element_buffer_temp);

	// mesh.SetTexture("Res/Texture.bmp");

	// PrintGLMMatrix(projectionMatrix, "projection ");

	for (auto& mesh : meshes) {
		mesh.InitShader();
	}

}


void Scene::UpdateScene()
{
	const auto delta_time = GetFrameTime();
	std::cout << "\rDelta time: " << delta_time;
	
	// update camera
	const auto move_speed = 2.0f;
	const auto forward_direction = glm::normalize(camera.ForwardDirection());
	const auto right_hand_direction = glm::normalize(camera.RightHandDirection());
	const auto scale = move_speed * delta_time;

	auto delta = glm::vec3(0.0f, 0.0f, 0.0f);

	if (a_pressing)
	{
		delta = right_hand_direction * delta_time * move_speed * -1.0f;
	}
	if (d_pressing)
	{
		delta = right_hand_direction * delta_time * move_speed;
	}
	if (w_pressing)
	{
		delta = forward_direction * delta_time * move_speed;
	}
	if (s_pressing)
	{
		delta = forward_direction * delta_time * move_speed * -1.0f;
	}
	camera.Translate(delta);
}

void Scene::Draw()
{
	glClearColor(0.1f, 0.3f, 0.5f, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	// 每一帧绘制之前要清除颜色缓冲区和深度缓冲区(初始化为1.0，即最远)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);

	ground.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	for (auto& mesh : meshes) {
		mesh.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
	// wire_frame.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());

}

void Scene::OnKeyDown(char code)
{
	switch (code)
	{
	case 'A':
		a_pressing = true;
		break;
	case 'S':
		s_pressing = true;
		break;
	case 'D':
		d_pressing = true;
		break;
	case 'W':
		w_pressing = true;
		break;
	}
}

void Scene::OnKeyUp(char code)
{
	switch (code)
	{
	case 'A':
		a_pressing = false;
		break;
	case 'S':
		s_pressing = false;
		break;
	case 'D':
		d_pressing = false;
		break;
	case 'W':
		w_pressing = false;
		break;
	}
}

void Scene::OnMouseMove(const float delta_x, const float delta_y)
{
	// 在 x 轴滑动，相机沿 y轴转动，位移值近似逼近 yaw 的角度
	const auto angle_rotate_by_y_axis = delta_x / 1000.0f; 
	// 在 y 轴滑动，相机沿 x轴转动，位移值近似逼近 pitch 的角度
	const auto angle_rotate_by_x_axis = delta_y / 1000.0f; 
	camera.Yaw(- angle_rotate_by_y_axis );
	camera.Pitch(- angle_rotate_by_x_axis);
}
