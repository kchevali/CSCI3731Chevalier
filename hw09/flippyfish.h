#ifndef FLIPPYFISH_H
#define FLIPPYFISH_H
#include "angle.h"
#include "fish.h"

class FlippyFish : public Fish {
 public:
  FlippyFish(Population& pop, double x, double y, double size, double speed,
             double breedSize);
  FlippyFish(Population& pop);
  void update();
  bool breed(Fish& mate);
  friend std::ostream& operator<<(std::ostream& out, const FlippyFish& c);

protected:
  Angle turnRate;
};

#endif