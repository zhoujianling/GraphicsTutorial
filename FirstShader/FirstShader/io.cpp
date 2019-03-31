#include "io.h"
#include "Include/objloader.h"
#include "Include/ply_io.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Include/sbt_image.h"
#include "vertex.h"

extern "C" {
	typedef struct options
	{
		bool verbose;
		char* input_filename;
		char* output_filename;
	} Opts;

	typedef struct vec3f
	{
		float x, y, z;
	} Vec3f;

	typedef struct face
	{
		unsigned char count;
		int* vertex_indices;
	} Face;

	typedef struct triangle_mesh
	{
		int n_verts;
		int n_faces;
		Vec3f* vertices;
		Face* faces;
	} TriMesh;

	const char *elem_names[] = { "vertex", "face" };

	PlyProperty vert_props[] = {
	  {const_cast<char *>("x"), Float32, Float32, offsetof(Vec3f,x), 0, 0, 0, 0},
	  {const_cast<char *>("y"), Float32, Float32, offsetof(Vec3f,y), 0, 0, 0, 0},
	  {const_cast<char *>("z"), Float32, Float32, offsetof(Vec3f,z), 0, 0, 0, 0},
	};


	PlyProperty face_props[] = {
	  {const_cast<char *>("vertex_indices"), Int32, Int32, offsetof(Face,vertex_indices), 1, Uint8, Uint8, offsetof(Face,count)},
	};

	void read_ply_file(const char* filename, TriMesh* mesh)
	{
		int elem_count;
		char *elem_name;
		int i;
		int j;

		FILE *fp = fopen(filename, "rb");
		if (!fp) { return; }
		PlyFile *in_ply = read_ply(fp);

		for (i = 0; i < in_ply->num_elem_types; i++)
		{
			elem_name = setup_element_read_ply(in_ply, i, &elem_count);

			if (!strcmp("vertex", elem_name))
			{
				mesh->vertices = (Vec3f*)malloc(sizeof(Vec3f) * elem_count);
				mesh->n_verts = elem_count;

				setup_property_ply(in_ply, &vert_props[0]);
				setup_property_ply(in_ply, &vert_props[1]);
				setup_property_ply(in_ply, &vert_props[2]);

				for (j = 0; j < elem_count; j++) {
					get_element_ply(in_ply, (void *)&mesh->vertices[j]);
				}
			}

			if (!strcmp("face", elem_name))
			{
				mesh->n_faces = elem_count;
				mesh->faces = (Face*)malloc(sizeof(Face) * elem_count);

				setup_property_ply(in_ply, &face_props[0]);

				for (j = 0; j < elem_count; j++) {
					get_element_ply(in_ply, (void *)&mesh->faces[j]);
				}
			}
		}

		close_ply(in_ply);
		free_ply(in_ply);
	}

}

void LoadPly(std::string modelPath, VertexBuffer *buffer, ElementBuffer *element_buffer)
{
	memset(buffer, 0, sizeof(float) * buffer->GetVerticesCount() * 16);
	TriMesh trimesh;
	read_ply_file(modelPath.c_str(), &trimesh);
	buffer->SetVertexCount(trimesh.n_verts);
	for (int i = 0; i < trimesh.n_verts; i ++)
	{
		const auto& vt = trimesh.vertices[i];
		Vertex vertex;
		vertex.position[0] = vt.x;
		vertex.position[1] = vt.y;
		vertex.position[2] = vt.z;
		buffer->SetPosition(i, vt.x, vt.y, vt.z);
		buffer->SetColor(i, 1.0f, 1.0f, 1.0f);
	}
	element_buffer->SetBufferLength(trimesh.n_faces * 3);
	for (int i = 0; i < trimesh.n_faces; i ++)
	{
		const auto& face = trimesh.faces[i];
		if (face.count != 3)
		{
			std::cerr << "Not a triangulated mesh, exit" << std::endl;
			break;
		}
		unsigned int *indices = element_buffer->GetBuffer();
		for (int j = 0; j < 3; j ++)
		{
			indices[i * 3 + j] = face.vertex_indices[j];
		}
	}
}

// void LoadObj(std::string modelPath, VertexBuffer *model)
// {
// 	objl::Loader loader;
// 	const auto success = loader.LoadFile(modelPath);
// 	if (! success)
// 	{
// 		fprintf(stderr, "Fail to load obj!\n");
// 		return;
// 	}
// 	if (loader.LoadedMeshes.empty())
// 	{
// 		fprintf(stderr, "No mesh is loaded!\n");
// 		return;
// 	}
// 	const auto loadedMesh = loader.LoadedMeshes[0];
// 	for (const auto &vt : loadedMesh.Vertices)
// 	{
// 		Vertex vertex;
// 		vertex.position[0] = vt.Position.X;
// 		vertex.position[1] = vt.Position.Y;
// 		vertex.position[2] = vt.Position.Z;
// 		vertex.normal[0] = vt.Normal.X;
// 		vertex.normal[1] = vt.Normal.Y;
// 		vertex.normal[2] = vt.Normal.Z;
// 		vertex.texcoord[0] = vt.TextureCoordinate.X;
// 		vertex.texcoord[1] = vt.TextureCoordinate.Y;
// 		model->GetVertices().push_back(vertex);
// 	}
// 	for (const auto &index : loadedMesh.Indices)
// 	{
// 		model->GetFaces().push_back(index);
// 	}
// }

void LoadRGBImage(std::string imagePath, unsigned char *& data, int &width, int &height)
{
	// 下面的方法将第一个像素弄到左下角，用于 OpenGL 加载纹理
	// stbi_set_flip_vertically_on_load(true); 
	int channel;
	data = stbi_load(imagePath.c_str(), &width, &height, &channel, STBI_rgb);
//	stbi_image_free(data);
}

