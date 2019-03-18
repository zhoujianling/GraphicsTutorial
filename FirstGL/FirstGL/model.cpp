#include "model.h"
#include "utils.h"
#include "happly.h"
#include "objloader.h"

Model::Model()
{
	
}

void Model::LoadObj(const char* modelPath)
{
	objl::Loader loader;
	const auto success = loader.LoadFile(modelPath);
	if (! success)
	{
		fprintf(stderr, "Fail to load obj!\n");
		return;
	}
	if (loader.LoadedMeshes.empty())
	{
		fprintf(stderr, "No mesh is loaded!\n");
		return;
	}
	const auto loadedMesh = loader.LoadedMeshes[0];
	for (const auto &vt : loadedMesh.Vertices)
	{
		Vertex vertex;
		vertex.position[0] = vt.Position.X;
		vertex.position[1] = vt.Position.Y;
		vertex.position[2] = vt.Position.Z;
		vertex.normal[0] = vt.Normal.X;
		vertex.normal[1] = vt.Normal.Y;
		vertex.normal[2] = vt.Normal.Z;
		vertex.texcoord[0] = vt.TextureCoordinate.X;
		vertex.texcoord[1] = vt.TextureCoordinate.Y;
		vertices.push_back(vertex);
	}
	for (const auto &index : loadedMesh.Indices)
	{
		faceIndices.push_back(index );
	}
}

void Model::LoadPly(const char* modelPath)
{
	happly::PLYData plyIn(modelPath);

	// Get mesh-style data from the object
	std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
	std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();
	for (const auto &vt : vPos)
	{
		Vertex vertex;
		vertex.position[0] = vt[0];
		vertex.position[1] = vt[1];
		vertex.position[2] = vt[2];
		vertices.push_back(vertex);
	}
	for (const auto &is : fInd)
	{
		if (is.size() != 3) break;;
		for (const auto &i : is)
		{
			faceIndices.push_back(i);
		}
	}
	
}


void Model::Init(const char* modelPath)
{
	int nFileSize = 0;
	int len = strlen(modelPath);
	if (len < 4) return;
	const auto &suffix = std::string(modelPath + len - 3);
	if (suffix == "obj")
	{
		this->LoadObj(modelPath);
	} else if (suffix == "ply")
	{
		this->LoadPly(modelPath);
	} else
	{
		fprintf(stderr, "Unsupported types: %s!\n", modelPath);
		return;
	}
}

void Model::Draw()
{
	glPushMatrix();
	// 要后移一点，不然容易跟相机重合，看不到模型
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotated(90.0, 0, 1.0, 0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faceIndices.size(); i ++)
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


