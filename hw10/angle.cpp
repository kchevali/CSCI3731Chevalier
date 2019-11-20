#include "angle.h"
#include <cmath>

// create angle
Angle::Angle() { value = 0.0; }

Angle::Angle(double value) {
  this->value = value;
  *this = self();
}

Angle::Angle(double value, bool isRad) {
  this->value = isRad ? 180.0 * value / M_PI : value;
  *this = self();
}

// basic operators
Angle Angle::operator+(double value) const {
  return Angle(this->value + value);
}
Angle Angle::operator-(double value) const {
  return Angle(this->value - value);
}
Angle& Angle::operator+=(double value) {
  this->value += value;
  return self();
}
Angle& Angle::operator-=(double value) {
  this->value -= value;
  return self();
}

Angle Angle::operator*(double value) const {
  return Angle(this->value * value);
}
Angle Angle::operator/(double value) const {
  return Angle(this->value / value);
}
Angle& Angle::operator*=(double value) {
  this->value *= value;
  return self();
}
Angle& Angle::operator/=(double value) {
  this->value /= value;
  return self();
}
Angle& Angle::operator=(double value) {
  this->value = value;
  return self();
}

// comparative operators
bool Angle::operator==(double value) const {
  return fabs(this->value - value) < EPS;
}
bool Angle::operator>=(double value) const {
  return this->value - value > -EPS;
}
bool Angle::operator<=(double value) const { return this->value - value < EPS; }
bool Angle::operator>(double value) const { return this->value - value > EPS; }
bool Angle::operator<(double value) const { return this->value - value < -EPS; }

// cast angle to double
Angle::operator double() const { return this->value; }

// constrain angle to [0.0,360.0)
Angle& Angle::self() {
  while (*this >= 360.0) value -= 360.0;
  while (*this < 0.0) value += 360.0;
  cos_value = 2;
  sin_value = 2;
  return *this;
}

// trig functions
double Angle::getCos() {
  return cos_value == 2 ? (cos_value = cos(value * M_PI / 180.0)) : cos_value;
}
double Angle::getSin() {
  return sin_value == 2 ? (sin_value = sin(value * M_PI / 180.0)) : sin_value;
}
Angle::~Angle() {}

// printable angle
std::ostream& operator<<(std::ostream& out, const Angle& c) {
  out << c.value;
  return out;
}