#pragma once
#include "ggl.h"
#include "ground.h"
#include "mesh.h"
#include "model.h"
#include "camera.h"
#include "light.h"
#include <vector>


class Scene {
private:
	Ground ground;
	Camera camera;

	std::vector<DirectionLight> lights_;
	std::vector<Model> models;

	bool w_pressing;
	bool s_pressing;
	bool a_pressing;
	bool d_pressing;


	float delta_time_;

	int tick_cnt_;

public:
	Scene();

	void SetViewPortSize(float width, float height);

	void Init();

	void UpdateScene();

	void Draw();

	void DrawModel( Model& model);

	void DrawMesh( zjl::TriMesh& mesh, glm::mat4 model_matrix);

	// 键盘按下事件
	void OnKeyDown(char code);

	// 键盘弹起事件
	void OnKeyUp(char code);

	void OnMouseMove(float delta_x, float delta_y);

	void LoadModel(const std::string& file_path);

	float GetDeltaTime() const { return this->delta_time_; }

	std::vector<Model>& GetModels() { return this->models; }

	Ground& GetGround() { return this->ground; }

	Camera& GetCamera() { return this->camera; }

};
