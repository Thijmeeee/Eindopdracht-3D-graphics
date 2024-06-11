#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "ArrowUpdateComponent.h"
#include "ArrowComponent.h"
#include "MoveToComponent.h"
#include "../game/GameObject.h"


void ArrowUpdateComponent::update(float elapsedTime)
{
	if (gameObject->position.z >= 26.5f)
	{
		gameObject->destroy = true;

	}

	std::shared_ptr<ArrowComponent> arrow = gameObject->getComponent<ArrowComponent>();
	
	if (gameObject->position.z > 24.5f && gameObject->position.z < 26.0f)
	{
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS && arrow->direction == ArrowComponent::Direction::UP)
		{
			arrow->playerPressedOnTime = true;
			gameObject->destroy = true;
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS && arrow->direction == ArrowComponent::Direction::DOWN)
		{
			arrow->playerPressedOnTime = true;
			gameObject->destroy = true;
		}
		
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS && arrow->direction == ArrowComponent::Direction::LEFT)
		{
			arrow->playerPressedOnTime = true;
			gameObject->destroy = true;
		}

		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS && arrow->direction == ArrowComponent::Direction::RIGHT)
		{
			arrow->playerPressedOnTime = true;
			gameObject->destroy = true;
		}
	}
}
