#pragma once
#include "mesh.h"
#include <vector>

class Camera;
class Model { // hold an instance pointer -> renderManager which is an interface implemented by Scene?
private:
	std::vector<zjl::TriMesh> meshes_;
	// bbox
	// wire_frame
	// shadow
public:
	Model();

	// ~Model();

	void Draw(const Camera&);

	std::vector<zjl::TriMesh>& GetMeshes() { return this->meshes_; }

};
