#pragma once

class Foo
{
public:
  Foo() = default;
  Foo(double f) : f_(f) {}

  void print();

  double f_ = 0;
};