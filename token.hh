#ifndef _LOX_TOKEN_
#define _LOX_TOKEN_

#include <iostream>
#include <string>

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS,
    SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS,
    TRUE, VAR, WHILE,

    EOFILE
};

class Token {
    TokenType type;
    std::string lexeme;
    // We'll make it a string, but would prefer to make it a void*
    std::string literal;
    int line;

    friend std::ostream &operator<<(std::ostream &out, const Token &c);

    public:
    Token(TokenType _type, std::string _lexeme, std::string _literal, int _line) :
            type(_type), lexeme(_lexeme), literal(_literal), line(_line)
    { (void) line; };

};

std::ostream &operator<<(std::ostream &os, const Token &t);

#endif /* _LOX_TOKEN_ */
