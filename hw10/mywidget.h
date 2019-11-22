#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QCheckBox>
#include <QWidget>
#include <QtGui>
#include "population.h"

class MyWidget : public QWidget {
  Q_OBJECT
 public:
  MyWidget(std::vector<Population *> &pops);
  void updatePopulations();
  MyWidget &operator=(const MyWidget &thing) = delete;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
 signals:

 private:
  std::vector<Population *> &pops;
  std::string bestText, fps;
  QTimer *timer;
  QTime time;
  int frame;
  bool isSingleView;
  Vector mouse;
  std::vector<Vector> avoidPoints;
  Angle<double> temp;

 public slots:
};

#endif  // MYWIDGET_H