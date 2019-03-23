#include "utils.h"
#include "io.h"
#include "iostream"


unsigned char* DecodeBMP(unsigned char* bmpData, int& width, int& height)
{
	if (0x4D42 == *reinterpret_cast<unsigned short*>(bmpData))
	{
		auto pixelDataOffset = *reinterpret_cast<int*>(bmpData + 10);
		width = *reinterpret_cast<int*>(bmpData + 18);
		height = *reinterpret_cast<int*>(bmpData + 22);
		auto bmpImgData = bmpData + pixelDataOffset;
		// BGR -> RGB
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = bmpImgData[i];
			bmpImgData[i] = bmpImgData[i + 2];
			bmpImgData[i + 2] = temp;
		}
		return bmpImgData;
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
	// 以下指定过滤方式， 第二个参数还可以为 GL_REPEAT, UV 若大于 1.0， 则重复搬运纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // UV坐标超过1.0怎么办， 去纹理边界（1.0）处取
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // UV坐标超过1.0怎么办 
	// 将内存里的图片数据拷贝到显存里
	// 第二个参数 0， 是指 mipmap 的 level
	// border 必须为 0
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0); // 设置当前纹理为0号纹理，类似当前矩阵的概念？
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmpPath)
{
	int nFileSize = 0;
	unsigned char *bmpFileData = LoadFile(bmpPath, nFileSize);
	if (bmpFileData == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // 出错，返回 0 号黑色纹理单元
	}
	int width = 0, height = 0;
	unsigned char *bmpImageData = nullptr;
	LoadRGBImage(bmpPath, bmpImageData, width, height);
	//= DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmpFileData;
		return 0;
	}

	GLuint textureID = CreateTexture2D(bmpImageData, width, height, GL_RGB);
	//	delete bmpFileData;
	delete bmpImageData;
	return textureID;
}

/**
 * 将所有绘制指令（glBegin(xxxx)) 打包进显示列表
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	GLuint displayList = glGenLists(1); // 声明 OpenGL 的显示列表
	glNewList(displayList, GL_COMPILE);
	foo();
	glEndList();
	return displayList;
}

// 代码生成 size x size 的纹理
GLuint CreateProcedureTexture(int size)
{
	unsigned char *imageData = new unsigned char[size * size * 4];
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			int i = (x + y * size) * 4;
			imageData[i + 0] = 255;
			imageData[i + 1] = 255;
			imageData[i + 2] = 255;
			imageData[i + 3] = 255;
		}
	}
	GLuint texture = CreateTexture2D(imageData, size, size, GL_RGBA);
	delete imageData;
	return texture;
}

float GetFrameTime()
{
	static unsigned long latestTime = 0;
	static unsigned long timeSinceBoot = 0;
	timeSinceBoot = timeGetTime();
	unsigned long frameTime = latestTime == 0 ? 0 : timeSinceBoot - latestTime;
	latestTime = timeSinceBoot;
	return static_cast<float>(frameTime) / 1000.0f;
}

GLuint CompileShader(GLenum shaderType, const char* shaderCode)
{
	GLuint shader = glCreateShader(shaderType);
	// 第二个参数 1 表示将 shader文件的内容分为多少个字符串，一行则第四个参数传 null
	// shader 文件中可以分为多个字符串, 那样的话，第四个参数传一个数组，告诉每个字符串的长度
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);// 让显卡驱动编译 shader（程序的运行时来做这件事）
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult); // 获取编译结果

	if (compileResult == GL_FALSE)
	{
		char szLog[1024] = { 0 };
		GLsizei logLength = 0;
		glGetShaderInfoLog(shader, 1024, &logLength, szLog);
		std::cerr << "Fail to compile shader: " << shaderCode << " , log: " << szLog << std::endl;
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

GLuint CreateShaderProgram(GLuint vsShader, GLuint fsShader)
{
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vsShader);
	glAttachShader(programId, fsShader);
	// 链接两个shader
	glLinkProgram(programId);
	glDetachShader(programId, vsShader);
	glDetachShader(programId, fsShader);
	GLint nResult = GL_TRUE;
	glGetProgramiv(programId, GL_LINK_STATUS, &nResult);
	if (nResult == GL_FALSE) // 链接失败，释放资源，打印日志
	{
		char szLog[1024] = { 0 };
		GLsizei logLength = 0;
		glGetShaderInfoLog(programId, 1024, &logLength, szLog);
		std::cerr << "Fail to link program, log: " << szLog << std::endl;
		glDeleteProgram(programId);
		programId = 0;
	}
	return programId;
}