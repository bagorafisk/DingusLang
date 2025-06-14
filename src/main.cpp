#include <lexer.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    std::vector<Token> tokens = tokenize(source);

    for (const auto& token : tokens) {
      std::cout << "Token: " << token.lexeme << " Type: " << toString(token.type) << std::endl;
    }

    return 0;
}
