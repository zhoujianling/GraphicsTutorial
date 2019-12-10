#pragma once
#include "ggl.h"
#include "ground.h"
#include "mesh.h"
#include "model.h"
#include "camera.h"
#include <vector>

struct RenderingOption {
	bool show_bbox_;
	bool draw_wireframe_;
	bool draw_shadow_;

	bool face_culling_;

	RenderingOption():
		show_bbox_(true),
		draw_wireframe_(false),
		draw_shadow_(true),
		face_culling_(true)
	{}
};

struct RenderingElementOption {
	bool visible_;

	RenderingElementOption() :
		visible_(true)
	{}
};

class Scene {
private:
	RenderingOption option_;
	Ground ground;
	Camera camera;

	std::vector<Model> models;
	std::unordered_map<const RenderingElement*, RenderingElementOption> rendering_element_option_table_;

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

	// 键盘按下事件
	void OnKeyDown(char code);

	// 键盘弹起事件
	void OnKeyUp(char code);

	void OnMouseMove(float delta_x, float delta_y);

	void LoadModel(const std::string& file_path);

	float GetDeltaTime() const { return this->delta_time_; }

	RenderingOption& GetOption() { return this->option_; }

	RenderingElementOption& GetElementOption(const RenderingElement* element) { return this->rendering_element_option_table_[element]; }

	std::vector<Model>& GetModels() { return this->models; }

	const Ground& GetGround() { return this->ground; }
};
