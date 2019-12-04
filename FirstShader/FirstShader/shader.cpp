#include "shader.h"
#include "utils.h"
#include "vertex.h"

UniformVector4f::UniformVector4f():location_(-1)
{
	memset(value_, 0, sizeof(float) * 4);
}

UniformVector4f::UniformVector4f(float x, float y, float z, float w, GLint location):
value_{x, y, z, w},
location_(location)
{
}

Shader::~Shader() {
	for (auto& kv : textures_map_) {
		delete kv.second;
	}
	for (auto& kv : vec4_map_) {
		delete kv.second;
	}
}

void Shader::Init(const std::string &vs, const std::string &fs)
{

	auto file_size = 0;
	const unsigned char *shader_code = LoadFile(vs.c_str(), file_size);
	const auto vs_shader = CompileShader(GL_VERTEX_SHADER, (char*)shader_code);
	if (vs_shader == 0)
	{
		std::cerr << "fail to create vertex shader " << vs << std::endl;
		return;
	}
	delete shader_code;
	shader_code = LoadFile(fs.c_str(), file_size);
	const auto fs_shader = CompileShader(GL_FRAGMENT_SHADER, (char*)shader_code);
	if (fs_shader == 0)
	{
		std::cerr << "fail to create fragment shader " << fs << std::endl;
		return;
	}
	delete shader_code;
	program_id_ = CreateShaderProgram(vs_shader, fs_shader);
	glDeleteShader(vs_shader);
	glDeleteShader(fs_shader);
	if (program_id_ != 0)
	{
		position_location_ = glGetAttribLocation(program_id_, "position");
		color_location_ = glGetAttribLocation(program_id_, "color");
		normal_location_ = glGetAttribLocation(program_id_, "normal");
		texcoord_location_ = glGetAttribLocation(program_id_, "texcoord");
		model_matrix_location_ = glGetUniformLocation(program_id_, "ModelMatrix");
		view_matrix_location_ = glGetUniformLocation(program_id_, "ViewMatrix");
		projection_matrix_location_ = glGetUniformLocation(program_id_, "ProjectionMatrix");
		std::cerr << "succeed in binding slots"<< std::endl;
	} else {
		std::cerr << "fail to create shader program "<< std::endl;
	}
}

/**
 * 做 M V P 矩阵的绑定，每次 Draw 模型之前都要 bind 一次
 * 此时与顶点数据是解耦的，但是知道不同位置的数据的语义，做语义绑定
 * 顶点数据取决于调用 glDrawElements() 之前 glBindBuffer() 里面传入的 vbo
 */
void Shader::Bind(float* M, float* V, float* P)
{
	glUseProgram(program_id_);
	glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, M);
	glUniformMatrix4fv(view_matrix_location_, 1, GL_FALSE, V);
	glUniformMatrix4fv(projection_matrix_location_, 1, GL_FALSE, P);

	glEnableVertexAttribArray(position_location_);
	glVertexAttribPointer(position_location_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);;
	glEnableVertexAttribArray(color_location_);
	glVertexAttribPointer(color_location_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 4));;
	glEnableVertexAttribArray(texcoord_location_);
	glVertexAttribPointer(texcoord_location_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 8));;
	glEnableVertexAttribArray(normal_location_);
	glVertexAttribPointer(normal_location_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 12));;

	int texture_index = 0;
	for (auto && kv : textures_map_)
	{
		glActiveTexture(GL_TEXTURE0 + texture_index); // 重置状态机，设置当前纹理编号
		glBindTexture(GL_TEXTURE_2D, kv.second->texture_);
		glUniform1i(kv.second->location_, texture_index++);
	}

	for (auto kv : vec4_map_)
	{
		glUniform4fv(kv.second->location_, 1, kv.second->value_);
	}
}

void Shader::SetVector4(const std::string& name, float x, float y, float z, float w)
{
	auto iter = vec4_map_.find(name);
	if (iter == vec4_map_.end()) {
		GLint location = glGetUniformLocation(program_id_, name.c_str());
		if (location != -1) {
			vec4_map_[name] = new UniformVector4f(x, y, z, w, location);
		} else {
			std::cerr << "Error: Fail to get location of " << name << " when setting vector" << std::endl;
		}
	} else {
		iter->second->value_[0] = x;
		iter->second->value_[1] = y;
		iter->second->value_[2] = z;
		iter->second->value_[3] = w;
	}
}

void Shader::SetTexture(const std::string& name, const std::string& texture_image_path)
{
	if (textures_map_.find(name) == textures_map_.end())  {
		GLint location = glGetUniformLocation(program_id_, name.c_str());
		if (location != -1) {
			UniformTexture * texture = new UniformTexture();
			texture->location_ = location;
			std::cerr << "reading imgae " << std::endl;
			texture->texture_ = CreateTexture2DFromImage(texture_image_path.c_str());
			textures_map_[name] = texture;
		} else {
			std::cerr << "Error: Fail to get location of " << name << " when setting texture" << std::endl;
		}
	} else {
		auto ptr = textures_map_[name];
		glDeleteTextures(1, &ptr->texture_);
		ptr->texture_ = CreateTexture2DFromImage(texture_image_path.c_str());
	}
}
