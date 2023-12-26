

int main(){
    //Outputer
    std::ofstream logfile("log.txt");

    if (!logfile.is_open()) {
        std::cerr << "Error: Failed to open log file." << std::endl;
        return 1;
    }

    std::streambuf* original_stdout = std::cout.rdbuf();
    std::cout.rdbuf(logfile.rdbuf());
    //Outputer


    // Main program


    //Outputer
    std::cout.rdbuf(original_stdout);
    logfile.close();
    //Outputer
    
    return 0;
}