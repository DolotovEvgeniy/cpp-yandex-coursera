#include "Common.h"

#include <memory>
#include <string>

namespace Expressions {

class Value : public Expression {
public:
  Value(int value)
    : value_(value)
  {}

  int Evaluate() const override {
    return value_;
  }

  std::string ToString() const override {
    return std::to_string(value_);
  }

private:
  int value_;
};

class BinaryOp : public Expression {
public:
  BinaryOp(ExpressionPtr lhs, ExpressionPtr rhs)
    : lhs_(move(lhs))
    , rhs_(move(rhs))
  {}


  int Evaluate() const override {
    return Process(lhs_->Evaluate(), rhs_->Evaluate());
  }

  std::string ToString() const override {
    return "(" + lhs_->ToString() + ")" + opName() + "(" + rhs_->ToString() + ")";
  }

protected:
  virtual int Process(int lhs, int rhs) const = 0;
  virtual std::string opName() const = 0;
private:
  ExpressionPtr lhs_;
  ExpressionPtr rhs_;
};

class Sum : public BinaryOp {
public:
  Sum(ExpressionPtr lhs, ExpressionPtr rhs)
    : BinaryOp(move(lhs), move(rhs))
  {}

private:
  int Process(int lhs, int rhs) const override {
    return lhs + rhs;
  }

  std::string opName() const override {
    return "+";
  }
};

class Product : public BinaryOp {
public:
  Product(ExpressionPtr lhs, ExpressionPtr rhs)
    : BinaryOp(move(lhs), move(rhs))
  {}

private:
  int Process(int lhs, int rhs) const override {
    return lhs * rhs;
  }

  std::string opName() const override {
    return "*";
  }
};

}

// Функции для формирования выражения
ExpressionPtr Value(int value) {
  return std::make_unique<Expressions::Value>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
  return std::make_unique<Expressions::Sum>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
  return std::make_unique<Expressions::Product>(move(left), move(right));
}
