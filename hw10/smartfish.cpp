#include "smartfish.h"
#include "fish.h"
#include "main.h"
#include "population.h"
#include "vector.h"

SmartFish::SmartFish(Population& pop, double x, double y, int size,
                     double speed, int breedSize, int perception,
                     std::vector<Population*>& pops)
    : Fish(pop, x, y, size, speed, breedSize,perception), pops(pops) {
}
SmartFish::SmartFish(Population& pop, std::vector<Population*>& pops)
    : Fish(pop), pops(pops) {
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
    if (*other != this->pop) {
      for (auto it = other->begin(); it != other->end(); it++) {
        Fish* emy = *it;
        if (this->inRange(emy->getPos()))
          attract(emy->getPos(), emy->getSize() >= this->getSize(), 100);
      }
    }
  }
  // adjust rot points for collision detecting
  updateRotPoints();
}

void SmartFish::newFish(int count, int size) const {
  for (int i = 0; i < count; i++) {
    new SmartFish(pop, getX(), getY(), size, vel.getMag(),
                  breedSize,  perception, pops);
  }
}


SmartFish::~SmartFish() {}