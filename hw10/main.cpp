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
  *Battle Royale - 3 Classes - 8 Populations - Only 1 will survive
  *Classes: Flippy(1), Drunken(1) and Smart(5)
  *Starting Populations are 150 for Flippy and Drunken,and 50 for Smart
  *Scoreboard at the bottom shows the pop sizes respectively

  *Each fish has random starting attributes
  *A fish's children will have similar attributes
  *Fishes target/eats smaller fishes from different populations
  *Fishs have different movement mechanisms (based on class)
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
    Pathfinding for fish tracking is significantly improved
    Added breeding
    Added precise collsion detection
    Show characteristics of the largest population to show change in
characteristic
*/

int main(int argc, char** argv) {
  srand(time(NULL));

  // define populations
  std::vector<Population*> pops;
  const int numberOfSimplePopulations = 1;
  const int simplePopSize = 100;

  const int numberOfSmartPopulations = 5;
  const int smartPopSize = 5;

  const int totalNumberOfPopulations =
      numberOfSmartPopulations + 2 * numberOfSimplePopulations;

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
  for (int i = 0; i < totalNumberOfPopulations; i++)
    pops.push_back(new Population(i, size.width(), size.height()));

  // Create fishies
  for (int i = 0; i < simplePopSize; i++) {
    for (int j = 0; j < numberOfSimplePopulations; j++) {
      new DrunkenFish(*pops[2 * j]);
      new FlippyFish(*pops[2 * j + 1]);
    }
  }
  for (int i = 0; i < smartPopSize; i++) {
    for (int j = 0; j < numberOfSmartPopulations; j++)
      new SmartFish(*pops[j + 2 * numberOfSimplePopulations], pops);
  }

  // run
  myWidget.show();
  return app.exec();
}

// constrain value between min and max
double constrain(double x, double min, double max) {
  return std::min(std::max(min, x), max);
}

int ran(int min, int max) { return (rand() % (max - min)) + min; }