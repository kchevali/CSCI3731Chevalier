#ifndef SMARTFISH_H
#define SMARTFISH_H
#include "fish.h"
#include "vector.h"

class SmartFish : public Fish {
 public:
  SmartFish(Population& pop, double x, double y, double size, double speed,
            double perception, double breedSize,
            std::vector<Population*>& pops);
  SmartFish(Population& pop, std::vector<Population*>& pops);
  void update();
  void attract(Vector& position, bool reverse, double constant);
  bool inRange(Vector& position);
  bool breed(Fish& mate);
  friend std::ostream& operator<<(std::ostream& out, const Fish& c);

 private:
  std::vector<Population*>& pops;
  double perception;
};

#endif