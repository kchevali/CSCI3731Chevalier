#include "main.h"
#include <QApplication>
#include <QtGui>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include "angle.h"
#include "drunkenfish.h"
#include "fish.h"
#include "flippyfish.h"
#include "flockyfish.h"
#include "mywidget.h"
#include "population.h"
#include "smartfish.h"

/*
Kevin Chevalier
November 3, 2019
CSCI 3731
Homework 9
Inheritance: More fishes!

Simulation Rules
  *Battle Royale - 4 Classes -
  *Classes: Flippy, Drunken, Smart, Flocky(Subclass of Smart)
  *Scoreboard at the bottom shows the pop sizes respectively
  *Left click to see Single View, which highlights the largest fish and his view of other populations with the quad tree
  *Right click to place a obstacle

  *Each fish has random starting attributes
  *A fish's children will have similar attributes
  *Fishes target/eats smaller fishes from different populations
  *Fishs have different movement mechanisms (based on class)
  *Flocky fishes try to form flocks and tend to stay close as a group
  *Flocky fish try to stay close, but not too close and have similar alignments
  *Flocky fish follow the same behavior as Smart fish:
  *Smart fishes are attracted to smaller fish and run away from bigger fish
  *Smart fishes can only see other fishes within their range of perception
  *Fishes can only eat other fishes within their feeding radius
  *Every iteration, a fish shrinks in size - pops larger then 50 shrink faster
  *A fish dies when its eaten or its size is zero
  *When a fish eats it gets bigger
  *A fish can breed if it is big enough and meets a friend
  *A fish can also breed asexually if it eats too much
  *A fish gets smaller when it breeds


  Big changes from last time
    Added QuadTree optimization
    Added Flocky Fish
    Added Left click (new view)
    Added Right click (create obstacles)

Debugger: llbd build/main.exe -> run
*/

int main(int argc, char** argv) {

  srand(time(NULL));

  // define populations
  std::vector<Population*> pops;
  const int numOfSimplePopulations = 1;
  const int simplePopSize = 50;

  const int numOfSmartPopulations = 0;
  const int smartPopSize = 10;

  const int numOfFlockyPopulations = 8;
  const int flockyPopSize = 10;

  const int totalNumOfPopulations = numOfSmartPopulations +
                                    numOfFlockyPopulations +
                                    2 * numOfSimplePopulations;

  // start application
  QApplication app(argc, argv);
  MyWidget myWidget(pops);
  QPalette pal = QPalette();

  // set background
  pal.setColor(QPalette::Background, QColor(0, 0, 50));
  myWidget.setAutoFillBackground(true);
  myWidget.setPalette(pal);
  myWidget.resize(1200, 600);

  // Create populations
  QSize size = myWidget.size();
  for (int i = 0; i < totalNumOfPopulations; i++)
    pops.push_back(new Population(i, size.width(), size.height()));

  // Create fishies
  for (int i = 0; i < simplePopSize; i++) {
    for (int j = 0; j < numOfSimplePopulations; j++) {
      new DrunkenFish(*pops[2 * j]);
      new FlippyFish(*pops[2 * j + 1]);
    }
  }
  int start = 2 * numOfSimplePopulations;
  for (int i = 0; i < smartPopSize; i++) {
    for (int j = 0; j < numOfSmartPopulations; j++)
      new SmartFish(*pops[j + start], pops);
  }

  start += numOfSmartPopulations;
  for (int i = 0; i < flockyPopSize; i++) {
    for (int j = 0; j < numOfFlockyPopulations; j++) {
      new FlockyFish(*pops[j + start], pops);
    }
  }

  // run
  if (totalNumOfPopulations > 0) {
    myWidget.show();
    return app.exec();
  }
}

// constrain value between min and max
double constrain(double x, double min, double max) {
  return std::min(std::max(min, x), max);
}

int ran(int min, int max) { return (rand() % (max - min)) + min; }