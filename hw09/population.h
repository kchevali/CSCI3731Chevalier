#ifndef POPULATION_H
#define POPULATION_H
#include <QColor>
class Fish;

class Population {
 public:
  Population(const int width, const int height);
  void add(Fish& Fish);
  void remove(Fish& fish);
  int size() const;
  int getWidth() const;
  int getHeight() const;
  int getHistory() const;
  QColor& getColor();
  void swim();
  void update();
  void feed(Population& other);
  void shrink();
  void breed();
  int getAverageSpeed() const;
  int getAverageBreedSize() const;
  int getAveragePerception() const;
  Fish& get(const int index) const;
  Fish& first() const;
  bool operator==(Population& that) const;
  bool operator!=(Population& that) const;

  friend std::ostream& operator<<(std::ostream& out, const Population& c);

  virtual ~Population();
  Population& operator=(const Population& thing) = delete;

 private:
  int length, history, width, height;
  Fish* head;
  QColor color;
};

#endif