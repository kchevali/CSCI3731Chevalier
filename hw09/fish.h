#ifndef FISH_H
#define FISH_H
#include <vector>
#include "vector.h"
class Population;

class Fish {
 public:
  Fish(Population& pop);
  Fish(Population& pop, double x, double y, int size, double speed,
       int breedSize);
  void swim();
  void virtual update() = 0;
  void virtual newFish(int count, int size) const = 0;
  void bound();
  void feed(Population& other);
  void feed(Fish& emy);
  bool hasPopulation();
  bool shrink();
  void breed(Fish& mate);
  int getSize() const;
  int getBreedSize() const;
  double getX() const;
  double getY() const;
  double getCenterX() const;
  double getCenterY() const;
  double rotX(double dx, double dy);
  double rotY(double dx, double dy);
  void updateRotPoints();
  bool isCollide(Fish& other);
  double getWidth() const;
  double getHeight() const;
  Vector& getPos();
  Vector& getVel();
  Vector& getAcc();
  Angle& getDirection();
  int virtual getPerception() const = 0;
  void death();
  void setPos(double x, double y);
  void setNext(Fish* next);
  Fish* getNext() const;
  void setPrev(Fish* prev);
  Fish* getPrev() const;
  Population& getPop() const;
  void setPop(Population& pop);
  virtual ~Fish();
  friend std::ostream& operator<<(std::ostream& out, const Fish& c);

  bool operator==(Fish& that) const;
  Fish& operator=(const Fish& thing) = delete;

 protected:
  int id, size, width, height, maxSpeed;
  double breedSize;
  Vector pos, vel, acc;
  Population* pop;
  Fish *next, *prev, *target;

 private:
  std::vector<Vector*> rotPoints;
};

#endif