#include "../Header Files/logger.hpp"

void Log::listen() {
    std::cout << "Starting to listen" << std::endl;

}

void Output::save_to_file(std::string log) {
    std::ofstream wFile; // file to write to

    wFile.open("log.txt");

    // catch error in opening the file
    if (!wFile.is_open()) exit(1);

    wFile << log;

    wFile.close();

    std::cout << "Saved current log to a file" << std::endl;
}

void Output::email_logs(std::string filename, std::string email) {
    std::cout << "Send file " << filename << " to address " << email << std::endl;

}