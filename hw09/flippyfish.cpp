#include "flippyfish.h"
#include "fish.h"
#include "main.h"
#include "vector.h"

FlippyFish::FlippyFish(Population& pop, double x, double y, double size,
                       double speed, double breedSize)
    : Fish(pop, x, y, size, speed, breedSize), turnRate(5) {}

FlippyFish::FlippyFish(Population& pop) : Fish(pop), turnRate(5) {}

void FlippyFish::update() {
  //move fish randomly by the turn rate
  int choice = rand() % 3;
  if (choice == 0)
    vel.turn(-turnRate);
  else if (choice == 1)
    vel.turn(turnRate);
  updateRotPoints();
}
bool FlippyFish::breed(Fish& mate) {
  if (Fish::breed(mate)) {
    new FlippyFish(*pop, getX(), getY(), size / 2, vel.getMag(), breedSize);
    return true;
  }
  return false;
}