#include "NumberComponent.h"

#include "../GameObject.h"


NumberComponent::NumberComponent(std::shared_ptr<ModelComponent> numberModel, bool shouldBeVisible, bool tens) 
	: numberModel(numberModel), shouldBeVisible(shouldBeVisible), tens(tens), numberMatrix(1.0f)
{
	numberMatrix = glm::scale(numberMatrix, glm::vec3(10));

	numberMatrix = glm::rotate(numberMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	numberMatrix = glm::rotate(numberMatrix, glm::radians(180.0f), glm::vec3(0, 0, 1));
	numberMatrix = glm::rotate(numberMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));
	color = glm::vec4(1.0, 0.0f, 0.0f, 1.0f);
}

void NumberComponent::draw()
{
	if (shouldBeVisible) {
		glm::mat4 modelMatrix(1.0f);
		if (gameObject) {
			modelMatrix = glm::translate(modelMatrix, gameObject->position);
			modelMatrix = modelMatrix * numberMatrix;
		}
		tigl::shader->setModelMatrix(modelMatrix);

		tigl::shader->enableColorMult(true);
		tigl::shader->setColorMult(color);
		numberModel->draw();
		tigl::shader->enableColorMult(false);
	}
}