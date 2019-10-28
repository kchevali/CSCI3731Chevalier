#ifndef FISH_H
#define FISH_H
#include "angle.h"
class Population;

class Fish {
 public:
  Fish(Population& pop, int x, int y, double direction);
  void swim();
  void bound();
  void scan(Population& other);
  void scan(Fish& emy);
  void feed();
  bool hasPopulation();
  bool shrink();
  int getSize() const;
  double getX() const;
  double getY() const;
  int getWidth() const;
  int getHeight() const;
  double getDirection() const;
  double getPerception() const;
  double getFeedRadius() const;
  void death();
  bool hasTarget() const;
  void setNext(Fish* next);
  Fish* getNext() const;
  void setPrev(Fish* prev);
  Fish* getPrev() const;
  Population& getPop() const;
  void setPop(Population& pop);
  virtual ~Fish();
  friend std::ostream& operator<<(std::ostream& out, const Fish& c);

  bool operator==(Fish& that) const;

 private:
  int id, speed, size, width, height;
  double x, y, targetDist, perception, feedRadius;
  Angle direction, turn;
  Population* pop;
  Fish *next, *prev, *target;
};

#endif