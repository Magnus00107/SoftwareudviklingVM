#include <iostream>
#include <array>

//const char* stages[] = {"Backlog", "Doing", "Review", "Done"};
//const int numStages = sizeof(stages) / sizeof(stages[0]); //sizeof(stages) gives the size of the array in bytes, sizeof(stages[0]) gives the size of the first element in bytes.

std::array<const char*, 4> stages = {"Backlog", "Doing", "Review", "Done"};

int main() {
    for (int i = 0; i < stages.size(); ++i) {
        std::cout << i << std::endl;
    }
    return 0;
}
