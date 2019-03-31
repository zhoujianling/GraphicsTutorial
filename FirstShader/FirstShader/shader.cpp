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
	programId = CreateShaderProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	if (programId != 0)
	{
		positionLocation = glGetAttribLocation(programId, "position");
		colorLocation = glGetAttribLocation(programId, "color");
		normalLocation = glGetAttribLocation(programId, "normal");
		// texcoordLocation = glGetAttribLocation(programId, "texcoord");
		modelMatrixLocation = glGetUniformLocation(programId, "ModelMatrix");
		viewMatrixLocation = glGetUniformLocation(programId, "ViewMatrix");
		projectionMatrixLocation = glGetUniformLocation(programId, "ProjectionMatrix");
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
	glUseProgram(programId);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, M);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, V);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, P);

	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);;
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 4));;
	// glEnableVertexAttribArray(texcoordLocation);
	// glVertexAttribPointer(texcoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 8));;
	glEnableVertexAttribArray(normalLocation);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 12));;
}
