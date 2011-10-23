#include "common.h"
#include "DomWin.h"
#include <QLayout>
#include <cassert>

DomWin::DomWin(vector<string> &names, int fontsize, QWidget *parent):
  QWidget(parent) {

  vl.resize(4);
  for(int i=0;i<4;++i) {
    vl[i] = new QLabel(names[i].c_str());
    vl[i]->setAlignment(Qt::AlignCenter);

    QFont qf = vl[i]->font();
    qf.setPointSize(fontsize);
    qf.setStyleHint(QFont::Times);
    vl[i]->setFont(qf);
  }

  QVBoxLayout *vLayoutL = new QVBoxLayout;
  vLayoutL->addStretch(1);
  vLayoutL->addWidget(vl[0]);
  vLayoutL->addStretch(1);
  vLayoutL->addWidget(vl[3]);
  vLayoutL->addStretch(1);

  QVBoxLayout *vLayoutR = new QVBoxLayout;
  vLayoutR->addStretch(1);
  vLayoutR->addWidget(vl[1]);
  vLayoutR->addStretch(1);
  vLayoutR->addWidget(vl[2]);
  vLayoutR->addStretch(1);

  QVBoxLayout *vLayoutC = new QVBoxLayout;
  dv = new DomView(names);

  connect(dv,
	  SIGNAL(signalUpdateTeamPoints(int, string, int, QColor)),
	  this,
	  SLOT(updateTeamPoints(int, string, int, QColor))
	  );

  connect(dv,
	  SIGNAL(signalUpdateTurn(int)),
	  this,
	  SLOT(updateTurn(int))
	  );

  turn = new QLabel(LONG_GAME_NAME);
  QFont tf = turn->font();
  tf.setPointSize(12);
  turn->setFont(tf);

  QHBoxLayout *midLayout = new QHBoxLayout;
  midLayout->addStretch(1);
  midLayout->addWidget(turn);
  midLayout->addStretch(1);

  vLayoutC->addLayout(midLayout);
  vLayoutC->addWidget(dv);
  tw = new TimeWidget(dv);
  vLayoutC->addWidget(tw);

  QHBoxLayout *mainLayout = new QHBoxLayout;

  mainLayout->addLayout(vLayoutL);
  mainLayout->addLayout(vLayoutC);
  mainLayout->addLayout(vLayoutR);

  setLayout(mainLayout);
  setWindowTitle(tr(LONG_GAME_NAME));
}

void DomWin::updateTeamPoints(int team, string name, int points, QColor c) {
    char buf[1000];
    sprintf(buf, "%s\n%05d\n          ", name.c_str(), points);
  vl[team]->setText(buf);

  QPalette qp = vl[team]->palette();
  qp.setColor(QPalette::WindowText, c);
  vl[team]->setPalette(qp);
}

void DomWin::updateTurn(int t) {
  ostringstream oss;
  oss << t;
  turn->setText(oss.str().c_str());
}

