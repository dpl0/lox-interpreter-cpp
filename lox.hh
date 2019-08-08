#ifndef _LOX_LOX_
#define _LOX_LOX_

#include <string>

class Lox {
    bool hadError = false;
public:
    void runFile(std::string filename);
    void prompt();

    void error(int line, std::string msg);

private:
    void run(std::string source);

    void report(int line, std::string where, std::string msg);
};


#endif /* _LOX_LOX_ */
