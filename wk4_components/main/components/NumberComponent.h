#pragma once
#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "../tigl.h"
#include "DrawComponent.h"
#include "ModelComponent.h"

using tigl::Vertex;



class NumberComponent : public DrawComponent
{

public:
	NumberComponent(std::shared_ptr<ModelComponent> numberModel);
	~NumberComponent() = default;

	virtual void draw() override;

	std::shared_ptr<ModelComponent> numberModel;
	bool shouldBeVisible = false;

private:
	glm::vec4 color;
	glm::mat4 numberMatrix;



};

