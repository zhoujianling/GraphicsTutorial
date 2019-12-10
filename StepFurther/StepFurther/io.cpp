#include "io.h"
#include "Include/objloader.h"
#include "Include/ply_io.h"
#include "mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Include/sbt_image.h"
#include "vertex.h"
#include <algorithm>

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

	typedef struct vec6f
	{
		float x, y, z, nx, ny, nz;
	} Vec6f;

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

	typedef struct triangle_mesh_normal
	{
		int n_verts;
		int n_faces;
		Vec6f* vertices;
		Face* faces;
	} TriMeshNormal;

	const char *elem_names[] = { "vertex", "face" };

	PlyProperty vert_props[] = {
	  {const_cast<char *>("x"), Float32, Float32, offsetof(Vec3f,x), 0, 0, 0, 0},
	  {const_cast<char *>("y"), Float32, Float32, offsetof(Vec3f,y), 0, 0, 0, 0},
	  {const_cast<char *>("z"), Float32, Float32, offsetof(Vec3f,z), 0, 0, 0, 0},
	};

	PlyProperty vert_n_props[] = {
	  {const_cast<char *>("x"), Float32, Float32, offsetof(Vec6f,x), 0, 0, 0, 0},
	  {const_cast<char *>("y"), Float32, Float32, offsetof(Vec6f,y), 0, 0, 0, 0},
	  {const_cast<char *>("z"), Float32, Float32, offsetof(Vec6f,z), 0, 0, 0, 0},
	  {const_cast<char *>("nx"), Float32, Float32, offsetof(Vec6f,nx), 0, 0, 0, 0},
	  {const_cast<char *>("ny"), Float32, Float32, offsetof(Vec6f,ny), 0, 0, 0, 0},
	  {const_cast<char *>("nz"), Float32, Float32, offsetof(Vec6f,nz), 0, 0, 0, 0},
	};


	PlyProperty face_props[] = {
	  {const_cast<char *>("vertex_indices"), Int32, Int32, offsetof(Face,vertex_indices), 1, Uint8, Uint8, offsetof(Face,count)},
	};

	void read_ply_file(const char* filename, TriMeshNormal* mesh)
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
				int prop_cnt = in_ply->elems[i]->nprops;
				mesh->vertices = (Vec6f*)malloc(sizeof(Vec6f) * elem_count);
				//memset(mesh->vertices, 0, sizeof(Vec6f) * elem_count);
				mesh->n_verts = elem_count;
				if (prop_cnt == 3)
				{
					setup_property_ply(in_ply, &vert_props[0]);
					setup_property_ply(in_ply, &vert_props[1]);
					setup_property_ply(in_ply, &vert_props[2]);
	
					for (j = 0; j < elem_count; j++) {
						get_element_ply(in_ply, (void *)&mesh->vertices[j]);
					}
					
				} else if (prop_cnt == 6)
				{
					setup_property_ply(in_ply, &vert_n_props[0]);
					setup_property_ply(in_ply, &vert_n_props[1]);
					setup_property_ply(in_ply, &vert_n_props[2]);
					setup_property_ply(in_ply, &vert_n_props[3]);
					setup_property_ply(in_ply, &vert_n_props[4]);
					setup_property_ply(in_ply, &vert_n_props[5]);
	
					for (j = 0; j < elem_count; j++) {
						get_element_ply(in_ply, (void *)&mesh->vertices[j]);
					}
					
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



void LoadModel(const std::string& model_path, VertexBuffer& buffer, ElementBuffer& element_buffer) {
	const std::string file_name_suffix = model_path.substr(model_path.rfind('.') + 1, model_path.npos);
	if (file_name_suffix == "obj") {
		LoadObj(model_path, buffer, element_buffer);
	} else if (file_name_suffix == "ply") {
		LoadPly(model_path, &buffer, &element_buffer);
	} else {
		std::cerr << "Warning: Can't load " << model_path << std::endl;
	}
}

void LoadPly(const std::string& model_path, VertexBuffer *buffer, ElementBuffer *element_buffer)
{
	memset(buffer, 0, sizeof(float) * buffer->GetVerticesCount() * 16);
	TriMeshNormal trimesh;
	read_ply_file(model_path.c_str(), &trimesh);
	buffer->SetVertexCount(trimesh.n_verts);
	for (int i = 0; i < trimesh.n_verts; i ++)
	{
		const auto& vt = trimesh.vertices[i];
		Vertex vertex{};
		vertex.position[0] = vt.x;
		vertex.position[1] = vt.y;
		vertex.position[2] = vt.z;
		buffer->SetPosition(i, vt.x, vt.y, vt.z);
		buffer->SetNormal(i, vt.nx, vt.ny, vt.nz);
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

bool LoadObj(const std::string& model_path, std::vector<zjl::TriMesh>& meshes) {
	std::string model_path_filtered = model_path;
	// change backslash to forward slash
	for (size_t i = 0; i < model_path_filtered.size(); i++) {
		if (model_path_filtered[i] == '\\') {
			model_path_filtered[i] = '/';
		}
	}
	std::string model_dir = ".";
	auto forward_slash_pos = model_path_filtered.rfind('/');

	if (forward_slash_pos != model_path_filtered.npos) {
		model_dir = model_path.substr(0, forward_slash_pos);
	}

 	objl::Loader loader;
 	const auto success = loader.LoadFile(model_path_filtered);
 	if (! success) {
 		fprintf(stderr, "Fail to load obj!\n");
 		return false;
 	}
 	if (loader.LoadedMeshes.empty()) {
 		fprintf(stderr, "No mesh is loaded!\n");
 		return false;
 	}
	for (const auto& loaded_mesh : loader.LoadedMeshes) {
		meshes.push_back(zjl::TriMesh());
		// std::cout << "name:" << loaded_mesh.MeshMaterial.name << std::endl;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> face_indices;
 		for (const auto &vt : loaded_mesh.Vertices) {
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
 		// model->GetVertices().push_back(vertex);
 		}
 		for (const auto &index : loaded_mesh.Indices) {
			face_indices.push_back(index);
 			//model->GetFaces().push_back(index);
 		}
		auto& vertices_buff = meshes.back().GetVertexBuffer(); 
		auto& elements_buff = meshes.back().GetElementBuffer();
		vertices_buff.SetVertexCount(vertices.size());
		elements_buff.SetBufferLength(face_indices.size());
		memcpy(vertices_buff.GetVertex(), vertices.data(), sizeof(Vertex) * vertices.size());
		memcpy(elements_buff.GetBuffer(), face_indices.data(), sizeof(unsigned int) * face_indices.size());

		std::string map_kd_filepath = model_dir + "/" + loaded_mesh.MeshMaterial.map_Kd;
		//std::cout << "model_path " << model_path << std::endl;
		//std::cout << "model_path2 " << str << std::endl;
		//std::cout << "model_dir " << model_dir << std::endl;
		//std::cout << "path: " << map_kd_filepath << std::endl;
		meshes.back().SetTextureColorFile(map_kd_filepath);
	}
	return true;
}

 void LoadObj(std::string modelPath, VertexBuffer& vertices_buff, ElementBuffer& elements_buff) {
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
	std::vector<Vertex> vertices;
	std::vector<unsigned int> face_indices;
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
 		// model->GetVertices().push_back(vertex);
 	}
 	for (const auto &index : loadedMesh.Indices)
 	{
		face_indices.push_back(index);
 		//model->GetFaces().push_back(index);
 	}
	vertices_buff.SetVertexCount(vertices.size());
	elements_buff.SetBufferLength(face_indices.size());
	memcpy(vertices_buff.GetVertex(), vertices.data(), sizeof(Vertex) * vertices.size());
	memcpy(elements_buff.GetBuffer(), face_indices.data(), sizeof(unsigned int) * face_indices.size());
 }

void LoadRGBImage(std::string image_path, unsigned char *& data, int &width, int &height)
{
	// 下面的方法将第一个像素弄到左下角，用于 OpenGL 加载纹理
	stbi_set_flip_vertically_on_load(true); 
	int channel;
	// 最后一个参数无需指定格式。。。
	data = stbi_load(image_path.c_str(), &width, &height, &channel, 0);
//	stbi_image_free(data);
}

void LoadRGBAImage(std::string image_path, unsigned char *& data, int &width, int &height)
{
	// 下面的方法将第一个像素弄到左下角，用于 OpenGL 加载纹理
	stbi_set_flip_vertically_on_load(1); 
	int channel;
	data = stbi_load(image_path.c_str(), &width, &height, &channel, STBI_rgb);
//	stbi_image_free(data);
}
