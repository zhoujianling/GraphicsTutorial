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
	glGenTextures(1, &texture); // ���� 1 ��������ַ
	glBindTexture(GL_TEXTURE_2D, texture); // 2d ������ 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ������С��ô�죬���Բ�ֵ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ���Բ�ֵ
	// ����ָ�����˷�ʽ�� �ڶ�������������Ϊ GL_REPEAT, UV ������ 1.0�� ���ظ���������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // UV���곬��1.0��ô�죬 ȥ�����߽磨1.0����ȡ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // UV���곬��1.0��ô�� 
	// ���ڴ����ͼƬ���ݿ������Դ���
	// �ڶ������� 0�� ��ָ mipmap �� level
	// border ����Ϊ 0
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0); // ���õ�ǰ����Ϊ0�����������Ƶ�ǰ����ĸ��
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmpPath)
{
	int nFileSize = 0;
	unsigned char *bmpFileData = LoadFile(bmpPath, nFileSize);
	if (bmpFileData == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // ���������� 0 �ź�ɫ������Ԫ
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
 * �����л���ָ�glBegin(xxxx)) �������ʾ�б�
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	GLuint displayList = glGenLists(1); // ���� OpenGL ����ʾ�б�
	glNewList(displayList, GL_COMPILE);
	foo();
	glEndList();
	return displayList;
}

// �������� size x size ������
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
	// �ڶ������� 1 ��ʾ�� shader�ļ������ݷ�Ϊ���ٸ��ַ�����һ������ĸ������� null
	// shader �ļ��п��Է�Ϊ����ַ���, �����Ļ������ĸ�������һ�����飬����ÿ���ַ����ĳ���
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);// ���Կ��������� shader�����������ʱ��������£�
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult); // ��ȡ������

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
	// ��������shader
	glLinkProgram(programId);
	glDetachShader(programId, vsShader);
	glDetachShader(programId, fsShader);
	GLint nResult = GL_TRUE;
	glGetProgramiv(programId, GL_LINK_STATUS, &nResult);
	if (nResult == GL_FALSE) // ����ʧ�ܣ��ͷ���Դ����ӡ��־
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

GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void* data)
{
	GLuint bufferObject;
	glGenBuffers(1, &bufferObject);
	glBindBuffer(bufferType, bufferObject);
	glBufferData(bufferType, size, data, usage);
	// ���õ�ǰ������ָ��
	glBindBuffer(bufferType, 0);
	return bufferObject;
}