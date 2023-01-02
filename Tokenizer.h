#ifndef COMPILER_DESIGN_TOKENIZER_H
#define COMPILER_DESIGN_TOKENIZER_H
#include <string>
#include <vector>
#include "Token.h"

class Tokenizer {
    static std::set<std::string> search_by_ith_char(char c, const std::set<std::string>& record, int index);
    static void check_data_type(std::vector<Token>& record, std::string& s);
    static void enlist(std::vector<Token>& record, std::string& s, const std::string& comment, const int& line_number);
public:
    static std::vector<Token> tokenize(std::vector<std::pair<std::string, int>>& record);
};


#endif //COMPILER_DESIGN_TOKENIZER_H
