#ifndef DRUNKENFISH_H
#define DRUNKENFISH_H
#include "fish.h"
#include "vector.h"

class DrunkenFish : public Fish {
 public:
  DrunkenFish(Population& pop, double x, double y, int size, double speed,
              int breedSize);
  DrunkenFish(Population& pop);
  void update();
  void newFish(int count, int size) const;
  int getPerception() const;
  friend std::ostream& operator<<(std::ostream& out, const DrunkenFish& c);
  virtual ~DrunkenFish();
};

#endif