#include "Test.h"

bool Test::TestListNotEmpty(std::list<std::shared_ptr<GameObject>> objects) {
	bool result = !objects.empty();

	if (result) std::cout << "Object list is right initialized" << std::endl;

	return result;
}