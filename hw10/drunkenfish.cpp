#include "drunkenfish.h"
#include "fish.h"
#include "main.h"
#include "population.h"
#include "vector.h"

DrunkenFish::DrunkenFish(Population& pop, double x, double y, int size,
                         double speed, int breedSize, int perception)
    : Fish(pop, x, y, size, speed, breedSize, perception) {}

DrunkenFish::DrunkenFish(Population& pop) : Fish(pop) {
  // pos.set(pop.getWidth() / 2, pop.getHeight() / 2);
  // vel.set(0, 0);
  // size = 10;
}

void DrunkenFish::update() {
  // turn 90 to the left, right or go straight
  if (rand() % 20 == 0) vel.turn(rand() % 3 * 90 - 90);
}

void DrunkenFish::newFish(int count, int size) const {
  for (int i = 0; i < count; i++) {
    new DrunkenFish(pop, getX(), getY(), size, vel.getMag(), breedSize,
                    perception);
  }
}
DrunkenFish::~DrunkenFish() {}