#include <iostream>
#include <fstream>

int main() {
    std::ofstream logfile("log.txt");

    if (!logfile.is_open()) {
        std::cerr << "Error: Failed to open log file." << std::endl;
        return 1;
    }

    std::streambuf* original_stdout = std::cout.rdbuf();
    std::cout.rdbuf(logfile.rdbuf());

    // Now, you can log messages to the log file using std::cout
    std::cout << "This is a log message." << std::endl;
    std::cout << "Another log message." << std::endl;

    // Restore the original stdout stream buffer and close the log file
    std::cout.rdbuf(original_stdout);
    logfile.close();

    return 0;
}
