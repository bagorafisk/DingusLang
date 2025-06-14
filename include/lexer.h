#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <cctype>
#include <optional>
#include <vector>
#include <fstream>
#include <sstream>
#include <token.h>

std::vector<Token> tokenize(const std::string& source);
bool isDigit(char c);
bool isAlpha(char c);
std::string toString(Token::Type type);

#endif
