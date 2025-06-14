#include <lexer.h>

bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

std::string toString(Token::Type type) {
  switch (type) {
    case Token::Type::Let: return "Let";
    case Token::Type::Print: return "Print";
    case Token::Type::Identifier: return "Identifier";
    case Token::Type::Number: return "Number";
    case Token::Type::Equals: return "Equals";
    case Token::Type::Plus: return "Plus";
    case Token::Type::Minus: return "Minus";
    case Token::Type::Star: return "Star";
    case Token::Type::Slash: return "Slash";
    case Token::Type::LeftParen: return "LeftParen";
    case Token::Type::RightParen: return "RightParen";
    case Token::Type::Semicolon: return "Semicolon";
    case Token::Type::EndOfFile: return "EndOfFile";
    case Token::Type::Unknown: return "Unknown";
  }
}

std::vector<Token> tokenize(const std::string& source) {
    std::vector<Token> tokens;

    int i = 0;
    
    while(i < source.size()) {
      char c = source[i];

      if (std::isspace(c)) {
          i++;
          continue;
      }

      if (isAlpha(c)) {
        size_t start = i;
        while (i < source.size() && (isAlpha(source[i]) || isDigit(source[i]))) i++;
        std::string word = source.substr(start, i - start);
        if (word == "let") {
            tokens.push_back({Token::Type::Let, word});
        } else if (word == "print") {
            tokens.push_back({Token::Type::Print, word});
        } else {
            tokens.push_back({Token::Type::Identifier, word});
        }
      } else if (isDigit(c)) {
        size_t start = i;
        while (i < source.size() && isDigit(source[i])) i++;
        tokens.push_back({Token::Type::Number, source.substr(start, i - start)});
      } else {
        switch (c) {
          case '=': tokens.push_back({Token::Type::Equals, "="}); break;
          case '+': tokens.push_back({Token::Type::Plus, "+"}); break;
          case '-': tokens.push_back({Token::Type::Minus, "-"}); break;
          case '*': tokens.push_back({Token::Type::Star, "*"}); break;
          case '/': tokens.push_back({Token::Type::Slash, "/"}); break;
          case '(': tokens.push_back({Token::Type::LeftParen, "("}); break;
          case ')': tokens.push_back({Token::Type::RightParen, ")"}); break;
          case ';': tokens.push_back({Token::Type::Semicolon, ";"}); break;
          default:
            tokens.push_back({Token::Type::Unknown, std::string(1, c)});
            break;
        }
        i++;
      }
    }
    
    tokens.push_back({Token::Type::EndOfFile, ""});
    return tokens;
}
