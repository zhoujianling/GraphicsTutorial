#pragma once

#include "ggl.h"
#include "Include/glm/gtx/string_cast.hpp"
#include "iostream"

/** 加载文件内容到内存 **/
unsigned char* LoadFile(const char* file_path, int& file_size);

/** 解码 BMP 图片 **/
unsigned char* DecodeBMP(unsigned char* bmp_data, int& width, int& height);

/**
 * 创建二维纹理
 * @param type: 像素类型
 * @return 返回纹理对象的标识符
 **/
GLuint CreateTexture2D(unsigned char* pixelData, int with, int height, GLenum type);

GLuint CreateTexture2DFromBmp(const char *bmp_path);

GLuint CreateDisplayList(std::function<void()> foo);

/** 生成程序纹理 **/
GLuint CreateProcedureTexture(int size);

/** 统计渲染每一帧的时间，需要链接 winmm.lib **/
float GetFrameTime();


/**
 * 编译 shader
 * @param shader_type: 是 VertexShader 还是 FragmentShader
 * @param shader_code: d
 */
GLuint CompileShader(GLenum shader_type, const char *shader_code);

/**
 * 链接 vertexShader 和 fragmentShader
 * @param vs_shader: vertex shader
 * @param fs_shader: fragment shader
 */
GLuint CreateShaderProgram(GLuint vs_shader, GLuint fs_shader);

/**
 * 创建 Buffer Object
 * @param buffer_type 缓冲区类型
 * @param size 缓冲区的大小
 * @param usage static_draw 还是 dynamic_draw
 * @param data 具体的数据
 */
GLuint CreateBufferObject(GLenum buffer_type, GLsizeiptr size, GLenum usage, void *data = nullptr);

template<typename T>
void PrintGLMMatrix(T const& m, const std::string  prompt = "")
{
	// 列向量转行向量，方便观察
	const auto tm = glm::transpose(m);
	std::string str = glm::to_string(tm);
	std::string log = prompt;
	int prev_index = 0;
	for (int i = 0; i < str.length(); i ++)
	{
		if (str[i] == '(' && prev_index == 0) {
			log += std::string(str.begin() + prev_index, str.begin() + i + 1);
			log += "\n";
			prev_index = i + 1;
		} else if (i + 1 < str.length() && str[i] == ')' && str[i + 1] == ',')
		{
			log += std::string(str.begin() + prev_index, str.begin() + i + 2);
			log += "\n";
			prev_index = i + 2;
		}
	}
	log += std::string(str.begin() + prev_index,str.end());
	std::cout << log << std::endl;
}
