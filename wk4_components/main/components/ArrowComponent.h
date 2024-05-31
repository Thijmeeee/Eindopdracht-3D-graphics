#pragma once
#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "../tigl.h"
#include "DrawComponent.h"
#include "ModelComponent.h"

using tigl::Vertex;



class ArrowComponent : public DrawComponent
{
	
public:
	enum Direction { LEFT, RIGHT, UP, DOWN };

	std::vector<tigl::Vertex> verts;

	ArrowComponent(Direction direction, std::shared_ptr<ModelComponent> arrowModel);
	~ArrowComponent() = default;

	virtual void draw() override;

private:
	std::shared_ptr<ModelComponent> arrowModel;
	glm::mat4 arrowMatrix;


};

