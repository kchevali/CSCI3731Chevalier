#include "vector.h"
#include <cmath>

// create angle
Vector::Vector() {
  x = 0.0;
  y = 0.0;
  updatePolar();
}

Vector::Vector(double x, double y) {
  this->x = x;
  this->y = y;
  updatePolar();
}

Vector::Vector(double mag) : angle(rand() % 360) {
  this->mag = mag;
  updateXY();
}

void Vector::updateXY() {
  x = mag * angle.getCos();
  y = mag * angle.getSin();
}

void Vector::updatePolar() {
  mag = sqrt(x * x + y * y);
  if (fabs(x) < EPS)
    angle = y > 0 ? 90 : 270;
  else
    angle = 180 * atan(y / x) / M_PI + (x < 0 ? 180 : 0);
}

double Vector::getX() const { return x; }
double Vector::getY() const { return y; }
Angle& Vector::getAngle() { return angle; }
double Vector::getMag() const { return mag; }

double Vector::getMagSq() const { return mag * mag; }

void Vector::setMag(double mag) {
  this->mag = mag;
  updateXY();
}

void Vector::limit(double maxMag) {
  this->mag = std::min(this->mag, maxMag);
  updateXY();
}

void Vector::setAngle(double angle) {
  this->angle = angle;
  updateXY();
}

void Vector::turn(double angle) {
  this->angle += angle;
  updateXY();
}

void Vector::set(double x, double y) {
  this->x = x;
  this->y = y;
  updatePolar();
}

// basic operators
Vector Vector::operator+(const Vector& that) const {
  return Vector(this->x + that.x, this->y + that.y);
}
Vector Vector::operator-(const Vector& that) const {
  return Vector(this->x - that.x, this->y - that.y);
}
Vector& Vector::operator+=(const Vector& that) {
  this->x += that.x;
  this->y += that.y;
  this->updatePolar();
  return *this;
}
Vector& Vector::operator-=(const Vector& that) {
  this->x -= that.x;
  this->y -= that.y;
  updatePolar();
  return *this;
}

Vector& Vector::operator*=(double value) {
  mag *= value;
  updateXY();
  return *this;
}

Vector& Vector::operator/=(double value) {
  mag /= value;
  updateXY();
  return *this;
}

Vector& Vector::operator=(const Vector& that) {
  this->x = that.x;
  this->y = that.y;
  this->angle = that.angle;
  this->mag = that.angle;
  return *this;
}

// comparative operators
// bool Vector::operator==(Vecto) const {
//   return fabs(this->value - value) < EPS;
// }
// bool Vector::operator>=(double value) const {
//   return this->value - value > -EPS;
// }
// bool Vector::operator<=(double value) const {
//   return this->value - value < EPS;
// }
// bool Vector::operator>(double value) const { return this->value - value >
// EPS; } bool Vector::operator<(double value) const {
//   return this->value - value < -EPS;
// }

Vector::~Vector() {}

// printable angle
std::ostream& operator<<(std::ostream& out, const Vector& c) {
  // out << "(" << c.x << ", " << c.y << ") " << c.angle << " deg M: " << c.mag;
  out << "(" << c.x << ", " << c.y << ") ";

  return out;
}