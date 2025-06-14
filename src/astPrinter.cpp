#include <astPrinter.h>

std::string AstPrinter::print(const std::unique_ptr<Expr>& expr) {
  if (auto binary = dynamic_cast<BinaryExpr*>(expr.get())) {
    return parenthesize(binary->op.lexeme, binary->left, binary->right);
  } else if (auto literal = dynamic_cast<LiteralExpr*>(expr.get())) {
    return literal->value;
  } else if (auto variable = dynamic_cast<VariableExpr*>(expr.get())) {
    return variable->name.lexeme;
  } else {
    return "UnknownExpr";
  }
}

std::string AstPrinter::parenthesize(const std::string& name, const std::unique_ptr<Expr>& left, const std::unique_ptr<Expr>& right) {
  return "(" + name + " " + print(left) + " " + print(right) + ")";
}
