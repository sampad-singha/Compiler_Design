#include <iostream>
#include "Tokenizer.h"
#include "PreprocessingHandler.h"
#include "Token.h"
#include "Types.h"
#include "Utility.h"

std::vector<Token> Tokenizer::tokenize(std::vector<std::pair<std::string, int>>& record) {
    std::vector<Token> tokens;
    std::pair<bool, char> string_checker{ false, '0' };
    std::string s;
    for (auto& i : record) {
        if (i.first[0] == '#' && !i.first.empty()) {
            if (PreprocessingHandler::check_preprocessor(i.first)) {
                std::cout << "line - " << i.second << " \"" << i.first << "\" is correct" << std::endl;
            }
            else {
                std::cout << "error on line - " << i.second << " \"" << i.first << "\"" << std::endl;
                return {};
            }
            continue;
        }
        for (int j = 0; j < i.first.size(); j++) {
            if (i.first.at(j) == '\"') {
                if (!string_checker.first) {
                    string_checker.first = true;
                    string_checker.second = i.first.at(j);
                }
                else {
                    if (string_checker.second != i.first.at(j)) {
                        std::cout << "error on line - " << i.second << " \"" << i.first << "\"" << std::endl;
                        return {};
                    }
                    else {
                        enlist(tokens, s, "string", i.second);
                        string_checker.first = false;
                        string_checker.second = '0';
                    }
                }
                continue;
            }
            if (i.first.at(j) == '\'') {
                if (!string_checker.first) {
                    string_checker.first = true;
                    string_checker.second = i.first.at(j);
                }
                else {
                    if (string_checker.second != i.first.at(j)) {
                        std::cout << "error on line - " << i.second << " \"" << i.first << "\"" << std::endl;
                        return {};
                    }
                    else {
                        if (s.size() > 1) {
                            std::cout << "error on line - " << i.second << " \"" << i.first << "\"" << std::endl;
                            return {};
                        }
                        enlist(tokens, s, "char", i.second);
                        string_checker.first = false;
                        string_checker.second = '0';
                    }
                }
                continue;
            }
            if (string_checker.first) {
                s.push_back(i.first.at(j));
                continue;
            }

            std::set<std::string> match = search_by_ith_char(i.first.at(j), Types::DOUBLE_CHAR_OPERATOR_LIST, 1);
            if (!match.empty()) {
                enlist(tokens, s, "default", i.second);
                if (j + 1 < i.first.size()) {
                    match = search_by_ith_char(i.first.at(j + 1), match, 2);
                    if (!match.empty()) {
                        s.push_back(i.first.at(j));
                        s.push_back(i.first.at(j + 1));
                        enlist(tokens, s, "default", i.second);
                        j += 2;
                    }
                }
                else {
                    j++;
                }
            }
            if (j >= i.first.size()) break;
            if (Types::SEPARATOR.count(std::string(1, i.first.at(j))) || Types::IGNORABLE.count(i.first.at(j))) {
                enlist(tokens, s, "default", i.second);
                if (Types::SEPARATOR.count(std::string(1, i.first.at(j)))) {
                    s.push_back(i.first.at(j));
                }
                enlist(tokens, s, "separator", i.second);
            }
            else {
                s.push_back(i.first.at(j));
            }
        }
        if (string_checker.first) {
            s.push_back('\n');
        }
        else {
            enlist(tokens, s, "default", i.second);
        }
    }
    return tokens;
}

void Tokenizer::enlist(std::vector<Token>& record, std::string& s, const std::string& comment, const int& line_number) {
    if (s.empty()) {
        s.clear();
        return;
    }
    std::string type;
    if (comment == "string" || comment == "char") {
        type = Types::CONSTANTS;
    }
    else if (Types::KEY_WORD_LIST.count(s)) {
        type = Types::KEY_WORD;
    }
    else if (Types::BINARY_OPERATOR_LIST.count(s)) {
        type = Types::BINARY_OPERATOR;
    }
    else if (Types::UNARY_OPERATOR_LIST.count(s)) {
        if (!record.empty()) {
            if (Types::SELF_INCREMENTAL_DECREMENTAL_OPERATOR_LIST.count(s) && record.back().getType() == Types::IDENTIFIER) {
                s = std::string(record.back().getContains()).append(s);
                std::cout << s << std::endl;
                record.pop_back();
                type = Types::EXPRESSION;
            }
            else {
                type = Types::UNARY_OPERATOR;
            }
        }
        else {
            type = Types::UNARY_OPERATOR;
        }
    }
    else {
        if (Utility::is_number(s)) {
            type = Types::CONSTANTS;
        }
        else {
            bool is_identifier{ true };
            if (record.size() >= 2) {
                if (record.back().getContains() == "&" && (record.at(record.size() - 2).getType() == Types::BINARY_OPERATOR || Types::END_OF_EXPRESSION.count(record.at(record.size() - 2).getType()))) {
                    s = std::string("&").append(s);
                    record.pop_back();
                    is_identifier = false;
                }
            }
            else if (record.size() == 1) {
                if (record.back().getContains() == "&") {
                    s = std::string("&").append(s);
                    record.pop_back();
                    is_identifier = false;
                }
            }
            if (!record.empty() && Types::UNARY_OPERATOR_LIST.count(record.back().getContains())) {
                s = std::string(record.back().getContains()).append(s);
                record.pop_back();
                is_identifier = false;
            }
            std::set<std::string> mashup;
            mashup.insert(Types::IDENTIFIER);
            mashup.insert(Types::CONSTANTS);
            for (auto it = record.rbegin(); it != record.rend(); it++) {
                Token temp = *it;
                it++;
                if (temp.getContains() == "*" && it != record.rend() && (!mashup.count(it->getType()) || Types::END_OF_EXPRESSION.count(it->getContains()))) {
                    s = std::string("*").append(s);
                    record.pop_back();
                    is_identifier = false;
                }
                it--;
            }
            if (is_identifier) {
                type = Types::IDENTIFIER;
            }
            else {
                type = Types::EXPRESSION;
            }
        }
    }
    if (comment == "separator") {
        if (Types::PARENTHESIS_LIST.count(s.at(0))) {
            type = Types::PARENTHESIS;
        }
        else if (Types::BINARY_OPERATOR_LIST.count(s)) {
            type = Types::BINARY_OPERATOR;
        }
        else if (Types::UNARY_OPERATOR_LIST.count(s)) {
            type = Types::UNARY_OPERATOR;
        }
    }

    if (type == Types::KEY_WORD && Types::PRIMITIVE_DATA_TYPE_LIST.count(s)) {
        check_data_type(record, s);
    }

    record.emplace_back(s, type, line_number);
    s.clear();
}

void Tokenizer::check_data_type(std::vector<Token>& record, std::string& s) {
    std::set<std::string> long_addable_list{ "int", "long int", "double" };
    std::set<std::string> short_addable_list{ "int" };
    std::set<std::string> signed_or_unsigned_addable_list{ "int", "long int", "short int", "long long int", "char" };

    while (long_addable_list.count(s) || short_addable_list.count(s) || signed_or_unsigned_addable_list.count(s)) {
        if (record.empty()) {
            break;
        }
        if (long_addable_list.count(s) && record.back().getContains() == "long") {
            s = std::string("long ").append(s);
            record.pop_back();
        }
        else if (short_addable_list.count(s) && record.back().getContains() == "short") {
            s = std::string("short ").append(s);
            record.pop_back();
        }
        else if (signed_or_unsigned_addable_list.count(s)) {
            if (record.back().getContains() == "signed") {
                s = std::string("signed ").append(s);
                record.pop_back();
            }
            else if (record.back().getContains() == "unsigned") {
                s = std::string("unsigned ").append(s);
                record.pop_back();
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
}

std::set<std::string> Tokenizer::search_by_ith_char(char c, const std::set<std::string>& record, int index) {
    if (index > 2 || index < 1) return {};
    std::set<std::string> res;
    for (auto& i : record) {
        if (i.at(index - 1) == c) {
            res.insert(i);
        }
    }
    return res;
}