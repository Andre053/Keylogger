#include <iostream>
#include <fstream>
#include <unistd.h> // linux specific C++ files

void readFile() {
    std::string line;
    std::ifstream keyboardEventFile("/dev/input/event2");

    if (keyboardEventFile.is_open()) {
        std::cout << "Reading keyboard file" << std::endl;

        while (getline(keyboardEventFile, line)) {
            std::cout << line << std::endl;
        }
        keyboardEventFile.close();
    };

}

int main() {
    std::cout << "Hello, World!" << std::endl;

    readFile();

    return 0;
}