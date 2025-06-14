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
