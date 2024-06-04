#include "ArrowUpdateComponent.h"

#include "ArrowComponent.h"
#include "MoveToComponent.h"
#include "../GameObject.h"


void ArrowUpdateComponent::update(float elapsedTime)
{
	if (gameObject->position.z > 12.75f && gameObject->position.z < 13.00f)
	{
		gameObject->destroy = true;

	}
	
}
