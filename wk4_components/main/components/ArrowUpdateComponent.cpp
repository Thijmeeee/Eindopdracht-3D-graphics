#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "ArrowUpdateComponent.h"
#include "ArrowComponent.h"
#include "MoveToComponent.h"
#include "../GameObject.h"


void ArrowUpdateComponent::update(float elapsedTime)
{
	if (gameObject->position.z > 20.00f)
	{
		gameObject->destroy = true;

	}

	//TODO add
	if (gameObject->position.z > 12.00f && gameObject->position.z < 12.50f)
	{
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
		{

			gameObject->destroy = true;
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			gameObject->destroy = true;
		}

		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			gameObject->destroy = true;
		}

		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			gameObject->destroy = true;
		}
	}
}
