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

	
	if (gameObject->position.z > 26.0f && gameObject->position.z < 27.0f)
	{
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			gameObject->getComponent<ArrowComponent>()->playerPressedOnTime = true;
			gameObject->destroy = true;
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			gameObject->getComponent<ArrowComponent>()->playerPressedOnTime = true;
			gameObject->destroy = true;
		}

		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			gameObject->getComponent<ArrowComponent>()->playerPressedOnTime = true;
			gameObject->destroy = true;
		}

		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			gameObject->getComponent<ArrowComponent>()->playerPressedOnTime = true;
			gameObject->destroy = true;
		}
	}
}
