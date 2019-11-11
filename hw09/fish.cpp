#include "fish.h"
#include <cmath>
#include <limits>
#include "main.h"
#include "population.h"

Fish::Fish(Population& pop)
    : pos(ran(0, pop.getWidth()), ran(0, pop.getHeight())),
      vel(this->maxSpeed = ran(1, 5)),
      acc(),
      pop(&pop) {
  this->id = -1;
  // graphics
  this->width = 20;
  this->height = 5;

  // mechanics

  this->size = ran(3000, 5000);
  this->breedSize = ran(6000, 7500);

  // linked list var
  this->next = nullptr;
  this->prev = nullptr;

  this->pop->add(*this);
  this->id = pop.getHistory() - 1;

  for (int i = 0; i < 4; i++) rotPoints.push_back(new Vector(0, 0));
  updateRotPoints();
}
Fish::Fish(Population& pop, double x, double y, int size, double speed,
           int breedSize)
    : pos(ran(x - 100, x + 100) % pop.getWidth(),
          ran(y - 100, y + 100) % pop.getHeight()),
      vel(this->maxSpeed = std::max(1, ran(speed - 1, speed + 1))),
      acc(),
      pop(&pop) {
  this->id = -1;
  // graphics
  this->width = 20;
  this->height = 5;

  // mechanics
  this->size = std::max(100, ran(size - 10, size + 10));
  this->breedSize = ran(breedSize - 500, breedSize + 500);

  // linked list var
  this->next = nullptr;
  this->prev = nullptr;

  this->pop->add(*this);
  this->id = pop.getHistory() - 1;
  for (int i = 0; i < 4; i++) rotPoints.push_back(new Vector(0, 0));
  updateRotPoints();
}
void Fish::swim() {
  if (size == 0) return;
  pos += vel;
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
    pos.set(x = pop->getWidth() - margin, y);
  else if (x > pop->getWidth())
    pos.set(x = margin, y);

  if (y < 0.0)
    pos.set(x, pop->getHeight() - margin);
  else if (y > pop->getHeight())
    pos.set(x, margin);
}

void Fish::breed(Fish& mate) {
  if (this->size >= this->breedSize && mate.size >= mate.breedSize &&
      this->isCollide(mate)) {
    this->size /= 2;
    newFish(1, size / 2);
  }
}

// scan population for  fish to eat
void Fish::feed(Population& other) {
  if (size == 0) return;

  Fish* emy = &other.first();
  while (emy != nullptr) {
    this->feed(*emy);
    emy->feed(*this);
    emy = emy->getNext();
  }
}

// scan one fish for eating
void Fish::feed(Fish& emy) {
  if (emy.size == 0) return;
  if (this->size > emy.size && this->isCollide(emy)) {
    this->size += emy.size;
    if (this->size > 8000) {
      this->breed(*this);
    }
    emy.death();
  }
}

// shrink fish and return true if alive
bool Fish::shrink() {
  bool ans = (size -= (pop->size() > 50 ? 10 : 1)) > 0;
  if (!ans && pop->size() == 1) {
    newFish(10, 5000);
    newFish(5, 100);
  }
  return ans;
}

// getters
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

bool Fish::isCollide(Fish& other) {
  // Rot rectangle algorithm
  for (int x = 0; x < 2; x++) {
    std::vector<Vector*>& edges = x == 0 ? this->rotPoints : other.rotPoints;
    for (int i = 0; i < 4; i++) {
      int j = (i + 1) % 4;
      Vector *p1 = edges[i], *p2 = edges[j];
      Vector normal = Vector(p2->getY() - p1->getY(), p1->getX() - p2->getX());
      double minA = std::numeric_limits<float>::infinity();
      double maxA = -std::numeric_limits<float>::infinity();
      double minB = std::numeric_limits<float>::infinity();
      double maxB = -std::numeric_limits<float>::infinity();
      for (Vector* p : this->rotPoints) {
        double projected =
            normal.getX() * p->getX() + normal.getY() * p->getY();
        if (projected < minA) minA = projected;
        if (projected > maxA) maxA = projected;
      }
      for (Vector* p : other.rotPoints) {
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

Vector& Fish::getPos() { return pos; }
Vector& Fish::getVel() { return vel; }
Vector& Fish::getAcc() { return acc; }
Angle& Fish::getDirection() { return vel.getAngle(); }

void Fish::death() { size = 0; }

bool Fish::hasPopulation() { return id >= 0; }
void Fish::setNext(Fish* next) { this->next = next; }
Fish* Fish::getNext() const { return next; }
void Fish::setPrev(Fish* prev) { this->prev = prev; }
Fish* Fish::getPrev() const { return prev; }
Population& Fish::getPop() const { return *pop; }

// move fish to another population
void Fish::setPop(Population& pop) {
  this->pop->remove(*this);
  int id = this->id;
  this->id = -1;
  pop.add(*this);
  this->id = *(this->pop) != pop ? pop.getHistory() - 1 : id;
  this->pop = &pop;
}

// comparsion
bool Fish::operator==(Fish& that) const { return this->id == that.id; }

// printable
std::ostream& operator<<(std::ostream& out, const Fish& c) {
  out << c.id;
  return out;
}
Fish::~Fish() {
  pop->remove(*this);
  for (int i = 0; i < 4; i++) delete rotPoints[i];
}