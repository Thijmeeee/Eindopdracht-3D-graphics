#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "lib/tigl.h"
#include "DrawComponent.h"
#include "ModelComponent.h"
#include "../game/GameObject.h"

using tigl::Vertex;

class HeartComponent : public DrawComponent
{

public:
	HeartComponent(int id, std::shared_ptr<ModelComponent> heartModel);
	~HeartComponent() = default;

	void setPosition(glm::vec3 position);
	virtual void draw() override;

	bool lifeLost = false;
	int id;

private:
	std::shared_ptr<ModelComponent> heartModel;
	glm::vec4 color;
	glm::mat4 heartMatrix;


};

