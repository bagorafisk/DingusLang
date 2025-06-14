#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include <memory>
#include <token.h>

struct Expr {
  virtual ~Expr() = default;
};

struct LiteralExpr : Expr {
  double value;
  LiteralExpr(double val) : value(val) {}
};

struct VariableExpr : Expr {
  Token name;
  VariableExpr(const Token& name) : name(name) {}
};

struct BinaryExpr : Expr {
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr> l, Token o, std::unique_ptr<Expr> r)
    : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}
};

struct CallExpr : Expr {
  std::string callee;
  std::vector<std::unique_ptr<Expr>> arguments;

  CallExpr(std::string callee, std::vector<<std::unique_ptr<Expr>> args)
    : callee(std::move(callee)), arguments(std::move(args)) {}
};

#endif
