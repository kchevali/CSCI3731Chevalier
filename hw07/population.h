#ifndef POPULATION_H
#define POPULATION_H
#include <QColor>
class Fish;

class Population {
 public:
  Population(const int count, const int width, const int height);
  void add(int count, int x, int y);
  void add(Fish& Fish);
  void remove(Fish& fish);
  int size() const;
  int averageFishSize() const;
  int getSpeed() const;
  int getWidth() const;
  int getHeight() const;
  int getHistory() const;
  QColor& getColor();
  void update();
  void feed();
  void scan(Population& other);
  Fish& get(const int index) const;
  Fish& first() const;
  bool operator==(Population& that) const;
  bool operator!=(Population& that) const;

  friend std::ostream& operator<<(std::ostream& out, const Population& c);

  virtual ~Population();

 private:
  int length, history, pop_speed, width, height;
  Fish* head;
  QColor color;
};

#endif