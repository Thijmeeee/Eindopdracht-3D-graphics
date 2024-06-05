#include "ArrowComponent.h"

#include "../GameObject.h"


ArrowComponent::ArrowComponent(Direction direction, std::shared_ptr<ModelComponent> arrowModel, bool spawner)
	: direction(direction), arrowModel(arrowModel), arrowMatrix(1.0f)
{
	float z = -100;
	if (!spawner)
	{
		z = 0;
	}

	arrowMatrix = glm::scale(arrowMatrix, glm::vec3(0.25));
	switch (direction)
	{
	case UP:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(35, 5, z));
		arrowMatrix = glm::rotate(arrowMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
		color = glm::vec4(0.5, 0.5, 0.5, 1);
		break;
	}
	case DOWN:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(45, 5, z));
		arrowMatrix = glm::rotate(arrowMatrix, glm::radians(270.0f), glm::vec3(0, 0, 1));
		color = glm::vec4(1, 1, 1, 1);
		break;
	}
	case LEFT:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(25.0f, 5, z));
		arrowMatrix = glm::rotate(arrowMatrix, glm::radians(180.f), glm::vec3(0, 1, 0));
		color = glm::vec4(0, 0, 0.5, 1);
		break;
	}
	case RIGHT:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(60.0f, 5, z));
		color = glm::vec4(1, 0, 0.5, 1);
		break;
	}
	}
}

void ArrowComponent::draw()
{
	glm::mat4 modelMatrix(1.0f);
	if (gameObject) {
		modelMatrix = glm::translate(modelMatrix, gameObject->position);
		modelMatrix = modelMatrix * arrowMatrix;
	}
	tigl::shader->setModelMatrix(modelMatrix);

	tigl::shader->enableColorMult(true);
	tigl::shader->setColorMult(color);
	arrowModel->draw();
	tigl::shader->enableColorMult(false);
}