#include "angle.h"
#include "image.h"

class Shape {
 public:
  Shape(double x, double y, const int sides, double length, const Angle& rot);
  void move(double x, double y, const Angle& rot);
  void draw(Image& canvas) const;
  void drawRing(Image& canvas, Angle& ringDelta, double ringRadius);
  virtual ~Shape();

 private:
  double x, y, length;
  Angle rot, delta;
};