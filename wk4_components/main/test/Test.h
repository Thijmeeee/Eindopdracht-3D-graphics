#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "../game/GameObject.h"
#include <list>
#include <iostream>
#include <fstream>

class Test {
public:
	Test();
	~Test() = default;

	std::ofstream file;
	std::string FILEPATH = "C:\\Users\\thijm\\OneDrive - Avans Hogeschool\\Documenten\\GitHub\\Eindopdracht-3D-graphics\\wk4_components\\files\\file.txt";

	bool TestListNotEmpty(std::list<std::shared_ptr<GameObject>> objects);
	void TestCountOfObjectList(std::list<std::shared_ptr<GameObject>> objects);
};
