#include "DomView.h"
#include <cassert>
#include <iomanip>

#define MINTIME 50


DomView::DomView(vector<string> &_jug, QWidget *parent):
  QWidget(parent), names(_jug), turn(-1),
  status(PLAY), waitingFor(NOTHING),
  timeAnimation(100), timeDelay(200) {

  logo.load("game.png");

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));

  setMinimumSize(dvt.width(), dvt.height());
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  clock.start();
  animationTimer.setSingleShot(false);
  connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));

  basetime = clock.elapsed();
  animationTimer.start(MINTIME);
}

void DomView::setSpeed(int speedms) {
  timeAnimation = min(100, speedms/2);
  timeDelay = max(speedms/2, speedms-100);
}

void DomView::setSpeedFromSlider(int s) {
  // 5 == default_speed_ms
  int x = DomViewTauler::default_speed_ms;
  while (s > 5) {
    x *= 2/3.0;
    --s;
  }
  while (s < 5) {
    x *= 3/2.0;
    ++s;
  }
  setSpeed(x);
}

void DomView::setStop() {
  status = STOP;
}

void DomView::saveImage(const string &name, int width,
			int height, int provturn) {

  QImage qi(width, height, QImage::Format_RGB32);
  qi.fill( qRgb(128, 255, 128) );

  QPainter p(&qi);
  dvt.dibuixa(p, T[provturn], provturn);

  qi.save(QString(name.c_str()));
}


void DomView::saveImages(const string &basefilename) {
  for(int i=0; i<int(T.size()); ++i) {
    ostringstream oss;
    oss << basefilename << "." << setfill('0') << setw(4) << i << ".ppm";
    cerr << "Saving image '" << oss.str() << "'..." << endl;
    saveImage(oss.str(), dvt.width(), dvt.height(), i);
  }
}

void DomView::paintEvent(QPaintEvent *) {

  if (turn==-1) {
    QPainter painter(this);
    painter.drawPixmap(QRect(0, 0, width(), height()),
		      logo);
    return;
  }

  for(int i=0;i<4;++i) {
    signalUpdateTeamPoints(i, names[i],
			   T[turn].puntuacio(i+1), dvt.color_equip(i+1));
  }
  signalUpdateTurn(T[turn].quin_torn());

  //always draw on a QImage(dvt.width(), dvt.height())
  QImage qim(dvt.width(), dvt.height(), QImage::Format_RGB32);
  QPainter p2(&qim);
  dvt.dibuixa(p2, T[turn], turn);

  QPainter painter(this);
  painter.drawImage(QRect(0, 0, dvt.width(), dvt.height()),
		    qim, QRect(0, 0, dvt.width(), dvt.height()));
}

void DomView::addTauler(Tauler &t) {
  T.push_back(t);
  signalMaxTimeChanged(T.size());
}

void DomView::next_frame() {
  //do we have a next frame?
  if (int(T.size())-1 == turn) return;

  ++turn; signalTimeChanged(turn);
  if (status == PLAY) waitingFor = ANIMATION;
  else if (status == STOP) waitingFor = NOTHING;

  basetime = clock.elapsed();
  animate();
}

void DomView::prev_frame() {
  //do we have a prev frame?
  if (turn <= 0) return;

  --turn; signalTimeChanged(turn);
  if (status == PLAY) waitingFor = DELAY;
  else if (status == STOP) waitingFor = NOTHING;

  basetime = clock.elapsed();
  animate();
}


void DomView::animate() {
  int diff = clock.elapsed() - basetime;

  if (waitingFor == ANIMATION and diff > timeAnimation) {
    waitingFor = DELAY;
    basetime = clock.elapsed() - (diff-timeAnimation);

    animationTimer.start(min(MINTIME,
			     max(1, timeDelay - (diff-timeAnimation))));
  }
  else if (waitingFor == DELAY and diff > timeDelay) {
    if (status == PLAY) {
      //haig d'esperar
      if (turn == int(T.size())-1) {
	waitingFor = NOTHING;
	animationTimer.start(MINTIME);
	update();
	return;
      }

      ++turn; signalTimeChanged(turn);
      waitingFor = ANIMATION;
      basetime = clock.elapsed();

      animationTimer.start(minredrawingtime);
      return;  //no repaint if delaying
    }
    else if (status == STOP) {
      waitingFor = NOTHING;
      animationTimer.start(MINTIME);
      update();
      return;
    }
  }
  else if (waitingFor == NOTHING) {
    if (status == PLAY and turn<int(T.size())-1) {
      ++turn; signalTimeChanged(turn);
      waitingFor = ANIMATION;
      basetime = clock.elapsed();

      animationTimer.start(minredrawingtime);
    }
    else return; //no repaint if doing nothing
  }

  repaint();
}


void DomView::stop() {
  status = STOP;
}

void DomView::play() {
  status = PLAY;
}

//void DomView::start() {
//  turn = 0;
//  status = STOP;
//  update();
//}

void DomView::stepback() {
  status = STOP;
  prev_frame();
  update();
}

void DomView::stepforw() {
  status = STOP;
  next_frame();
  update();
}

void DomView::setTimer(int t) {
  status = STOP;
  if (t>=0 and t<int(T.size())) {
    turn = t;
    signalTimeChanged(turn);
  }
  update();
}
