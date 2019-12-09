#pragma once
#include "ggl.h"
#include "ground.h"
#include "mesh.h"
#include "model.h"
#include "camera.h"
#include <vector>

struct RenderingOption {
	bool show_bbox_;

	RenderingOption():
		show_bbox_(true){}
};

class Scene {
private:
	RenderingOption option_;
	Ground ground;
	Camera camera;

	std::vector<Model> models;

	bool w_pressing;
	bool s_pressing;
	bool a_pressing;
	bool d_pressing;

	bool draw_wireframe_;

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

	RenderingOption& GetOption() { return this->option_; }

};
