#include "drunkenfish.h"
#include "fish.h"
#include "main.h"
#include "population.h"
#include "vector.h"

DrunkenFish::DrunkenFish(Population& pop, double x, double y, double size,
                         double speed, double breedSize)
    : Fish(pop, x, y, size, speed, breedSize) {}

DrunkenFish::DrunkenFish(Population& pop) : Fish(pop) {
  // pos.set(pop.getWidth() / 2, pop.getHeight() / 2);
  // vel.set(0, 0);
  // size = 10;
}

void DrunkenFish::update() {

  //turn 90 to the left, right or go straight
  if (rand() % 20 == 0) vel.turn(rand() % 3 * 90 - 90);
  updateRotPoints();
}

bool DrunkenFish::breed(Fish& mate) {
  if (Fish::breed(mate)) {
    new DrunkenFish(*pop, getX(), getY(), size / 2, vel.getMag(), breedSize);
    return true;
  }
  return false;
}