#include "lox.hh"
#include "scanner.hh"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string filename;

    if (argc > 2) {
        std::cout << "Usage: lox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        filename = std::string(argv[1]);
        std::cout << "Reading from file " << filename << std::endl;
        runFile(filename);
    } else {
        printf("Running prompt\n");
        prompt();
    }

    return 0;
}


void runFile(std::string filename) {
    std::cout << "Filename: " << filename << std::endl;
    std::ifstream filein(filename, ios_base::in);
    run(filein)
}

void run(std::ifstream filestream) {
}

void prompt() {
    std::string text;
    std::cout << ">: ";
    std::cin >> text;
    std::cout << "We got: " << text << std::endl;;
}
