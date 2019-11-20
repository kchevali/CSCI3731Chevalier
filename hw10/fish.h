#ifndef FISH_H
#define FISH_H
#include <QWidget>
#include <list>
#include <vector>
#include "vector.h"
class Population;

class Fish {
 public:
  Fish(Population& pop);
  Fish(Population& pop, double x, double y, int size, double speed,
       int breedSize, int perception);
  void swim();
  void virtual update() = 0;
  void virtual newFish(int count, int size) const = 0;
  void bound();
  bool feed(Fish* emy);
  bool hasPopulation();
  bool shrink();
  void breed(Fish* mate);
  int getId() const;
  int getSize() const;
  int getBreedSize() const;
  double getX() const;
  double getY() const;
  double getCenterX() const;
  double getCenterY() const;
  double rotX(double dx, double dy);
  double rotY(double dx, double dy);
  void updateRotPoints();
  bool isCollide(Fish* other);
  double getWidth() const;
  double getHeight() const;
  Vector& getPos();
  Vector& getVel();
  Vector& getAcc();
  Angle& getDirection();
  int getPerception() const;
  void death();
  void setPos(double x, double y);
  Population& getPop() const;
  void display(QPainter& painter);
  virtual ~Fish();
  friend std::ostream& operator<<(std::ostream& out, const Fish& c);

  bool operator==(Fish& that) const;
  Fish& operator=(const Fish& thing) = delete;

 protected:
  int id, size, width, height, maxSpeed, perception;
  ;
  double breedSize;
  Vector pos, vel, acc;
  Population& pop;
  std::list<Fish*>::iterator& it;

 private:
  std::vector<Vector*> rotPoints;
};

#endif