#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "angle.h"

class Vector {
 public:
  Vector();
  Vector(double x, double y);
  Vector(double mag);
  void updateXY();
  void updatePolar();
  double getX() const;
  double getY() const;
  Angle<double>& getAngle();
  double getMag() const;
  double getMagSq() const;
  void limit(double maxMag);
  void set(double x, double y);
  void setMag(double mag);
  void setAngle(double mag);
  void normalize();
  void turn(double angle);
  double distSq(Vector& position);
  Vector operator+(const Vector& that) const;
  Vector operator-(const Vector& that) const;
  Vector& operator+=(const Vector& that);
  Vector& operator-=(const Vector& that);
  Vector& operator*=(double value);
  Vector& operator/=(double value);
  Vector& operator=(const Vector& that);

  virtual ~Vector();
  friend std::ostream& operator<<(std::ostream& out, const Vector& c);

 private:
  double EPS = 10e-6;
  Angle<double> angle;
  double x, y, mag;
};

#endif
