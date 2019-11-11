#ifndef FLIPPYFISH_H
#define FLIPPYFISH_H
#include "angle.h"
#include "fish.h"

class FlippyFish : public Fish {
 public:
  FlippyFish(Population& pop, double x, double y, int size, double speed,
             int breedSize);
  FlippyFish(Population& pop);
  void update();
  void newFish(int count, int size) const;
  int getPerception() const;
  friend std::ostream& operator<<(std::ostream& out, const FlippyFish& c);
  virtual ~FlippyFish();

 protected:
  Angle turnRate;
};

#endif