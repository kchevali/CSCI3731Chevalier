#include "smartfish.h"
#include "fish.h"
#include "main.h"
#include "population.h"
#include "vector.h"

SmartFish::SmartFish(Population& pop, double x, double y, int size,
                     double speed, int breedSize, int perception,
                     std::vector<Population*>& pops)
    : Fish(pop, x, y, size, speed, breedSize, perception), pops(pops) {}
SmartFish::SmartFish(Population& pop, std::vector<Population*>& pops)
    : Fish(pop), pops(pops) {}

// update velocities/accelerations
void SmartFish::update() {
  for (Population* other : this->pops) {
    if (*other != this->pop) {
      std::vector<Fish*> result;
      other->getQuadTree().query(getCenterX(), getCenterY(), getPerception(),
                                 result, nullptr);
      for (Fish* emy : result) {
        double d = getPos().distSq(emy->getPos());
        if (d < perception * perception)
          attract(emy->getPos(), emy->getSize() >= this->getSize(), 10);
      }
    }
  }
}

void SmartFish::newFish(int count, int size) const {
  for (int i = 0; i < count; i++) {
    new SmartFish(pop, getX(), getY(), size, vel.getMag(), breedSize,
                  perception, pops);
  }
}

SmartFish::~SmartFish() {}