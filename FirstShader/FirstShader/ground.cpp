#include "ground.h"


using glm::mat4;
using glm::identity;
using glm::identity;

Ground::Ground():texture_color_name_("Res/Stone_tiles_floor_02_1K_Base_Color.png") {
}

void Ground::InitGeometry() {
	model_matrix_ = identity<mat4>();
	//model_matrix_ = glm::translate(identity<mat4>(), {0.0f, 0.0f, 0.0f});
	//PrintGLMMatrix(model_matrix_);
	buffer_.SetVertexCount(1600);
	for (int z = 0; z < 20; ++z) {
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; ++x) {
			int offset = (x + z * 20) * 4;
			float xStart = x * 10.0f - 100.0f;
			buffer_.SetPosition(offset + 0, xStart, -1.0f, zStart);
			buffer_.SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
			buffer_.SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
			buffer_.SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);

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
	//shader_.SetVector4("U_LightPosition", 0.0f, 1.0f, 1.0f, 1.0f);
	//shader_.SetVector4("U_LightAmbient", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader_.SetVector4("U_LightAmbientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
	//shader_.SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	//shader_.SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
	//shader_.SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	//shader_.SetVector4("U_LightSpecularMaterial", 1.0f, 1.0f, 1.0f, 1.0f);
	//shader_.SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	//shader_.SetVector4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);
	
	// std::cout << "###Ground###" << std::endl;
	if (! texture_color_name_.empty()) {
		shader_.SetTexture("U_Texture", texture_color_name_);
	}
}

void Ground::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
	glEnable(GL_DEPTH_TEST);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	buffer_.Bind();
	shader_.Bind(glm::value_ptr(model_matrix_), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	for (int i = 0; i < 400; i ++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
		//glDrawArrays(GL_QUADS, i * 4, 4);
	}
	buffer_.UnBind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
