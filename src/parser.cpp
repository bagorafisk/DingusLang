#include <parser.h>
#include <stdexcept>

// === Helper functions ===

bool Parser::match(std::initializer_list<Token::Type> types) {
  for (Token::Type type : types) {
    if(check(type)) {
      advance();
      return true;
    }
  }
  return false;
}

bool Parser::check(Token::Type type) const {
  if (isAtEnd()) return false;
  return peek().type == type;
}

const Token& Parser::advance() {
  if (!isAtEnd()) current++;
  return previous();
}

const Token& Parser::peek() const {
  return tokens[current];
}

const Token& Parser::previous const {
  return tokens[current - 1];
}

bool Parser::isAtEnd() const {
  return peek().type == Token::Type::EndOfFile;
}

const Token& Parser::consume(Token::Type type, const std::string& message) {
  if (check(type)) return advance();
  throw std::runtime_error("Parse error: " + message);
}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
  std::vector<std::unique_ptr<Stmt>> statements;
  while (!isAtEnd()) {
    statements.push_back(statement());
  }
  return statements;
}

std::unique_ptr<Stmt> Parser::statement() {
  if(match({Token::Type::Decl})) return varDeclaration();
  return expressionStatement();
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
  Token name = consume(Token::Type::Identifier, "Expected variable name after 'decl'.");

  consume(Token::Type::Equals, "Expected '=' after a variable name.");

  std::unique_ptr<Expr> initializer = expression();

  consume(Token::Type::Semicolon, "Expected ';' after variable declaration.");

  return std::make_unique<VarDecl>(name, std::move(initializer));
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
  std::unique_ptr<Expr> expr = expression();
  consume(Token::Type::Semicolon, "Expected ';' after expression");
  return std::make_unique<ExprStmt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::expression() {
  return term();
}

std::unique_ptr<Expr> Parser::term() {
  std::unique_ptr<Expr> expr = factor();

  while (match({Token::Type::Plus, Token::Type::Minus})) {
    Token op = previous();
    std::unique_ptr<Expr> right = factor();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::factor() {
  std::unique_ptr<Expr> expr = primary();

  while (match({Token::Type::Star, Token::Type::Slash})) {
    Token op = previous;
    std::unique_ptr<Expr> right = primary();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }

  return expr;
}

std::unique_ptr<Expr> Parser::primary() {
  if (match({Token::Type::Number})) {
    return std::make_unique<LiteralExpr>(previous().lexeme);
  }

  if (match({Token::Type::Identifier})) {
    return std::make_unique<VariableExpr>(previous());
  }

  if (match({Token::Type::LeftParen})) {
    std::unique_ptr<Expr> expr = expression();
    consume(Token::Type::RightParen, "Expected ')' after expression.");
    return expr;
  }

  throw std::runtime_error("Expected expression");
}
