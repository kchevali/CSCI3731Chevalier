#include "angle.h"
#include "image.h"

class Shape {
 public:
  Shape(const double x, const double y, const int sides, const double length,
        const Angle& rot);
  void move(const double x, const double y, const Angle& rot);
  void draw(Image& canvas) const;
  void drawRing(Image& canvas, Angle& ringDelta, double ringRadius);
  virtual ~Shape();

 private:
  double x, y, length;
  Angle rot, delta;
};