#ifndef TOKEN_H
#define TOKEN_H

struct Token {
  enum class Type {
    // Keywords
    Decl,
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


#endif
