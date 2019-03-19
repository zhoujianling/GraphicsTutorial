#include "model.h"
#include "utils.h"
// #include "happly.h"
#include "io.h"
#include "iostream"

Model::Model()
{
	
}

void Model::Init(const char* modelPath)
{
	int nFileSize = 0;
	int len = strlen(modelPath);
	if (len < 4) return;
	const auto &suffix = std::string(modelPath + len - 3);
	if (suffix == "obj")
	{
		LoadObj(modelPath, this);
	} else if (suffix == "ply")
	{
		LoadPly(modelPath, this);
	} else
	{
		std::cerr << "Unsupported types:" << modelPath << std::endl;
		return;
	}
}

void Model::Draw()
{
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecularMaterial);
	glPushMatrix();
	// 要后移一点，不然容易跟相机重合，看不到模型
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotated(90.0, 0, 1.0, 0);
	glBegin(GL_TRIANGLES);
	// 假设绘制的是三角化的网格模型
	for (auto i = 0; i < faceIndices.size(); i ++)
	{
		Vertex vertex = vertices[faceIndices[i]];
		//glTexCoord2fv(vertex.texcoord);
		//glNormal3fv(vertex.normal);
		glColor3ub(125, 200, 0);
		glVertex3fv(vertex.position);
		
	}
	glEnd();
	glPopMatrix();
}



