#pragma once
#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "../tigl.h"
#include "DrawComponent.h"
#include "ModelComponent.h"
#include "../GameObject.h"

using tigl::Vertex;

class NumberComponent : public DrawComponent
{

public:
	enum Units { UNIT, TENS, HUNDERDS };
	NumberComponent(std::shared_ptr<ModelComponent> numberModel, bool shouldBeVisible, Units unit);
	~NumberComponent() = default;

	virtual void draw() override;
	void setPosition(glm::vec3 position);

	std::shared_ptr<ModelComponent> numberModel;
	bool shouldBeVisible = false;
	Units unit;

private:
	glm::vec4 color;
	glm::mat4 numberMatrix;



};

