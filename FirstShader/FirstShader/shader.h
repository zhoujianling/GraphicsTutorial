#pragma once

#include "ggl.h"

/**
 * 对于一个要画的物体，我们通常要写它的 VertexShader 和 FragmentShader
 * 代码的读取、编译、链接，可以进一步封装
 */
class Shader
{
private:
	GLuint program_id_;

	GLint position_location_;

	GLint color_location_;

	GLint texcoord_location_;

	GLint normal_location_;

	GLint model_matrix_location_;
	GLint view_matrix_location_;
	GLint projection_matrix_location_;

public:
	int GetPositionLocation() const { return position_location_; }

	int GetColorLocation() const { return color_location_; }

	int GetTexcoordLocation() const { return texcoord_location_; }

	int GetNormalLocation() const { return normal_location_; }
		
	void Init(const std::string& vs, const std::string& fs);

	void Bind(float *M, float *V, float *P);
};
