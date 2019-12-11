#include "renderer.h"

Renderer::Renderer():
	scene_(nullptr)
{}

void Renderer::Render() {
	if (scene_ == nullptr) {
		std::cerr << "Info: No scene loaded." << std::endl;
		return;
	}
	glClearColor(0.1f, 0.3f, 0.5f, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	// 每一帧绘制之前要清除颜色缓冲区和深度缓冲区(初始化为1.0，即最远)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// Gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);
	if (option_.face_culling_) {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	glEnable(GL_MULTISAMPLE);

	if (rendering_element_option_table_[&scene_->GetGround()].visible_) {
		// ground.Draw(camera);
		DrawGround(scene_->GetGround());
	}

	if (option_.draw_wireframe_) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	for (auto& model : scene_->GetModels()) {
		if (! rendering_element_option_table_[&model].visible_) continue;
		// model.Draw(camera, option_);
		DrawModel(model);
	}
}

void Renderer::DrawModel(Model& model) {
	auto model_matrix_0 = model.ComputeModelMatrix();
	//glEnable(GL_STENCIL_TEST);
	// 蒙版默认初始化为 0
	//glClearStencil(0);
	//glStencilMask(0xFF);
	//glStencilFunc(GL_NOTEQUAL, 0x1, 0xFF); // 当和 0XFF 做 and运算的结果 NOTEQUAL 1时，通过蒙版测试
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // ???
	// glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	if (option_.draw_shadow_) {
		for (auto& mesh : model.GetConstMeshes()) {
			// mesh.DrawShadow(camera.GetViewMatrix(), camera.GetProjectionMatrix(), model_matrix_0);
		//glStencilMask(0x00);
		}
	}
	// 关闭蒙版写入
	//glStencilMask(0x00);

	//glDisable(GL_STENCIL_TEST);

	for (auto& mesh : model.GetMeshes()) {
		//glEnable(GL_BLEND);
		DrawMesh(mesh, model_matrix_0);
		//glDisable(GL_BLEND);
	}
	if (option_.show_bbox_) {
		//bbox_wire_.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), model_matrix_0);
		DrawWireFrame(model.GetBoxWires(), model_matrix_0);
	}
}

void Renderer::DrawMesh(zjl::TriMesh& mesh, glm::mat4 model_matrix) {
	glEnable(GL_DEPTH_TEST);
	//if (is_transparent_) {
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//}
	auto& camera = scene_->GetCamera();
	auto& shader = mesh.GetShader();
	auto& vertex_buffer_ = mesh.GetVertexBuffer();
	auto& element_buffer_ = mesh.GetElementBuffer();
	auto view_matrix = camera.GetViewMatrix();
	auto projection_matrix = camera.GetProjectionMatrix();
	vertex_buffer_.Bind();
	element_buffer_.Bind();

	auto ptr = glm::value_ptr((view_matrix));
	shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader.Bind(glm::value_ptr(model_matrix), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix);
	auto it_location = glGetUniformLocation(shader.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_.GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_.GetVerticesCount());
	//
	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
	glDisable(GL_BLEND);
}

void Renderer::DrawMeshShadow(zjl::TriMesh& mesh, glm::mat4 model_matrix) {
	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//vertex_buffer_.Bind();
	//element_buffer_.Bind();

	////auto ptr = glm::value_ptr((view_matrix));
	////shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	//shadow_shader_.Bind(glm::value_ptr(model_matrix), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	//auto it = glm::inverseTranspose(model_matrix);
	//auto it_location = glGetUniformLocation(shadow_shader_.GetProgramId(), "IT_ModelMatrix");
	//glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	////glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	//
	//glDrawElements(GL_TRIANGLES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);

	//vertex_buffer_.UnBind();
	//element_buffer_.UnBind();
}

void Renderer::DrawWireFrame(WireFrame& wire_frame, glm::mat4 model_matrix) {
	glEnable(GL_DEPTH_TEST);
	auto& camera = scene_->GetCamera();
	auto& shader = wire_frame.GetShader();
	auto& vertex_buffer_ = wire_frame.GetVertexBuffer();
	auto& element_buffer_ = wire_frame.GetElementBuffer();
	auto view_matrix = camera.GetViewMatrix();
	auto projection_matrix = camera.GetProjectionMatrix();
	vertex_buffer_.Bind();
	element_buffer_.Bind();

	auto ptr = glm::value_ptr((view_matrix));
	//shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader.Bind(glm::value_ptr(model_matrix), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix);
	auto it_location = glGetUniformLocation(shader.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_LINES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);

	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
}

void Renderer::DrawGround(Ground& ground) {
	glEnable(GL_DEPTH_TEST);
	auto& camera = scene_->GetCamera();
	auto& shader_ = ground.GetShader();
	auto& buffer_ = ground.GetBuffer();
	auto model_matrix_ = ground.GetModelMatrix();
	glm::mat4 view_matrix = camera.GetViewMatrix();
	glm::mat4 projection_matrix = camera.GetProjectionMatrix();
	glm::vec3 camera_position = camera.GetPosition();
	const float cp_x = camera_position.x;
	const float cp_y = camera_position.y;
	const float cp_z = camera_position.z;
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	auto ptr = glm::value_ptr((view_matrix));
	//shader_.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader_.SetVector4("U_CameraPosition", cp_x, cp_y, cp_z, 1.0);
	buffer_.Bind();
	shader_.Bind(glm::value_ptr(model_matrix_), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	int cell_num = 400; // todo ...
	for (int i = 0; i < cell_num * cell_num; i ++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
		//glDrawArrays(GL_QUADS, i * 4, 4);
	}
	buffer_.UnBind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}



void Renderer::SetScene(Scene& scene) {
	rendering_element_option_table_.clear();
	this->scene_ = &scene;
}
