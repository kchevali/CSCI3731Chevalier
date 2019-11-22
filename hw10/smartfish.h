#ifndef SMARTFISH_H
#define SMARTFISH_H
#include "fish.h"
#include "vector.h"

class SmartFish : public Fish {
 public:
  SmartFish(Population& pop, double x, double y, int size, double speed,
            int breedSize, int perception, std::vector<Population*>& pops);
  SmartFish(Population& pop, std::vector<Population*>& pops);
  void virtual update();
  void virtual newFish(int count, int size) const;

  friend std::ostream& operator<<(std::ostream& out, const Fish& c);
  virtual ~SmartFish();

 protected:
  std::vector<Population*>& pops;
};

#endif