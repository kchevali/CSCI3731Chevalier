#ifndef DRUNKENFISH_H
#define DRUNKENFISH_H
#include "fish.h"
#include "vector.h"

class DrunkenFish : public Fish {
 public:
  DrunkenFish(Population& pop, double x, double y, double size, double speed,
              double breedSize);
  DrunkenFish(Population& pop);
  void update();
  bool breed(Fish& mate);
  friend std::ostream& operator<<(std::ostream& out, const DrunkenFish& c);

};

#endif