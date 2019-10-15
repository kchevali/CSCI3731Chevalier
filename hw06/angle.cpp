#include "angle.h"
#include <math.h>

// create angle
Angle::Angle() { value = 0.0; }

Angle::Angle(double value) {
  this->value = value;
  *this = self();
}

// basic operators
Angle Angle::operator+(const double value) const {
  return Angle(this->value + value);
}
Angle Angle::operator-(const double value) const {
  return Angle(this->value - value);
}
Angle& Angle::operator+=(const double value) {
  this->value += value;
  return self();
}
Angle& Angle::operator-=(const double value) {
  this->value -= value;
  return self();
}

Angle Angle::operator*(const double value) const {
  return Angle(this->value * value);
}
Angle Angle::operator/(const double value) const {
  return Angle(this->value / value);
}
Angle& Angle::operator*=(const double value) {
  this->value *= value;
  return self();
}
Angle& Angle::operator/=(const double value) {
  this->value /= value;
  return self();
}
Angle& Angle::operator=(const double value) {
  this->value = value;
  return self();
}

// comparative operators
bool Angle::operator==(const double value) const {
  return fabs(this->value - value) < EPS;
}
bool Angle::operator>=(const double value) const {
  return this->value - value > -EPS;
}
bool Angle::operator<=(const double value) const {
  return this->value - value < EPS;
}
bool Angle::operator>(const double value) const {
  return this->value - value > EPS;
}
bool Angle::operator<(const double value) const {
  return this->value - value < -EPS;
}

// cast angle to double
Angle::operator double() const { return this->value; }

// constrain angle to [0.0,360.0)
Angle& Angle::self() {
  while (*this >= 360.0) value -= 360.0;
  while (*this < 0.0) value += 360.0;
  return *this;
}

// degrees to radian
Angle Angle::rad() const { return Angle(value * acos(-1.0) / 180.0); }
Angle::~Angle() {}

// printable angle
std::ostream& operator<<(std::ostream& out, const Angle& c) {
  out << c.value;
  return out;
}

// test the comparative operations
void Angle::test_comp_op(Angle& a, Angle& b) {
  std::cout << a << " == " << b << " = " << (a == b) << std::endl;
  std::cout << a << " < " << b << " = " << (a < b) << std::endl;
  std::cout << a << " > " << b << " = " << (a > b) << std::endl;
  std::cout << a << " >= " << b << " = " << (a >= b) << std::endl;
  std::cout << a << " <= " << b << " = " << (a <= b) << std::endl << std::endl;
}

// test all operations
void Angle::test_op(Angle& a, Angle& b) {
  Angle c = a;
  std::cout << a << " + " << b << " = " << (a + b) << std::endl;
  std::cout << a << " - " << b << " = " << (a - b) << std::endl;
  std::cout << a << " * " << b << " = " << (a * b) << std::endl;
  std::cout << a << " / " << b << " = " << (a / b) << std::endl << std::endl;

  std::cout << a << " += " << b << " = " << (a += b) << std::endl;
  std::cout << a << " -= " << b << " = " << (a -= b) << std::endl;
  std::cout << a << " *= " << b << " = " << (a *= b) << std::endl;
  std::cout << a << " /= " << b << " = " << (a /= b) << std::endl << std::endl;
  a = c;
  test_comp_op(a, b);
  test_comp_op(b, a);
  test_comp_op(a, c);
}