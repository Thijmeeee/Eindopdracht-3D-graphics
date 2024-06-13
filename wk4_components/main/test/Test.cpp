#include "Test.h"

FileWriter fileWriter;

Test::Test() {}

bool Test::TestListNotEmpty(std::list<std::shared_ptr<GameObject>> objects) {
    bool result = !objects.empty();
    if (result) fileWriter.writeTextToFile("Models are loaded in correctly.");
    return result;
}

void Test::TestCountOfObjectList(std::list<std::shared_ptr<GameObject>> objects) {
    fileWriter.writeTextToFile("Expected is 8, the result of the test is: " + std::to_string(objects.size()));
}
