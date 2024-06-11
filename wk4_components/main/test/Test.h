#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "../game/GameObject.h"
#include <list>
#include <iostream>

class Test {
public:
	Test() = default;
	~Test() = default;

	bool TestListNotEmpty(std::list<std::shared_ptr<GameObject>> objects);
};
