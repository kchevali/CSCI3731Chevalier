#include "population.h"
#include <QColor>
#include <cstdlib>
#include "fish.h"

Population::Population(const int width, const int height)
    : head(nullptr),
      color(100 + rand() % 150, 100 + rand() % 150, 100 + rand() % 150) {
  this->length = this->history = 0;
  this->width = width;
  this->height = height;
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

// shrink fish and move/delete them
void Population::shrink() {
  Fish* curr = head;
  while (curr != nullptr) {
    Fish* next = curr->getNext();
    if (!curr->shrink()) delete curr;
    curr = next;
  }
}

//update speed and acc of fish
void Population::update() {
  Fish* curr = head;
  while (curr != nullptr) {
    curr->update();
    curr = curr->getNext();
  }
}

//move fish
void Population::swim() {
  Fish* curr = head;
  while (curr != nullptr) {
    curr->swim();
    curr = curr->getNext();
  }
}

void Population::breed() {
  Fish* curr = head;
  while (curr != nullptr) {
    Fish* other = curr->getNext();
    while (other != nullptr) {
      curr->breed(*other);
      other = other->getNext();
    }
    curr = curr->getNext();
  }
}

// scan a population for every fish to eat
void Population::feed(Population& other) {
  Fish* curr = head;
  while (curr != nullptr) {
    curr->feed(other);
    curr = curr->getNext();
  }
}

// getters
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
  return out << "LEN: " << c.size() << "\t";
}

Population::~Population() {
  // del all fish
  while (head != nullptr) {
    Fish* next = head->getNext();
    delete head;
    head = next;
  }
}