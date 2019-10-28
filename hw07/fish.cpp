#include "fish.h"
#include <cmath>
#include <cstdlib>
#include <limits>
#include "population.h"

Fish::Fish(Population& pop, int x, int y, double direction)
    : direction(direction == -1 ? rand() % 360 : direction),
      turn(4),
      pop(&pop) {
  this->id = -1;

  // position
  this->x = x == -1 ? rand() % pop.getWidth() : x;
  this->y = y == -1 ? rand() % pop.getHeight() : y;

  // graphics
  this->width = 100;
  this->height = 20;

  // mechanics
  this->size = 400 + rand() % 100;
  this->speed = pop.getSpeed();
  this->perception = 10000.0;
  this->feedRadius = 100.0;

  // linked list var
  this->next = nullptr;
  this->prev = nullptr;

  // tracking vars
  this->target = nullptr;
  this->targetDist = std::numeric_limits<double>::infinity();
  this->pop->add(*this);
  this->id = pop.getHistory() - 1;
}

void Fish::swim() {
  // can't swim if dead
  if (size == 0) return;
  int choice;

  if (target == nullptr) {
    // random
    choice = rand() % 3;
  } else {
    // tracking
    double dx = target->x - x, dy = target->y - y;
    if (dx == 0) {
      // fish is straight above/below
      double sx = direction.getCos(), sy = direction.getSin();
      choice = sx * dy < 0 ? 0 : 2;
    } else {
      // normal tracking
      Angle ang = Angle(tan(dy / dx), true);
      if (dx < 0) ang += 180.0;
      ang = direction - ang;
      double sx = ang.getCos(), sy = ang.getSin();
      choice = sy > 0 ? 0 : 2;
    }
  }

  // make choice
  if (choice == 0)
    direction -= turn;
  else if (choice == 2)
    direction += turn;

  // move
  x += speed * direction.getCos();
  y += speed * direction.getSin();

  // move to other side of screen
  bound();
  // reset targeting
  target = nullptr;
  targetDist = std::numeric_limits<double>::infinity();
}

// bound fish to screen by moving to other side
void Fish::bound() {
  if (x < 0.0)
    x = pop->getWidth() - 10;
  else if (x > pop->getWidth())
    x = 10;

  if (y < 0.0)
    y = pop->getHeight() - 10;
  else if (y > pop->getHeight())
    y = 10;
}

// scan population for closest fish
void Fish::scan(Population& other) {
  if (size == 0) return;
  Fish* emy = &other.first();
  while (emy != nullptr) {
    this->scan(*emy);
    emy->scan(*this);
    emy = emy->getNext();
  }
}

// scan one fish for targeting/eating
void Fish::scan(Fish& emy) {
  if (emy.size == 0) return;
  if (this->size > emy.size) {
    double dx = this->x - emy.x, dy = this->y - emy.y;
    double dist = dx * dx + dy * dy;
    double t = std::min(targetDist, perception);
    // std::cout << "D: " << dx << " " << dy << " " << t << "\n";
    if (dist < t) {
      targetDist = dist;
      target = &emy;
    }
  }
}

// fish is currently tracking another
bool Fish::hasTarget() const { return target != nullptr; }

// eat a fish if possible
void Fish::feed() {
  if (size == 0 || targetDist > feedRadius) {
    return;
  }
  // target != nullptr if targetDist < inf
  this->size = std::min(1000, this->size + target->size);

  target->death();
}

// shrink fish and return true if alive
bool Fish::shrink() {
  bool ans = (size -= speed) > 0;
  return ans;
}

// getters
int Fish::getSize() const { return size; }
double Fish::getX() const { return x; }
double Fish::getY() const { return y; }
int Fish::getWidth() const { return width; }
int Fish::getHeight() const { return height; }
double Fish::getDirection() const { return direction; }
double Fish::getPerception() const { return perception; }
double Fish::getFeedRadius() const { return feedRadius; }

void Fish::death() {
  size = 0;
  speed = 0;
}

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
Fish::~Fish() { pop->remove(*this); }