#ifndef FLOCKYFISH_H
#define FLOCKYFISH_H
#include "smartfish.h"
#include "vector.h"

class FlockyFish : public SmartFish {
 public:
  FlockyFish(Population& pop, double x, double y, int size, double speed,
             int breedSize, int perception, std::vector<Population*>& pops);
  FlockyFish(Population& pop, std::vector<Population*>& pops);
  void update();
  void align(std::vector<Fish*> fishes);
  void cohesion(std::vector<Fish*> fishes);
  void separation(std::vector<Fish*> fishes);
  void newFish(int count, int size) const;

  friend std::ostream& operator<<(std::ostream& out, const Fish& c);
  virtual ~FlockyFish();
};

#endif