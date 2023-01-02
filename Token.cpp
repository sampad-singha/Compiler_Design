#include "Token.h"

#include <utility>

const std::string& Token::getContains() const {
    return contains;
}

const std::string& Token::getType() const {
    return type;
}

int Token::getLineNumber() const {
    return line_number;
}

Token::Token(std::string contains, std::string type, int lineNumber) : contains(std::move(contains)), type(std::move(type)),
line_number(lineNumber) {}