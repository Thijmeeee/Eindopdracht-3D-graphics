#include "ArrowComponent.h"

#include "../GameObject.h"


ArrowComponent::ArrowComponent(Direction direction, std::shared_ptr<ModelComponent> arrowModel)
	: arrowModel(arrowModel), arrowMatrix(1.0f)
{
	arrowMatrix = glm::scale(arrowMatrix, glm::vec3(0.25));
	switch (direction)
	{
	case UP:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(35, 5, 0));
		arrowMatrix = glm::rotate(arrowMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
		break;
	}
	case DOWN:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(45, 5, 0));
		arrowMatrix = glm::rotate(arrowMatrix, glm::radians(270.0f), glm::vec3(0, 0, 1));
		break;
	}
	case LEFT:
	{
		arrowMatrix = glm::rotate(arrowMatrix, glm::radians(180.f), glm::vec3(0, 1, 0));
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(-20.0f, 5, 0));
		break;
	}
	case RIGHT:
	{
		arrowMatrix = glm::translate(arrowMatrix, glm::vec3(60.0f, 5, 0));
		break;
	}
	}
	color = glm::vec4(1, 1, 0.5, 1);
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