#pragma once

#include "ggl.h"
#include <unordered_map>

struct UniformTexture
{
	GLint location_; // 纹理变量的插槽

	GLuint texture_; // 纹理的唯一标识符

	UniformTexture(): location_(-1), texture_(0){}
};

/**
 * 表示 shader 文件中一个 uniform vec4 类型的变量
 */
struct UniformVector4f
{
	GLint location_; // 变量对应插槽

	float value_[4];

	UniformVector4f();

	UniformVector4f(float x, float y, float z, float w, GLint location);
};

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

	/** 键： shader 中的 vec4 类型的变量名 **/
	std::unordered_map<std::string, UniformVector4f*> vec4_map_;

	std::unordered_map<std::string, UniformTexture*> textures_map_;

public:
	Shader() = default;
	Shader(const Shader&);
	Shader& operator= (const Shader&);

	~Shader();

	int GetProgramId() const { return program_id_; }

	int GetPositionLocation() const { return position_location_; }

	int GetColorLocation() const { return color_location_; }

	int GetTexcoordLocation() const { return texcoord_location_; }

	int GetNormalLocation() const { return normal_location_; }
		
	void Init(const std::string& vs, const std::string& fs);

	void Bind(float *M, float *V, float *P);

	void SetVector4(const std::string & name, float x, float y, float z, float w);

	void SetTexture(const std::string & name, const std::string & texture_image_path);
};
