#include "smartfish.h"
#include "fish.h"
#include "main.h"
#include "population.h"
#include "vector.h"

SmartFish::SmartFish(Population& pop, double x, double y, double size,
                     double speed, double perception, double breedSize,
                     std::vector<Population*>& pops)
    : Fish(pop, x, y, size, speed, breedSize), pops(pops) {
  this->perception = std::max(0, ran(perception - 10, perception + 10));
}
SmartFish::SmartFish(Population& pop, std::vector<Population*>& pops)
    : Fish(pop), pops(pops) {
  this->perception = 2000;  // ran(10, 20);
}

//attract/repulse self to another fish based on size
void SmartFish::attract(Vector& position, bool reverse, double constant) {
  Vector force = reverse ? this->pos - position : position - this->pos;
  double dirSq = constrain(force.getMagSq(), 25, 100);
  double strength = constant / dirSq;
  force.setMag(strength);
  acc += force;
}

//check if fish is in range
bool SmartFish::inRange(Vector& position){
  double dx = getX() - position.getX(), dy = getY() - position.getY();
  return dx*dx + dy*dy <= perception;
}

//update velocities/accelerations
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
  //adjust rot points for collision detecting
  updateRotPoints();
}

bool SmartFish::breed(Fish& mate) {
  if (Fish::breed(mate)) {
    new SmartFish(*pop, getX(), getY(), size / 2, vel.getMag(), perception,
                  breedSize, pops);
    return true;
  }
  return false;
}