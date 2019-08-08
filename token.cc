#include "token.hh"


std::ostream &operator<<(std::ostream &os, const Token &t) {
    std::string TokenTypeStrings[] {
        // Single-character tokens.
        "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "COMMA", "DOT",
        "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

        // One or two character tokens.
        "BANG", "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL", "GREATER", "GREATER_EQUAL",
        "LESS", "LESS_EQUAL",

        // Literals.
        "IDENTIFIER", "STRING", "NUMBER",

        // Keywords.
        "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR", "PRINT",
        "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",

        "EOFILE"
    };

    os << TokenTypeStrings[t.type] << " " << t.lexeme << " " << std::string(t.literal)
       << std::endl;

    return os;
}

