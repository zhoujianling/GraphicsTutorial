#include "ground.h"
#include "camera.h"

using glm::mat4;
using glm::identity;
using glm::identity;

Ground::Ground():
	cell_size(3.0f),
	cell_num(30),
	texture_color_name_("Res/Stone_tiles_floor_02_1K_Base_Color.png"), 
	texture_normal_name_("Res/Stone_tiles_floor_02_1K_Normal.png")
{}

void Ground::InitGeometry() {
	model_matrix_ = identity<mat4>();
	//model_matrix_ = glm::translate(identity<mat4>(), {0.0f, 0.0f, 0.0f});
	//PrintGLMMatrix(model_matrix_);
	buffer_.SetVertexCount(cell_num * cell_num * 4);
	for (int z = 0; z < cell_num; ++z) {
		float zStart = cell_size * cell_num / 2 - z * cell_size;
		for (int x = 0; x < cell_num; ++x) {
			int offset = (x + z * cell_num) * 4;
			float xStart = x * cell_size - cell_num / 2 * cell_size;
			buffer_.SetPosition(offset + 0, xStart,				-1.0f, zStart);
			buffer_.SetPosition(offset + 1, xStart + cell_size, -1.0f, zStart);
			buffer_.SetPosition(offset + 2, xStart,				-1.0f, zStart - cell_size);
			buffer_.SetPosition(offset + 3, xStart + cell_size, -1.0f, zStart - cell_size);

			buffer_.SetNormal(offset + 0, 0.0f, 1.0f, 0.0f);
			buffer_.SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
			buffer_.SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
			buffer_.SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);

			float color = ((z % 2) ^ (x % 2)) ? 0.1f : 0.8f;
			buffer_.SetColor(offset + 0, color, color, color);
			buffer_.SetColor(offset + 1, color, color, color);
			buffer_.SetColor(offset + 2, color, color, color);
			buffer_.SetColor(offset + 3, color, color, color);

			buffer_.SetTexcoord(offset + 0, 0.0f, 0.0f);
			buffer_.SetTexcoord(offset + 1, 1.0f, 0.0f);
			buffer_.SetTexcoord(offset + 2, 0.0f, 1.0f);
			buffer_.SetTexcoord(offset + 3, 1.0f, 1.0f);
		}
	}
//	std::cerr << "sizeof(vertex):" << sizeof(Vertex) << " vertices number: " << vertex_buffer_.GetVerticesCount() << std::endl;
	//vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_buffer_.GetVerticesCount(), GL_STATIC_DRAW, vertex_buffer_.GetVertex());
}

void Ground::InitShader() {
	shader_.Init("ground.vert", "ground.frag");
	shader_.SetVector4("U_LightPosition", 0.0f, 2.5f, 1.5f, 1.0f);
	shader_.SetVector4("U_LightAmbient", 1.0f, 1.0f, 1.0f, 1.0f);
	shader_.SetVector4("U_LightAmbientMaterial", 0.10f, 0.10f, 0.10f, 1.0f);
	shader_.SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader_.SetVector4("U_LightDiffuseMaterial", 0.70f, 0.70f, 0.70f, 1.0f);
	shader_.SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	shader_.SetVector4("U_LightSpecularMaterial", 0.2f, 0.2f, 0.2f, 1.0f);
	shader_.SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	shader_.SetVector4("U_LightOpt", 4.0f, 0.0f, 0.0f, 1.0f);
	
	// std::cout << "###Ground###" << std::endl;
	if (! texture_color_name_.empty()) {
		shader_.SetTexture("U_Texture", texture_color_name_);
		if (!texture_normal_name_.empty()) {
			shader_.SetTexture("U_TextureNormal", texture_normal_name_);
		}
	}
}

void Ground::Draw(const Camera& camera) {
	glEnable(GL_DEPTH_TEST);
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
	for (int i = 0; i < cell_num * cell_num; i ++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
		//glDrawArrays(GL_QUADS, i * 4, 4);
	}
	buffer_.UnBind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
