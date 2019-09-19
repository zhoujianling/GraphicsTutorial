#include "utils.h"
#include "io.h"
#include "iostream"


unsigned char* DecodeBMP(unsigned char* bmp_data, int& width, int& height)
{
	if (0x4D42 == *reinterpret_cast<unsigned short*>(bmp_data))
	{
		const auto pixel_data_offset = *reinterpret_cast<int*>(bmp_data + 10);
		width = *reinterpret_cast<int*>(bmp_data + 18);
		height = *reinterpret_cast<int*>(bmp_data + 22);
		const auto bmp_img_data = bmp_data + pixel_data_offset;
		// BGR -> RGB
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = bmp_img_data[i];
			bmp_img_data[i] = bmp_img_data[i + 2];
			bmp_img_data[i + 2] = temp;
		}
		return bmp_img_data;
	}
	return nullptr;
}

GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	glGenTextures(1, &texture); // 申请 1 个纹理地址
	glBindTexture(GL_TEXTURE_2D, texture); // 2d 纹理， 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 纹理过小怎么办，线性插值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线性插值
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // UV坐标超过1.0怎么办， 去纹理边界（1.0）处取
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // UV坐标超过1.0怎么办 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // UV坐标超过1.0怎么办，重复搬运 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // UV坐标超过1.0怎么办 
	// 将内存里的图片数据拷贝到显存里
	// 第二个参数 0， 是指 mipmap 的 level
	// border 必须为 0
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0); // 设置当前纹理为0号纹理，类似当前矩阵的概念？
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmp_path)
{
	int n_file_size = 0;
	const auto bmp_file_data = LoadFile(bmp_path, n_file_size);
	if (bmp_file_data == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // 出错，返回 0 号黑色纹理单元
	}
	auto width = 0, height = 0;
	unsigned char *bmp_image_data = nullptr;
	LoadRGBImage(bmp_path, bmp_image_data, width, height);
	//= DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmp_file_data;
		return 0;
	}

	const GLuint texture_id = CreateTexture2D(bmp_image_data, width, height, GL_RGB);
	//	delete bmpFileData;
	delete bmp_image_data;
	return texture_id;
}

/**
 * 将所有绘制指令（glBegin(xxxx)) 打包进显示列表
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	const GLuint display_list = glGenLists(1); // 声明 OpenGL 的显示列表
	glNewList(display_list, GL_COMPILE);
	foo();
	glEndList();
	return display_list;
}

// 代码生成 size x size 的纹理
GLuint CreateProcedureTexture(int size)
{
	unsigned char *image_data = new unsigned char[size * size * 4];
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			int i = (x + y * size) * 4;
			image_data[i + 0] = 255;
			image_data[i + 1] = 255;
			image_data[i + 2] = 255;
			image_data[i + 3] = 255;
		}
	}
	GLuint texture = CreateTexture2D(image_data, size, size, GL_RGBA);
	delete[] image_data;
	return texture;
}

float GetFrameTime()
{
	static unsigned long latest_time = 0;
	static unsigned long time_since_boot = 0;
	time_since_boot = timeGetTime();
	const unsigned long frame_time = latest_time == 0 ? 0 : time_since_boot - latest_time;
	latest_time = time_since_boot;
	return static_cast<float>(frame_time) / 1000.0f;
}

GLuint CompileShader(const GLenum shader_type, const char* shader_code)
{
	GLuint shader = glCreateShader(shader_type);
	// 第二个参数 1 表示将 shader文件的内容分为多少个字符串，一行则第四个参数传 null
	// shader 文件中可以分为多个字符串, 那样的话，第四个参数传一个数组，告诉每个字符串的长度
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);// 让显卡驱动编译 shader（程序的运行时来做这件事）
	GLint compile_result = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result); // 获取编译结果

	if (compile_result == GL_FALSE)
	{
		char sz_log[1024] = { 0 };
		GLsizei log_length = 0;
		glGetShaderInfoLog(shader, 1024, &log_length, sz_log);
		std::cerr << "Fail to compile shader: " << shader_code << " , log: " << sz_log << std::endl;
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

GLuint CreateShaderProgram(const GLuint vs_shader, const GLuint fs_shader)
{
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vs_shader);
	glAttachShader(program_id, fs_shader);
	// 链接两个shader
	glLinkProgram(program_id);
	glDetachShader(program_id, vs_shader);
	glDetachShader(program_id, fs_shader);
	GLint n_result = GL_TRUE;
	glGetProgramiv(program_id, GL_LINK_STATUS, &n_result);
	if (n_result == GL_FALSE) // 链接失败，释放资源，打印日志
	{
		char sz_log[1024] = { 0 };
		GLsizei log_length = 0;
		glGetShaderInfoLog(program_id, 1024, &log_length, sz_log);
		std::cerr << "Fail to link program, log: " << sz_log << std::endl;
		glDeleteProgram(program_id);
		program_id = 0;
	}
	return program_id;
}

GLuint CreateBufferObject(const GLenum buffer_type, GLsizeiptr size, GLenum usage, void* data)
{
	GLuint buffer_object;
	glGenBuffers(1, &buffer_object);
	glBindBuffer(buffer_type, buffer_object);
	glBufferData(buffer_type, size, data, usage);
	// 重置当前缓冲区指向
	glBindBuffer(buffer_type, 0);
	return buffer_object;
}
