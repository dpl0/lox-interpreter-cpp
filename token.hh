#ifndef _LOX_TOKEN_
#define _LOX_TOKEN_

#include <string>

enum TokenType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	EOFILE
};

class Token {
    TokenType type;
    std::string lexeme;
    void *literal;
    int line;

    public:
    Token(TokenType type, std::string lexeme, void *literal, int line);
};

#endif /* _LOX_TOKEN_ */
