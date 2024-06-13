#include "HeartComponent.h"

HeartComponent::HeartComponent(std::shared_ptr<ModelComponent> heartModel)
    : heartModel(heartModel), heartMatrix(1.0f)
{
    heartMatrix = glm::scale(heartMatrix, glm::vec3(0.01f));
    heartMatrix = glm::rotate(heartMatrix, glm::radians(180.0f), glm::vec3(1, 0, 0));
    heartMatrix = glm::rotate(heartMatrix, glm::radians(-180.0f), glm::vec3(0, 0, 1));

    color = glm::vec4(1, 0, 0, 1);
}

void HeartComponent::setPosition(glm::vec3 position) {
    if (gameObject) {
        gameObject->position = position;
    }
}

void HeartComponent::draw() {
    if (heartModel) {
        glm::mat4 modelMatrix(1.0f);
        if (gameObject) {
            modelMatrix = glm::translate(modelMatrix, gameObject->position);
            modelMatrix = modelMatrix * heartMatrix;
        }
        tigl::shader->setModelMatrix(modelMatrix);
        tigl::shader->enableColorMult(true);
        if (lifeLost && color.r == 1.0f) {
            color = glm::vec4(0.5f, 0.5f, 0.5f, 1);
        }
        tigl::shader->setColorMult(color);
        heartModel->draw();
        tigl::shader->enableColorMult(false);
    }
}
