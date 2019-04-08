#include "model.h"
#include "utils.h"
// #include "happly.h"
#include "io.h"
#include "iostream"

Model::Model()
{
	
}

void Model::Init(const char* model_path)
{
	int len = strlen(model_path);
	if (len < 4) return;
	const auto &suffix = std::string(model_path + len - 3);
	if (suffix == "obj")
	{
		LoadObj(model_path, this);
	} else if (suffix == "ply")
	{
		LoadPly(model_path, this);
	} else
	{
		std::cerr << "Unsupported types:" << model_path << std::endl;
		return;
	}
}

void Model::Draw()
{
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_material_);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_material_);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material_);
	glPushMatrix();
	// 要后移一点，不然容易跟相机重合，看不到模型
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotated(90.0, 0, 1.0, 0);
	glBegin(GL_TRIANGLES);
	// 假设绘制的是三角化的网格模型
	for (auto i = 0; i < face_indices_.size(); i ++)
	{
		auto vertex = vertices_[face_indices_[i]];
		//glTexCoord2fv(vertex.tex_coord_);
		//glNormal3fv(vertex.normal_);
		glColor3ub(125, 200, 0);
		glVertex3fv(vertex.position_);
		
	}
	glEnd();
	glPopMatrix();
}



