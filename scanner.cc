#include "lox.hh"
#include "scanner.hh"

const std::vector<std::string> Scanner::keywords = {
        "and", "class", "else", "false", "for", "fun", "if", "nil", "or",
        "print", "return",  "super", "this", "true",  "var", "while"
    };

std::vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }

    tokens.push_back(Token(EOFILE, "", nullptr, line));
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        case '(':
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '+':
            addToken(PLUS);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '*':
            addToken(STAR);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until EOL
                while (peek() != '\n' && !isAtEnd()) {
                    advance();
                }
            } else {
                addToken(SLASH);
            }
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '>':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case ';':
            addToken(SEMICOLON);
            break;

        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace
            break;
        case '\n':
            line++;
            break;

        case '"':
            scanString();
            break;

        default:
            if (isDigit(c)) {
                scanNumber();
            } else if (isAlpha(c)) {
                scanIdentifier();
            } else {
                loxInstance->error(line, "Unexpected character");
            }
            break;
    }

    return;
}

void Scanner::scanIdentifier() {
}

void Scanner::scanNumber() {
}

void Scanner::scanString() {
}

bool Scanner::isAtEnd() {
    return current > (int)source.size();
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if ((unsigned long) current + 1 > source.size()) return '\0';
    return source[current + 1];
}

char Scanner::advance() {
    current++;
    return source[current-1];
}

void Scanner::addToken(TokenType type) {
    // TODO - Get String representing literal
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal) {
    std::string text = ""; // TODO - GET FROM SOURCE substring(start, current)
    tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlphanumeric(char c) {
    return isAlpha(c) || isDigit(c);
}
