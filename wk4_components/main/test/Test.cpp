#include "Test.h"

Test::Test() {}

bool Test::TestListNotEmpty(std::list<std::shared_ptr<GameObject>> objects) {
    std::ofstream file;
    file.open(FILEPATH, std::ios_base::app);

    bool result = !objects.empty();
    if (result) file << "Models are loaded in correctly.\n";

    file.close();
    return result;
}

void Test::TestCountOfObjectList(std::list<std::shared_ptr<GameObject>> objects) {
    std::ofstream file;
    file.open(FILEPATH, std::ios_base::app);

    file << "The expected result is 8, the result of the test is: " << objects.size() << "\n";

    file.close();
}
