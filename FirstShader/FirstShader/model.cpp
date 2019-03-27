#include "model.h"
#include "utils.h"
// #include "happly.h"
#include "io.h"
#include "iostream"

void VertexBuffer::SetPosition(int index, float x, float y, float z, float w)
{
	this->mVertices[index].position[0] = x;
	this->mVertices[index].position[1] = y;
	this->mVertices[index].position[2] = z;
	this->mVertices[index].position[3] = w;
}

void VertexBuffer::SetColor(int index, float r, float g, float b, float a)
{
	this->mVertices[index].color[0] = r;
	this->mVertices[index].color[1] = g;
	this->mVertices[index].color[2] = b;
	this->mVertices[index].color[3] = a;
}

void VertexBuffer::SetNormal(int index, float x, float y, float z, float a)
{
	this->mVertices[index].normal[0] = x;
	this->mVertices[index].normal[1] = y;
	this->mVertices[index].normal[2] = z;
	this->mVertices[index].normal[3] = 1.0;
}

void VertexBuffer::SetTexcoord(int index, float u, float v)
{
	this->mVertices[index].texcoord[0] = u;
	this->mVertices[index].texcoord[1] = v;
}

Model::Model()
{
	
}

// void Model::Init(const char* modelPath)
// {
// 	int nFileSize = 0;
// 	int len = strlen(modelPath);
// 	if (len < 4) return;
// 	const auto &suffix = std::string(modelPath + len - 3);
// 	if (suffix == "obj")
// 	{
// 		LoadObj(modelPath, this);
// 	} else if (suffix == "ply")
// 	{
// 		LoadPly(modelPath, this);
// 	} else
// 	{
// 		std::cerr << "Unsupported types:" << modelPath << std::endl;
// 		return;
// 	}
// }
//
// void Model::Draw()
// {
// 	glEnable(GL_LIGHTING);
// 	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbientMaterial);
// 	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
// 	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecularMaterial);
// 	glPushMatrix();
// 	// 要后移一点，不然容易跟相机重合，看不到模型
// 	glTranslatef(0.0f, 0.0f, -3.0f);
// 	glRotated(90.0, 0, 1.0, 0);
// 	glBegin(GL_TRIANGLES);
// 	// 假设绘制的是三角化的网格模型
// 	for (auto i = 0; i < faceIndices.size(); i ++)
// 	{
// 		Vertex vertex = vertices[faceIndices[i]];
// 		//glTexCoord2fv(vertex.texcoord);
// 		//glNormal3fv(vertex.normal);
// 		glColor3ub(125, 200, 0);
// 		glVertex3fv(vertex.position);
// 		
// 	}
// 	glEnd();
// 	glPopMatrix();
// }
//
//
//
