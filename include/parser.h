#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <Token.h>
#include <Expr.h>

class Parser {
public:
  explicit Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {}

  std::vector<std::unique_ptr<Stmt>> parse();

private:
  const std::vector<Token>& tokens;
  size_t current;
  
  // Statement parsing
  std::unique_ptr<Stmt> statement();
  std::unique_ptr<Stmt> varDeclaration();
  std::unique_ptr<Stmt> expressionStatement();
  
  //Expression parsing
  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> term();
  std::unique_ptr<Expr> factor();
  std::unique_ptr<Expr> primary();

  // Helpers
  bool match(std::initializer_list<Token::Type> types);
  bool check(Token::Type type) const;
  const Token& advance();
  const Token& peek() const;
  const Token& previous() const;
  bool isAtEnd() const;
  const Token& consume(Token::Type type, const std::string& message);
}

#endif
