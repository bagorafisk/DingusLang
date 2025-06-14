#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <cctype>
#include <optional>
#include <vector>
#include <fstream>
#include <sstream>

struct Token {
  enum class Type {
    // Keywords
    Let,
    Print,
    
    // Literals
    Identifier,
    Number,

    // Operators
    Equals,
    Plus,
    Minus,
    Star,
    Slash,

    // Symbols
    LeftParen,
    RightParen,
    Semicolon,

    // Control
    EndOfFile,
    Unknown
  };

  Type type;

  std::string lexeme;
};

std::vector<Token> tokenize(const std::string& source);
bool isDigit(char c);
bool isAlpha(char c);
std::string toString(Token::Type type);

#endif
