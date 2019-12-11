#pragma once
#include "mesh.h"
#include "wireframe.h"
#include <vector>

class Camera;
struct RenderingOption;
class Model : public RenderingElement { // hold an instance pointer -> renderManager which is an interface implemented by Scene?
private:
	std::vector<zjl::TriMesh> meshes_;

	glm::mat4 model_matrix_;

	BoundingBox bbox_;

	WireFrame bbox_wire_;

	std::string name_;

	float scale_times_;

public:
	Model();

	// ~Model();

	void Init();

	Model& MoveBy(glm::fvec3 world_position);

	Model& RotateBy(glm::fvec3 axis, float radian);

	Model& ScaleBy(float ratio);

	std::vector<zjl::TriMesh>& GetMeshes() { return this->meshes_; }

	const std::vector<zjl::TriMesh>& GetConstMeshes() const { return this->meshes_; }

	void ComputeBoundingBox();

	const BoundingBox& GetBoundingBox() const { return this->bbox_; }

	const std::string& GetName() const { return this->name_; }

	void SetName(const std::string& name) { this->name_ = name; }

	float& GetScaleTimes() { return this->scale_times_; }

	WireFrame& GetBoxWires() { return this->bbox_wire_; }

	glm::mat4 ComputeModelMatrix() const {
		auto model_matrix_0 = glm::scale(glm::identity<glm::mat4>(), { scale_times_, scale_times_, scale_times_ });
		model_matrix_0 = model_matrix_0 * model_matrix_;
		return model_matrix_0;
	}
};
