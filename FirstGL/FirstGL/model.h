#pragma once

#include "ggl.h"

/**
 * 一个网格顶点
 */
struct Vertex
{
	/** x,y,z坐标 **/
	GLfloat position[3];

	/** UV 纹理坐标 **/
	GLfloat texcoord[2];

	/** 法线信息 **/
	GLfloat normal[3];
};

class Model
{
private:
	std::vector<Vertex> vertices;

	std::vector<int> faceIndices;

	void LoadObj(const char *filePath);

	void LoadPly(const char *filePath);
public:
	Model();

	void Init(const char *modelPath);

	void Draw();
};
