#include "mesh.h"
#include "camera.h"
#include "model.h"

Model::Model()
{
}

void Model::Draw(const Camera& camera) {
	for (auto& mesh : meshes_) {
		mesh.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
}
