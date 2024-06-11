#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (drawComponent == nullptr)
		drawComponent = dynamic_pointer_cast<DrawComponent>(component);

}

std::list<std::shared_ptr<Component>> GameObject::getComponents()
{
	return components;
}


void GameObject::draw(const glm::mat4 &parentMatrix)
{
	if (!drawComponent)
		return;

	glm::mat4 modelMatrix = parentMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scale);
	
	tigl::shader->setModelMatrix(modelMatrix);
	drawComponent->draw();
}

void GameObject::update(float elapsedTime)
{
	for (auto &c : components)
		c->update(elapsedTime);
}