#ifndef COMPILER_DESIGN_TOKEN_H
#define COMPILER_DESIGN_TOKEN_H


#include <string>

class Token {
public:
    Token(std::string contains, std::string type, int lineNumber);

    const std::string& getContains() const;

    const std::string& getType() const;

    int getLineNumber() const;

private:
    std::string contains;
    std::string type;
    int line_number;
};


#endif //COMPILER_DESIGN_TOKEN_H