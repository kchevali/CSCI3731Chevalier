#include "population.h"
#include <QWidget>
#include <QtGui>
#include <cstdlib>
#include <iostream>
#include "drunkenfish.h"
#include "fish.h"
#include "flippyfish.h"
#include "flockyfish.h"
#include "quadtree.h"
#include "smartfish.h"

Population::Population(int id, int width, int height)
    : color(100 + rand() % 150, 100 + rand() % 150, 100 + rand() % 150),
      quadTree(width / 2.0, height / 2.0, width / 2.0, height / 2.0) {
  this->id = id;
  this->width = width;
  this->height = height;
  this->nextId = 0;
}

// add fish to population
std::list<Fish*>::iterator& Population::add(Fish* fish) {
  fishes.push_back(fish);
  return --fishes.end();
}

// remove fish from population
void Population::remove(std::list<Fish*>::iterator& it) { fishes.erase(it); }

int Population::size() const { return fishes.size(); }
int Population::getNextId() { return nextId++; }

// shrink fish and move/delete them
void Population::shrink() {
  for (auto it = fishes.begin(); it != fishes.end(); it++) {
    if (!(*it)->shrink()) remove(it);
  }
}

// update speed and acc of fish
void Population::update() {
  for (auto it = fishes.begin(); it != fishes.end(); it++) {
    (*it)->update();
    (*it)->updateRotPoints();
  }
}

void Population::avoid(std::vector<Vector>& points, int r) {
  for(Vector& point: points){
      std::vector<Fish*> result;
    quadTree.query(point.getX(), point.getY(), r, result, nullptr);
    for (Fish* fish: result) fish->attract(point, true, 50);
  }
}

// move fish
void Population::swim() {
  quadTree = QuadTree(width / 2.0, height / 2.0, width / 2.0, height / 2.0);
  for (auto it = fishes.begin(); it != fishes.end(); it++) {
    (*it)->swim();
    quadTree.insert(*it);
  }
}

void Population::breed() {
  for (auto it = fishes.begin(); it != fishes.end(); it++) {
    Fish* fish = *it;
    std::vector<Fish*> result;
    quadTree.query(fish->getCenterX(), fish->getCenterY(),
                   fish->getPerception(), result, nullptr);
    for (Fish* other : result) {
      if (fish->getId() > other->getId()) {
        fish->breed(other);
      }
    }
  }
}

// scan a population for every fish to eat
void Population::feed(Population* other) {
  for (auto it = other->begin(); it != other->end(); it++) this->feed(*it);
}

void Population::feed(Fish* emy) {
  std::vector<Fish*> result;
  quadTree.query(emy->getCenterX(), emy->getCenterY(), emy->getPerception(),
                 result, nullptr);

  for (Fish* fish : result) {
    if (!fish->feed(emy)) emy->feed(fish);
  }
}

// getters
int Population::getWidth() const { return width; }
int Population::getHeight() const { return height; }
QColor& Population::getColor() { return color; }
QuadTree& Population::getQuadTree() { return quadTree; }

int Population::getAverageSpeed() {
  int tot = 0, count = 0;
  for (auto it = fishes.begin(); it != fishes.end(); it++)
    if ((*it)->getSize() > 0) {
      tot += (*it)->getVel().getMag();
      count++;
    }
  return tot / count;
}

int Population::getAverageBreedSize() {
  int tot = 0, count = 0;
  for (auto it = fishes.begin(); it != fishes.end(); it++)
    if ((*it)->getSize() > 0) {
      tot += (*it)->getBreedSize();
      count++;
    }
  return tot / count;
}

int Population::getAveragePerception() {
  int tot = 0, count = 0;
  for (auto it = fishes.begin(); it != fishes.end(); it++)
    if ((*it)->getSize() > 0) {
      tot += (*it)->getPerception();
      count++;
    }
  return tot / count;
}

Fish* Population::getLargeFish() {
  Fish* bigBoi = nullptr;
  int size = 0;
  for (auto it = fishes.begin(); it != fishes.end(); it++) {
    Fish* fish = *it;
    if (fish->getSize() > size) size = (bigBoi = fish)->getSize();
  }
  return bigBoi;
}

void Population::display(QPainter& painter) {
  // painter.setPen(getColor());
  for (auto it = fishes.begin(); it != fishes.end(); it++) {
    (*it)->display(painter);
  }
  // quadTree.display(painter);
}

// get fish by index
Fish* Population::get(int index) { return *(std::next(fishes.begin(), index)); }

// head fish
Fish* Population::first() { return fishes.front(); }
std::list<Fish*>::iterator Population::begin() { return fishes.begin(); }
std::list<Fish*>::iterator Population::end() { return fishes.end(); }

// compare
bool Population::operator==(Population& that) const { return this == &that; }
bool Population::operator!=(Population& that) const { return this != &that; }

// print info
std::ostream& operator<<(std::ostream& out, const Population& c) {
  return out << "LEN: " << c.size() << "\t";
}

Population::~Population() {
  for (auto it = fishes.begin(); it != fishes.end(); it++) fishes.erase(it);
}