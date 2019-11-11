#ifndef SMARTFISH_H
#define SMARTFISH_H
#include "fish.h"
#include "vector.h"

class SmartFish : public Fish {
 public:
  SmartFish(Population& pop, double x, double y, int size, double speed,
            int perception, int breedSize, std::vector<Population*>& pops);
  SmartFish(Population& pop, std::vector<Population*>& pops);
  void update();
  void attract(Vector& position, bool reverse, double constant);
  bool inRange(Vector& position);
  bool breed(Fish& mate);
  void newFish(int count, int size) const;
  int getPerception() const;

  friend std::ostream& operator<<(std::ostream& out, const Fish& c);
  virtual ~SmartFish();

 private:
  std::vector<Population*>& pops;
  int perception;
};

#endif