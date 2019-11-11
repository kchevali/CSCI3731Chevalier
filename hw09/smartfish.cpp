#include "smartfish.h"
#include "fish.h"
#include "main.h"
#include "population.h"
#include "vector.h"

SmartFish::SmartFish(Population& pop, double x, double y, int size,
                     double speed, int perception, int breedSize,
                     std::vector<Population*>& pops)
    : Fish(pop, x, y, size, speed, breedSize), pops(pops) {
  this->perception = std::max(0, ran(perception - 500, perception + 500));
}
SmartFish::SmartFish(Population& pop, std::vector<Population*>& pops)
    : Fish(pop), pops(pops) {
  this->perception = 5000;  // ran(10, 20);
}

// attract/repulse self to another fish based on size
void SmartFish::attract(Vector& position, bool reverse, double constant) {
  Vector force = reverse ? this->pos - position : position - this->pos;
  double dirSq = constrain(force.getMagSq(), 25, 100);
  double strength = constant / dirSq;
  force.setMag(strength);
  acc += force;
}

// check if fish is in range
bool SmartFish::inRange(Vector& position) {
  double dx = getX() - position.getX(), dy = getY() - position.getY();
  return dx * dx + dy * dy <= perception;
}

// update velocities/accelerations
void SmartFish::update() {
  for (Population* other : this->pops) {
    if (other != this->pop) {
      Fish* emy = &other->first();
      while (emy != nullptr) {
        if (this->inRange(emy->getPos()))
          attract(emy->getPos(), emy->getSize() >= this->getSize(), 100);
        emy = emy->getNext();
      }
    }
  }
  // adjust rot points for collision detecting
  updateRotPoints();
}

bool SmartFish::breed(Fish& mate) {
  if (Fish::breed(mate)) {
    newFish(1, size / 2);
    return true;
  }
  return false;
}

void SmartFish::newFish(int count, int size) const {
  for (int i = 0; i < count; i++) {
    new SmartFish(*pop, getX(), getY(), size, vel.getMag(), perception,
                  breedSize, pops);
  }
}

int SmartFish::getPerception() const { return perception; }

SmartFish::~SmartFish() {}