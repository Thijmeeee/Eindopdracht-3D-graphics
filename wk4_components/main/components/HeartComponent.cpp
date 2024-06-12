#include "HeartComponent.h"

HeartComponent::HeartComponent(int id, std::shared_ptr<ModelComponent> heartModel)
	:id(id), heartModel(heartModel), heartMatrix(1.0f)
{
	heartMatrix = glm::scale(heartMatrix, glm::vec3(1.0f));

	heartMatrix = glm::rotate(heartMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
	heartMatrix = glm::rotate(heartMatrix, glm::radians(-180.0f), glm::vec3(0, 0, 1));

	if (!heartModel) {
		std::cerr << "Error: heartModel is a nullptr in HeartComponent constructor" << std::endl;
	}
	//color = glm::vec4(1, 1, 1, 1);
}

void HeartComponent::setPosition(glm::vec3 position) {
	gameObject->position = position;
}

void HeartComponent::draw()
{
	glm::mat4 modelMatrix(1.0f);
	if (gameObject) {
		modelMatrix = glm::translate(modelMatrix, gameObject->position);
		modelMatrix = modelMatrix * heartMatrix;
	}
	tigl::shader->setModelMatrix(modelMatrix);

	if (heartModel != nullptr) {
		heartModel->draw();
	}

}