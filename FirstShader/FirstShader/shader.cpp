#include "shader.h"
#include "utils.h"
#include "vertex.h"

void Shader::Init(const std::string &vs, const std::string &fs)
{

	int fileSize = 0;
	unsigned char *shaderCode = LoadFile(vs.c_str(), fileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
	if (vsShader == 0)
	{
		std::cerr << "fail to create vertex shader " << vs << std::endl;
		return;
	}
	delete shaderCode;
	shaderCode = LoadFile(fs.c_str(), fileSize);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
	if (fsShader == 0)
	{
		std::cerr << "fail to create fragment shader " << fs << std::endl;
		return;
	}
	delete shaderCode;
	program_id_ = CreateShaderProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	if (program_id_ != 0)
	{
		position_location_ = glGetAttribLocation(program_id_, "position");
		color_location_ = glGetAttribLocation(program_id_, "color");
		normal_location_ = glGetAttribLocation(program_id_, "normal");
		// texcoord_location_ = glGetAttribLocation(program_id_, "texcoord");
		model_matrix_location_ = glGetUniformLocation(program_id_, "ModelMatrix");
		view_matrix_location_ = glGetUniformLocation(program_id_, "ViewMatrix");
		projection_matrix_location_ = glGetUniformLocation(program_id_, "ProjectionMatrix");
		std::cerr << "succeed in binding slots"<< std::endl;
	} else
	{
		std::cerr << "fail to create shader program "<< std::endl;
	}
}

/**
 * 做 M V P 矩阵的绑定
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
	// glEnableVertexAttribArray(texcoord_location_);
	// glVertexAttribPointer(texcoord_location_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 8));;
	glEnableVertexAttribArray(normal_location_);
	glVertexAttribPointer(normal_location_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 12));;
}
