#include "MoveToComponent.h"

#include "ArrowComponent.h"
#include "../game/GameObject.h"


MoveToComponent::MoveToComponent()
{
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	//gameObject->position = (1 - speed) * gameObject->position + speed * target;

	//float angle = atan2(gameObject->position.z - target.z, gameObject->position.x - target.x);

	//gameObject->rotation.y = 0.05f * angle + 0.95f * gameObject->rotation.y;

	glm::vec3 diffVector = target - gameObject->position;

	float length = glm::length(diffVector); // GLM function to compute the magnitude

	if (length > 0) { // Prevent division by zero
		glm::vec3 normalVector = glm::normalize(diffVector); // GLM function to normalize the vector

		gameObject->position += normalVector * (speed * elapsedTime);
	}
}
