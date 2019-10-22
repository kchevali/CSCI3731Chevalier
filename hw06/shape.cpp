#include "shape.h"
#include <math.h>
#include <algorithm>
#include <utility>
#include "angle.h"
#include "image.h"

// create shape
Shape::Shape(double x, double y, const int sides, double length,
             const Angle& rot) {
  move(x, y, rot);
  this->length = length;
  this->delta = 360.0 / sides;
}

// set origin and rotation
void Shape::move(double x, double y, const Angle& rot) {
  this->x = x;
  this->y = y;
  this->rot = rot;
}

// draw shape from polar coordinates to image
void Shape::draw(Image& canvas) const {
  auto prev =
      std::make_pair(cos(rot.rad()) * length + x, sin(rot.rad()) * length + y);
  auto first = prev;
  for (Angle i = delta + rot; i != rot; i += delta) {
    auto curr =
        std::make_pair(cos(i.rad()) * length + x, sin(i.rad()) * length + y);
    canvas.drawLine(prev, curr);
    prev = curr;
  }
  canvas.drawLine(prev, first);
}

// draw shape multiple times in a ring
void Shape::drawRing(Image& canvas, Angle& ringDelta, double ringRadius) {
  move(cos(0.0) * ringRadius, sin(0.0) * ringRadius, 0.0);
  draw(canvas);
  for (Angle i = ringDelta; i != 0.0; i += ringDelta) {
    move(cos(i.rad()) * ringRadius, sin(i.rad()) * ringRadius, i);
    draw(canvas);
  }
}
Shape::~Shape() {}
