#include "flippyfish.h"
#include "angle.h"
#include "fish.h"
#include "main.h"
#include "vector.h"

FlippyFish::FlippyFish(Population& pop, double x, double y, int size,
                       double speed, int breedSize, int perception)
    : Fish(pop, x, y, size, speed, breedSize, perception), turnRate(5) {}

FlippyFish::FlippyFish(Population& pop) : Fish(pop), turnRate(5) {}

void FlippyFish::update() {
  // move fish randomly by the turn rate
  int choice = rand() % 3;
  if (choice == 0)
    vel.turn(-turnRate);
  else if (choice == 1)
    vel.turn(turnRate);
}
void FlippyFish::newFish(int count, int size) const {
  for (int i = 0; i < count; i++) {
    new FlippyFish(pop, getX(), getY(), size, vel.getMag(), breedSize,
                   perception);
  }
}

FlippyFish::~FlippyFish() {}