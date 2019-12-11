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

	//models.push_back(Model());
	//LoadObj("Res/01Alocasia.obj", models[0].GetMeshes());
	//models.back().ScaleBy(0.5f).MoveBy({0.0f, -0.5f, 0.0f});


	lights_.push_back(DirectionLight(0));
	lights_.back().SetPosition(0.0f, 2.5f, 1.5f);

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

	// PrintGLMMatrix(projectionMatrix, "projection ");

	for (auto& model : models) {
		model.Init();
	}

}


void Scene::UpdateScene() {
	delta_time_ = GetFrameTime();
	//std::cout << "\rDelta time: " << delta_time;
	
	// update camera
	const auto move_speed = 0.8f;
	const auto forward_direction = glm::normalize(camera.ForwardDirection());
	const auto right_hand_direction = glm::normalize(camera.RightHandDirection());
	const auto scale = move_speed * delta_time_;

	auto delta = glm::vec3(0.0f, 0.0f, 0.0f);

	if (a_pressing) {
		delta = right_hand_direction * delta_time_* move_speed * -1.0f;
	}
	if (d_pressing) {
		delta = right_hand_direction * delta_time_* move_speed;
	}
	if (w_pressing) {
		delta = forward_direction * delta_time_* move_speed;
	}
	if (s_pressing) {
		delta = forward_direction * delta_time_* move_speed * -1.0f;
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
		// option_.draw_wireframe_ = !option_.draw_wireframe_;
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

void Scene::LoadModel(const std::string& file_path) {
	models.push_back(Model());
	bool success = LoadObj(file_path, models.back());
	if (!success) {
		models.pop_back();
		return;
	}
	models.back().Init();
}
