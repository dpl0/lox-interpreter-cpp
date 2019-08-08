#include "lox.hh"
#include "scanner.hh"
#include "token.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;


int main(int argc, char *argv[]) {
    std::string filename;
    Lox lox;

    if (argc > 2) {
        std::cout << "Usage: lox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        filename = std::string(argv[1]);
        std::cout << "Running from file " << filename << std::endl;
        lox.runFile(filename);
    } else {
        printf("Running prompt\n");
        lox.prompt();
    }

    return 0;
}


void Lox::runFile(std::string filename) {
    fs::path *filepath = new fs::path(filename);
    auto filesize = fs::file_size(*filepath);
    std::string source;

    if (not fs::exists(*filepath)) {
        error(0, "File not found");
    }
    // Allocate filesize bytes
    source.reserve(filesize);

    // We don't check to see if the file is only text
    std::fstream data(filename, std::ios_base::in);
    data.read(&source[0], filesize);

    run(source);
}

void Lox::prompt() {
    std::string text;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, text);

        run(text);
        hadError = false;
    }

}

void Lox::run(std::string source) {
    Scanner scanner(this, source);
    std::vector<Token> tokens = scanner.scanTokens();

    // For now, just print the tokens.
    for (auto token : tokens) {
        std::cout << "Token: " << token << std::endl;
    }
}


void Lox::error(int line, std::string msg) {
    report(line, "", msg);
}

void Lox::report(int line, std::string where, std::string msg) {
    std::cerr << "[line: " << line
              << "] Error" << where << ": " << msg << std::endl;

    hadError = true;
}
