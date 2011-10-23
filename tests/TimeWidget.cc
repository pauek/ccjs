
#include "TimeWidget.h"
#include <QPushButton>
#include <QToolButton>
#include <QSlider>
#include <QLineEdit>

#include <QLabel>
#include <QScrollBar>
#include <QLayout>

#include <cassert>
#include <sstream>
#include <iostream>

#define ADD_BUTTON(NAME) \
  QToolButton * NAME##Button = new QToolButton(this);  \
  NAME##Button->setIcon(QIcon(#NAME "Icon.png")); \
  NAME##Button->setText(tr(#NAME)); \
  connect(NAME##Button, SIGNAL(clicked()), \
	  domview, SLOT(NAME()));	\
  buttonsLayout->addWidget(NAME##Button)

TimeWidget::TimeWidget(QWidget *domview, QWidget *parent):
  QWidget(parent) {

  //  setWindowTitle(tr("World Controller"));

  //  QToolButton *resetButton = new QToolButton(this);
  //  resetButton->setIcon(QIcon("resetIcon.png"));
  // resetButton->setText(tr("Reset"));
  // connect(resetButton, SIGNAL(clicked()), wc, SLOT(reset()));

  QHBoxLayout *buttonsLayout = new QHBoxLayout(this);

  //  ADD_BUTTON(reset);

  //  ADD_BUTTON(rewind);
  ADD_BUTTON(stop);
  ADD_BUTTON(play);

  //  ADD_BUTTON(slow);
  ADD_BUTTON(stepback);
  ADD_BUTTON(stepforw);

  //QSlider 1
  slider = new QSlider(Qt::Horizontal, this);
  slider->setTickInterval(10);
  slider->setTickPosition(QSlider::TicksBelow);
  slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );

  connect(domview, SIGNAL(signalTimeChanged(int)),
  	  this, SLOT(timeChanged(int)));
  connect(domview, SIGNAL(signalMaxTimeChanged(int)),
  	  this, SLOT(maxTimeChanged(int)));
  connect(slider, SIGNAL(sliderMoved(int)),
  	  domview, SLOT(setTimer(int)));

  //QSlider 2
  speeder = new QSlider(Qt::Horizontal, this);
  speeder->setTickInterval(1);
  speeder->setTickPosition(QSlider::TicksBelow);
  speeder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );
  speeder->setRange(1, 10);
  speeder->setValue(5);

  connect(speeder, SIGNAL(sliderMoved(int)),
  	  domview, SLOT(setSpeedFromSlider(int)));

  // Add them

  buttonsLayout->addWidget(slider);
  buttonsLayout->addWidget(speeder);

  reset();
}

void TimeWidget::maxTimeChanged(int t) {
  slider->setRange(0, t);
}

void TimeWidget::timeChanged(int t) {
  assert(t>=0);
  if (t > slider->maximum()) {
    slider->setRange(0, t);
  }
  slider->setValue(t);
}


void TimeWidget::reset() {
  slider->setRange(0, 0);
  slider->setValue(0);
  //  timeEdit->setText("0");
}
