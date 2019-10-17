#ifndef ANGLE_H
#define ANGLE_H

#include <iostream>

class Angle {
 public:
  Angle();
  Angle(double value);
  Angle operator+(const double value) const;
  Angle operator-(const double value) const;
  Angle& operator+=(const double value);
  Angle& operator-=(const double value);

  Angle operator*(const double value) const;
  Angle operator/(const double value) const;
  Angle& operator*=(const double value);
  Angle& operator/=(const double value);
  Angle& operator=(const double value);

  bool operator==(const double value) const;
  bool operator>=(const double value) const;
  bool operator<=(const double value) const;
  bool operator>(const double value) const;
  bool operator<(const double value) const;

  static void test_comp_op(Angle& a, Angle& b);
  static void test_op(Angle& a, Angle& b);
  Angle rad() const;

  operator double() const;

  virtual ~Angle();
  friend std::ostream& operator<<(std::ostream& out, const Angle& c);

 private:
  double EPS = 10e-6;
  Angle& self();
  double value;
};

#endif
