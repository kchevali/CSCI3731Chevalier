#include "flockyfish.h"
#include <cmath>
#include "main.h"
#include "population.h"
#include "smartfish.h"
#include "vector.h"

FlockyFish::FlockyFish(Population& pop, double x, double y, int size,
                       double speed, int breedSize, int perception,
                       std::vector<Population*>& pops)
    : SmartFish(pop, x, y, size, speed, breedSize, perception, pops) {}
FlockyFish::FlockyFish(Population& pop, std::vector<Population*>& pops)
    : SmartFish(pop, pops) {}

void FlockyFish::align(std::vector<Fish*> fishes) {
  Vector steering;
  int total = 0;
  for (Fish* other : fishes) {
    double d = getPos().distSq(other->getPos());
    if (inView(other->getPos(),d)) {
      steering += other->getVel();
      total++;
    }
  }
  if (total > 0) {
    steering /= total;
    steering.setMag(maxSpeed);
    steering -= getVel();
    steering.limit(maxForce);
  }
  acc += steering;
}

void FlockyFish::cohesion(std::vector<Fish*> fishes) {
  Vector steering;
  int total = 0;
  for (Fish* other : fishes) {
    double d = getPos().distSq(other->getPos());
    if (inView(other->getPos(),d)) {
      steering += other->getPos();
      total++;
    }
  }
  if (total > 0) {
    steering /= total;
    steering -= getPos();
    steering.setMag(maxSpeed);
    steering -= getVel();
    steering.limit(maxForce);
  }
  acc += steering;
}

void FlockyFish::separation(std::vector<Fish*> fishes) {
  Vector steering;
  int total = 0;
  for (Fish* other : fishes) {
    double d = getPos().distSq(other->getPos());
    if (inView(other->getPos(),d)) {
      Vector diff = getPos() - other->getPos();
      diff /= d;
      steering += diff;
      total++;
    }
  }
  if (total > 0) {
    steering /= total;
    steering.setMag(maxSpeed);
    steering -= getVel();
    steering.limit(2*maxForce);
  }
  acc += steering;
}

// update velocities/accelerations
void FlockyFish::update() {
  SmartFish::update();
  std::vector<Fish*> result;
  pop.getQuadTree().query(getCenterX(), getCenterY(), perception, result,
                          nullptr);
  align(result);
  cohesion(result);
  separation(result);
}

void FlockyFish::newFish(int count, int size) const {
  for (int i = 0; i < count; i++) {
    new FlockyFish(pop, getX(), getY(), size, vel.getMag(), breedSize,
                   perception, pops);
  }
}

FlockyFish::~FlockyFish() {}