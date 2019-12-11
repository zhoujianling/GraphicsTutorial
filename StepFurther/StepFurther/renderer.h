#pragma once
#include "scene.h"

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

class Renderer {
private:
	RenderingOption option_;

	Scene* scene_;
	std::unordered_map<const RenderingElement*, RenderingElementOption> rendering_element_option_table_;

	void DrawGround(Ground& ground);

	void DrawModel(Model& model);

	void DrawMesh(zjl::TriMesh& mesh, glm::mat4 model_matrix);

	void DrawMeshShadow(zjl::TriMesh& mesh, glm::mat4 model_matrix);

	void DrawWireFrame(WireFrame& wire_frame, glm::mat4 model_matrix);

public:
	Renderer();

	void Render();

	RenderingOption& GetOption() { return this->option_; }

	RenderingElementOption& GetElementOption(const RenderingElement* element) { return this->rendering_element_option_table_[element]; }

	void SetScene(Scene& scene);
};

