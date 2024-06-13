#include "NumberComponent.h"




NumberComponent::NumberComponent(std::shared_ptr<ModelComponent> numberModel, bool shouldBeVisible, Units unit)
	: numberModel(numberModel), shouldBeVisible(shouldBeVisible), unit(unit), numberMatrix(1.0f)
{
	numberMatrix = glm::scale(numberMatrix, glm::vec3(10));

	numberMatrix = glm::rotate(numberMatrix, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	numberMatrix = glm::rotate(numberMatrix, glm::radians(180.0f), glm::vec3(0, 0, 1));
	numberMatrix = glm::rotate(numberMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));

}

void NumberComponent::setPosition(glm::vec3 position) {
	gameObject->position = position;
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

		if (numberModel != nullptr) {
			numberModel->draw();
		}
		
	}
}