#ifndef ANGLE_H
#define ANGLE_H

#include <cmath>
#include <iostream>

template <class T>
class Angle {
 public:
  Angle() { value = 0.0; }
  Angle(T value) {
    this->value = value;
    *this = self();
  }
  Angle(T value, bool isRad) {
    this->value = isRad ? 180.0 * value / M_PI : value;
    *this = self();
  }
  Angle operator+(T value) const { return Angle(this->value + value); }
  Angle operator-(T value) const { return Angle(this->value - value); }
  Angle& operator+=(T value) {
    this->value += value;
    return self();
  }
  Angle& operator-=(T value) {
    this->value -= value;
    return self();
  }

  Angle operator*(T value) const { return Angle(this->value * value); }
  Angle operator/(T value) const { return Angle(this->value / value); }
  Angle& operator*=(T value) {
    this->value *= value;
    return self();
  }
  Angle& operator/=(T value) {
    this->value /= value;
    return self();
  }
  Angle& operator=(T value) {
    this->value = value;
    return self();
  }

  bool operator==(T value) const { return fabs(this->value - value) < EPS; }
  bool operator>=(T value) const { return this->value - value > -EPS; }
  bool operator<=(T value) const { return this->value - value < EPS; }
  bool operator>(T value) const { return this->value - value > EPS; }
  bool operator<(T value) const { return this->value - value < -EPS; }

  double getCos() {
    return cos_value == 2 ? (cos_value = cos(value * M_PI / 180.0)) : cos_value;
  }
  double getSin() {
    return sin_value == 2 ? (sin_value = sin(value * M_PI / 180.0)) : sin_value;
  }

  operator T() const { return value; }

  virtual ~Angle() {}
  friend std::ostream& operator<<(std::ostream& out, const Angle& c) {
    out << c.value;
    return out;
  }

 private:
  double EPS = 10e-6;
  Angle& self() {
    while (*this >= 360.0) value -= 360.0;
    while (*this < 0.0) value += 360.0;
    cos_value = 2;
    sin_value = 2;
    return *this;
  }
  T value;
  double cos_value, sin_value;
};

#endif
