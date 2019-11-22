#ifndef POPULATION_H
#define POPULATION_H
#include <QColor>
#include <list>
#include "quadtree.h"
class Fish;

class Population {
 public:
  Population(int id, int width, int height);
  std::list<Fish*>::iterator& add(Fish* Fish);
  void remove(std::list<Fish*>::iterator& it);
  int size() const;
  int getWidth() const;
  int getHeight() const;
  int getNextId();

  QColor& getColor();
  QuadTree& getQuadTree();
  void swim();
  void update();
  void avoid(std::vector<Vector>& points, int r);
  void feed(Population* other);
  void feed(Fish* emy);
  void shrink();
  void breed();
  int getAverageSpeed();
  int getAverageBreedSize();
  int getAveragePerception();
  Fish* getLargeFish();
  Fish* get(int index);
  Fish* first();
  void display(QPainter& painter);
  std::list<Fish*>::iterator begin();
  std::list<Fish*>::iterator end();
  bool operator==(Population& that) const;
  bool operator!=(Population& that) const;

  friend std::ostream& operator<<(std::ostream& out, const Population& c);

  virtual ~Population();
  Population& operator=(const Population& thing) = delete;

 private:
  int id, width, height, nextId;
  std::list<Fish*> fishes;
  QColor color;
  QuadTree quadTree;
};

#endif