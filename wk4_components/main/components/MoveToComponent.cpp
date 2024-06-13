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

	glm::vec3 diffVector = target - gameObject->position;

	float length = glm::length(diffVector); // GLM function to compute the magnitude

	if (length > 0) { // Prevent division by zero
		glm::vec3 normalVector = glm::normalize(diffVector); // GLM function to normalize the vector

		gameObject->position += normalVector * (speed * elapsedTime);
	}
}
