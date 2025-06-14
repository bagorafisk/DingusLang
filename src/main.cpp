#include <lexer.h>
#include <parser.h>
#include <AstPrinter.h>

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

    Parser parser(tokens);
    std::vector<std::unique_ptr<Stmt>> statements = parser.parse();

    AstPrinter printer;

    for (const auto& stmt : statements) {
      if (auto var = dynamic_cast<VariableStmt*>(stmt.get())) {
        std::cout << "Decl: " << var->name.lexeme << " = " << printer.print(var->initializer) << std::endl;
      } else if (auto exprStmt = dynamic_cast<ExprStmt>(stmt.get())) {
        std::cout << "ExprStmt: " << printer.print(exprStmt->expression) << std::endl;
      }
    }

    return 0;
}
