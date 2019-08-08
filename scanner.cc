#include "lox.hh"
#include "scanner.hh"

const std::map<std::string, TokenType> Scanner::keywords = {
    {"and", AND}, {"class", CLASS}, {"else", ELSE}, {"false", FALSE},
    {"fun", FUN}, {"for", FOR}, {"if", IF}, {"nil", NIL}, {"or", OR},
    {"print", PRINT}, {"return", RETURN}, {"super", SUPER}, {"this", THIS},
    {"true", TRUE}, {"var", VAR}, {"while", WHILE} };

std::vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }

    tokens.push_back(Token(EOFILE, "", "", line));
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
     // std::cout << "Scanning identifier\n";
     // std::cout << "\tsource: " << source << "\n";
     // std::cout << "\t        " << std::string(current-1, ' ') << "^\n";

    while (isAlphanumeric(peek()))
        advance();

    // See if the identifier is a keyword
    std::string id = source.substr(start, current);
    TokenType type = IDENTIFIER;

    for (const auto& [keyword, keytype]  : keywords) {
        if (keyword == id) type = keytype;
    }

    // std::cout << "Got id: " << id << "\n";
    addToken(type, id);
}



void Scanner::scanNumber() {
    // std::cout << "Scanning number\n";
    // std::cout << "\tsource: " << source << "\n";
    // std::cout << "\t        " << std::string(current-1, ' ') << "^\n";

    while (isDigit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the '.'
        advance();
        while (isDigit(peek()))
            advance();
    }
    std::string num = source.substr(start, current);

    // std::cout << "Got number: " << num << "\n";
    // addToken(NUMBER, Double.parseDouble(source.substring(start, current)));
    // TODO Parse number and add it (we need to be able to store the literal
    // value at the Token object
    addToken(NUMBER, num);
}

void Scanner::scanString() {
    // std::cout << "Scanning string\n";
    // std::cout << "\tsource: " << source << "\n";
    // std::cout << "\t        " << std::string(current-1, ' ') << "^\n";

    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    // Unterminated string.
    if (isAtEnd()) {
        loxInstance->error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim surrounding quotes.
    std::string value = source.substr(start+1, current-start-2);

    addToken(STRING, value);
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
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal) {
    // std::string text = "";
    std::string text = source.substr(start, current-start-1);
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
