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
	d_pressing(false),
	draw_wireframe_(false)
{
	tick_cnt_ = 0;
}

void Scene::SetViewPortSize(float width, float height) {
	glViewport(0, 0, width, height);
	camera.Init(width / height);
}

/**
 * 屏幕正中心是世界坐标系原点
 * z 轴指向屏幕外面, 所以 z 坐标要设负值
 */
void Scene::Init() {
	ground.InitGeometry();
	ground.InitShader();
	camera.Translate({ 0.0f, -0.6f, 3.0f });
	//meshes.push_back(TriMesh());
	//meshes[0].Init("Res/Dog.Normal.ply");
	// LoadObj("Res/01Alocasia.obj", meshes);

	models.push_back(Model());
	LoadObj("Res/01Alocasia.obj", models[0].GetMeshes());
	models.back().ScaleBy(0.5f).MoveBy({0.0f, -0.5f, 0.0f});


	//for (auto& mesh : meshes) {
		// shadows.emplace_back(mesh.GetVertexBuffer(), mesh.GetElementBuffer());
		//shadows.push_back(Shadow(mesh.GetVertexBuffer(), mesh.GetElementBuffer()));
	//}

	//meshes.push_back(TriMesh());
	//wire_frame.Init("Res/Dog.Normal.ply");

	ElementBuffer element_buffer_temp;
	VertexBuffer vertex_buffer_temp;
	ElementBuffer element_buffer_edge;

	//meshes.back().Init("Res/wall.obj");
	//meshes.back().MoveBy({ 0.0f, 0.0f, -0.9f });
	//meshes.back().SetTransparent(true);

	//ConvertFaces2Edges(element_buffer_temp, element_buffer_edge);
	//wire_frame.Init(vertex_buffer_temp, element_buffer_edge);
	// meshes[0].GetBoundingBox().ToWireframe(vertex_buffer_temp, element_buffer_temp);
	// wire_frame.Init(vertex_buffer_temp, element_buffer_temp);

	// mesh.SetTexture("Res/Texture.bmp");

	// PrintGLMMatrix(projectionMatrix, "projection ");

	for (auto& model : models) {
		model.Init();
	}

}


void Scene::UpdateScene() {
	const auto delta_time = GetFrameTime();
	std::cout << "\rDelta time: " << delta_time;
	
	// update camera
	const auto move_speed = 2.0f;
	const auto forward_direction = glm::normalize(camera.ForwardDirection());
	const auto right_hand_direction = glm::normalize(camera.RightHandDirection());
	const auto scale = move_speed * delta_time;

	auto delta = glm::vec3(0.0f, 0.0f, 0.0f);

	if (a_pressing) {
		delta = right_hand_direction * delta_time * move_speed * -1.0f;
	}
	if (d_pressing) {
		delta = right_hand_direction * delta_time * move_speed;
	}
	if (w_pressing) {
		delta = forward_direction * delta_time * move_speed;
	}
	if (s_pressing) {
		delta = forward_direction * delta_time * move_speed * -1.0f;
	}
	camera.Translate(delta);

	if (tick_cnt_ > 100) {
		float s1 = 0.6 * sin((tick_cnt_ - 200) * 1.0 / 120) ;
		float s2 = 0.6 * sin((tick_cnt_ - 201) * 1.0 / 120) ;
		if (!models.empty()) {
			models[0].MoveBy({0.0f, -(s1 - s2), 0.0f});
		}
	}
	tick_cnt_ += 1;
}

void Scene::Draw() {
	glClearColor(0.1f, 0.3f, 0.5f, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	// 每一帧绘制之前要清除颜色缓冲区和深度缓冲区(初始化为1.0，即最远)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// Gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	ground.Draw(camera);

	if (draw_wireframe_) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	for (auto& model : models) {
		model.Draw(camera, option_);
	}

}

void Scene::OnKeyDown(char code) {
	switch (code) {
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

void Scene::OnKeyUp(char code) {
	switch (code) {
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
	case 'M':
		draw_wireframe_ = !draw_wireframe_;
		break;
	}
}

void Scene::OnMouseMove(const float delta_x, const float delta_y) {
	// 在 x 轴滑动，相机沿 y轴转动，位移值近似逼近 yaw 的角度
	const auto angle_rotate_by_y_axis = delta_x / 1000.0f; 
	// 在 y 轴滑动，相机沿 x轴转动，位移值近似逼近 pitch 的角度
	const auto angle_rotate_by_x_axis = delta_y / 1000.0f; 
	camera.Yaw(- angle_rotate_by_y_axis );
	camera.Pitch(- angle_rotate_by_x_axis);
}
