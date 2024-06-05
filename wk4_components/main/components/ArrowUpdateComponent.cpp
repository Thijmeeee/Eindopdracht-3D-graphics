#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "ArrowUpdateComponent.h"
#include "ArrowComponent.h"
#include "MoveToComponent.h"
#include "../GameObject.h"


void ArrowUpdateComponent::update(float elapsedTime)
{
	if (gameObject->position.z >= 27.0f)
	{
		gameObject->destroy = true;

	}


	std::shared_ptr<ArrowComponent> arrow = gameObject->getComponent<ArrowComponent>();
	
	if (gameObject->position.z > 26.0f && gameObject->position.z < 27.0f)
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
