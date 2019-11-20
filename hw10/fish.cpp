#include "fish.h"
#include <QWidget>
#include <QtGui>
#include <cmath>
#include <limits>
#include "main.h"
#include "population.h"

Fish::Fish(Population& pop)
    : pos(ran(0, pop.getWidth()), ran(0, pop.getHeight())),
      vel(this->maxSpeed = ran(1, 5)),
      acc(),
      pop(pop),
      it(this->pop.add(this)) {
  // graphics
  this->width = 20;
  this->height = 5;
  // mechanics
  this->perception = 5000;  // ran(10, 20);
  this->size = ran(3000, 5000);
  this->breedSize = ran(6000, 7500);

  this->id = pop.getNextId();

  for (int i = 0; i < 4; i++) rotPoints.push_back(new Vector(0, 0));
  updateRotPoints();
}
Fish::Fish(Population& pop, double x, double y, int size, double speed,
           int breedSize, int perception)
    : pos(ran(x - 100, x + 100) % pop.getWidth(),
          ran(y - 100, y + 100) % pop.getHeight()),
      vel(this->maxSpeed = std::max(1, ran(speed - 1, speed + 1))),
      acc(),
      pop(pop),
      it(this->pop.add(this)) {
  this->id = -1;
  // graphics
  this->width = 20;
  this->height = 5;

  // mechanics
  this->perception = std::max(0, ran(perception - 500, perception + 500));
  this->size = std::max(100, ran(size - 10, size + 10));
  this->breedSize = ran(breedSize - 500, breedSize + 500);

  this->pop.add(this);
  this->id = pop.getNextId();
  for (int i = 0; i < 4; i++) rotPoints.push_back(new Vector(0, 0));
  updateRotPoints();
}
void Fish::swim() {
  if (size == 0) return;
  pos += vel;
  acc *= 0.5;
  vel += acc;
  vel.limit(maxSpeed);
  acc *= 0;
  // move to other side of screen
  bound();
}

// bound fish to screen by moving to other side
void Fish::bound() {
  int x = getX(), y = getY(), margin = 1;

  if (x < 0.0)
    pos.set(x = pop.getWidth() - margin, y);
  else if (x > pop.getWidth())
    pos.set(x = margin, y);

  if (y < 0.0)
    pos.set(x, pop.getHeight() - margin);
  else if (y > pop.getHeight())
    pos.set(x, margin);
}

void Fish::breed(Fish* mate) {
  if (this->size >= this->breedSize && mate->size >= mate->breedSize &&
      this->isCollide(mate)) {
    this->size /= 2;
    newFish(1, size);
  }
}

// scan one fish for eating
bool Fish::feed(Fish* emy) {
  if (this->size == 0 || emy->size == 0) return false;
  if (this->size > emy->size && this->isCollide(emy)) {
    this->size += emy->size;
    if (this->size > 8000) {
      this->breed(this);
    }
    emy->death();
    return true;
  }
  return false;
}

// shrink fish and return true if alive
bool Fish::shrink() {
  bool ans = (size -= (pop.size() > 250 ? 50 : 5)) > 0;
  if (!ans && pop.size() == 1) {
    newFish(5, 5000);
    newFish(10, 100);
  }
  return ans;
}

// getters
int Fish::getId() const { return id; }
int Fish::getSize() const { return size; }
int Fish::getBreedSize() const { return breedSize; }

double Fish::getX() const { return pos.getX(); }
double Fish::getY() const { return pos.getY(); }
double Fish::getCenterX() const { return pos.getX() + getWidth() / 2; }
double Fish::getCenterY() const { return pos.getY() + getHeight() / 2; }
double Fish::rotX(double dx, double dy) {
  double x = -getWidth() / 2 + dx, y = -getHeight() / 2 + dy;
  double res = x * getDirection().getCos() - y * getDirection().getSin();
  return res + getWidth() / 2 + pos.getX();

  // return (pos.getX() + dx) * getDirection().getCos() -
  //        (pos.getY() + dy) * getDirection().getSin();
}
double Fish::rotY(double dx, double dy) {
  double x = -getWidth() / 2 + dx, y = -getHeight() / 2 + dy;
  double res = y * getDirection().getCos() + x * getDirection().getSin();
  return res + getHeight() / 2 + pos.getY();
  // return (pos.getY() + dy) * getDirection().getCos() +
  //        (pos.getX() + dx) * getDirection().getSin();
}
void Fish::setPos(double x, double y) { pos.set(x, y); }

// rot points are points of rectangle if fish is rotated
void Fish::updateRotPoints() {
  rotPoints[0]->set(rotX(0, 0), rotY(0, 0));
  rotPoints[1]->set(rotX(getWidth(), 0), rotY(getWidth(), 0));
  rotPoints[2]->set(rotX(0, getHeight()), rotY(0, getHeight()));
  rotPoints[3]->set(rotX(getWidth(), getHeight()),
                    rotY(getWidth(), getHeight()));
}

bool Fish::isCollide(Fish* other) {
  // Rot rectangle algorithm
  for (int x = 0; x < 2; x++) {
    std::vector<Vector*>& edges = x == 0 ? this->rotPoints : other->rotPoints;
    for (int i = 0; i < 4; i++) {
      int j = (i + 1) % 4;
      Vector *p1 = edges[i], *p2 = edges[j];
      Vector normal = Vector(p2->getY() - p1->getY(), p1->getX() - p2->getX());
      double minA = std::numeric_limits<double>::infinity();
      double maxA = -std::numeric_limits<double>::infinity();
      double minB = std::numeric_limits<double>::infinity();
      double maxB = -std::numeric_limits<double>::infinity();
      for (Vector* p : this->rotPoints) {
        double projected =
            normal.getX() * p->getX() + normal.getY() * p->getY();
        if (projected < minA) minA = projected;
        if (projected > maxA) maxA = projected;
      }
      for (Vector* p : other->rotPoints) {
        double projected =
            normal.getX() * p->getX() + normal.getY() * p->getY();
        if (projected < minB) minB = projected;
        if (projected > maxB) maxB = projected;
      }

      if (maxA < minB || maxB < minA) return false;
    }
  }
  return true;
}

double Fish::getWidth() const { return width * size / 5000.0; }
double Fish::getHeight() const { return height * size / 5000.0; }
int Fish::getPerception() const { return perception; }

Vector& Fish::getPos() { return pos; }
Vector& Fish::getVel() { return vel; }
Vector& Fish::getAcc() { return acc; }
Angle& Fish::getDirection() { return vel.getAngle(); }

void Fish::death() { size = 0; }
Population& Fish::getPop() const { return pop; }

void Fish::display(QPainter& painter) {
  QRect rect = QRect(getX(), getY(), getWidth(), getHeight());
  QTransform t = QTransform()
                     .translate(getCenterX(), getCenterY())
                     .rotate(getDirection())
                     .translate(-getCenterX(), -getCenterY());
  QPolygon rotatedRect = t.mapToPolygon(rect);
  painter.drawConvexPolygon(rotatedRect);
}

// comparsion
bool Fish::operator==(Fish& that) const { return this->id == that.id; }

// printable
std::ostream& operator<<(std::ostream& out, const Fish& c) {
  out << c.id;
  return out;
}
Fish::~Fish() {
  pop.remove(this->it);
  for (int i = 0; i < 4; i++) delete rotPoints[i];
}