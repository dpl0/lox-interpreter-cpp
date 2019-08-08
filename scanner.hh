#ifndef _LOX_SCANNER_
#define _LOX_SCANNER_

#include "token.hh"

#include <string>
#include <vector>
#include <map>

class Scanner {
    Lox *loxInstance = nullptr;
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    static const std::map<std::string, TokenType> keywords;


public:
    Scanner(Lox *_loxInstance, std::string &_source) : loxInstance(_loxInstance), source(_source) {};
    std::vector<Token> scanTokens();

private:
    void scanToken();
    void scanIdentifier();
    void scanNumber();
    void scanString();

    bool isAtEnd();
    bool match(char expected);
    char peek();
    char peekNext();
    char advance();

    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);

    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphanumeric(char c);
};

#endif /* _LOX_SCANNER_ */
