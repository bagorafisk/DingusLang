#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <string>
#include <memory>
#include <expr.h>

class AstPrinter {
public:
  std::string print(const std::unique_ptr<Expr>& expr);

private:
  std::string parenthesize(const std::string& name, const std::unique_ptr<Expr>& left, const std::unique_ptr<Expr>& left);
};

#endif
