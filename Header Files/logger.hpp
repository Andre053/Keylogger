#include <iostream>
#include <fstream>

class Log {
    public:
        Log();
        void listen();

    private:

};

class Output {
    public:
        Output();
        void save_to_file(std::string log);
        void email_logs(std::string filename, std::string email);

    private:

};