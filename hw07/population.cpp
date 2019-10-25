#include "population.h"
#include <QColor>
#include <cstdlib>
#include "fish.h"

Population::Population(const int count, const int width, const int height)
    : head(nullptr),
      color(100 + rand() % 150, 100 + rand() % 150, 100 + rand() % 150) {
  // determine population speed
  this->pop_speed = 1 + rand() % 3;
  this->length = this->history = 0;
  this->width = width;
  this->height = height;

  // create fishes
  for (int i = 0; i < count; i++) new Fish(*this);
}

// add fish to population
void Population::add(Fish& fish) {
  // if has population already, then change it
  if (fish.hasPopulation()) {
    fish.setPop(*this);
    return;
  }

  // add to existing chain from front
  if (head != nullptr) {
    fish.setNext(head);
    head->setPrev(&fish);
  }

  // set front
  head = &fish;

  length++;
  history++;
}

// remove fish from population
void Population::remove(Fish& fish) {
  // cant remove fish not in the population
  if (*this != fish.getPop()) return;

  // disconnect chain from fish
  Fish *next = fish.getNext(), *prev = fish.getPrev();
  if (next != nullptr) next->setPrev(prev);
  if (prev != nullptr) prev->setNext(next);
  if (fish == *head) head = next;

  // disconnect fish from chain
  fish.setNext(nullptr);
  fish.setPrev(nullptr);

  --length;
}

int Population::size() const { return length; }
int Population::getHistory() const { return history; }

// average size of all fish in the population
int Population::averageFishSize() const {
  if (length == 0) return 0;
  int avg = 0;
  Fish* curr = head;
  while (curr != nullptr) {
    avg += curr->getSize();
    curr = curr->getNext();
  }
  return avg / length;
}

// shrink fish and move/delete them
void Population::update() {
  Fish* curr = head;
  while (curr != nullptr) {
    Fish* next = curr->getNext();

    if (curr->shrink()) {
      curr->swim();
    } else
      delete curr;

    curr = next;
  }
}

// if found food then eat
void Population::feed() {
  Fish* curr = head;
  while (curr != nullptr) {
    Fish* next = curr->getNext();
    curr->feed();
    curr = next;
  }
}

// scan a population for every fish
void Population::scan(Population& other) {
  Fish* curr = head;
  while (curr != nullptr) {
    curr->scan(other);
    curr = curr->getNext();
  }
}

// getters
int Population::getSpeed() const { return pop_speed + rand() % 1; }
int Population::getWidth() const { return width; }
int Population::getHeight() const { return height; }
QColor& Population::getColor() { return color; }

// get fish by index
Fish& Population::get(const int index) const {
  Fish* curr = head;
  int i = length - index - 1;
  while (i-- != 0) {
    curr = curr->getNext();
  }
  return *curr;
}

// head fish
Fish& Population::first() const { return *head; }

// compare
bool Population::operator==(Population& that) const { return this == &that; }
bool Population::operator!=(Population& that) const { return this != &that; }

// print info
std::ostream& operator<<(std::ostream& out, const Population& c) {
  return out << "LEN: " << c.size() << " SP: " << c.pop_speed
             << " AVG: " << c.averageFishSize() << "\t";
}

Population::~Population() {
  // del all fish
  while (head != nullptr) {
    Fish* next = head->getNext();
    delete head;
    head = next;
  }
}