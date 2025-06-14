#ifndef STMT_H
#define STMT_H

#include <string>
#include <memory>
#include <expr.h>

struct Stmt {
  virtual ~Stmt() = default;
};

struct VarDecl : Stmt {
  std::string name;
  std::unique_ptr<Expr> initializer;

  VarDecl(std::string name, std::unique_ptr<Expr> init)
    : name(std::move(name)), initializer(std::move(init)) {}
};

struct ExprStmt : Stmt {
  std::unique_ptr<Expr> expression;

  ExprStmt(std::unique_ptr<Expr> expr)
    : expression(std::move(expr)) {}
};

#endif
