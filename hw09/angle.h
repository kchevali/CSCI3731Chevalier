#ifndef ANGLE_H
#define ANGLE_H

#include <iostream>

class Angle {
 public:
  Angle();
  Angle(double value);
  Angle(double value, bool isRad);
  Angle operator+(double value) const;
  Angle operator-(double value) const;
  Angle& operator+=(double value);
  Angle& operator-=(double value);

  Angle operator*(double value) const;
  Angle operator/(double value) const;
  Angle& operator*=(double value);
  Angle& operator/=(double value);
  Angle& operator=(double value);

  bool operator==(double value) const;
  bool operator>=(double value) const;
  bool operator<=(double value) const;
  bool operator>(double value) const;
  bool operator<(double value) const;

  double getCos();
  double getSin();

  operator double() const;

  virtual ~Angle();
  friend std::ostream& operator<<(std::ostream& out, const Angle& c);

 private:
  double EPS = 10e-6;
  Angle& self();
  double value, cos_value, sin_value;
};

#endif
