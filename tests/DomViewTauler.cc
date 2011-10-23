#include "DomViewTauler.h"

DomViewTauler::DomViewTauler() {
  initColors();
}

QColor DomViewTauler::color_equip(int i) const {
  return color_e(i-1);
}

QColor DomViewTauler::color(int que, int team) {
  if (que == BLOCK) return Qt::white;
  if (que == EMPTY) return Qt::black;
  if (que == CYCLE) return aclara(color_e(team), 0.25);
  if (que == WALL) return Qt::black;
  return Qt::red;
}

QColor DomViewTauler::color_e(int equip) {
  if (equip == 0) return QColor(150, 0, 200);
  if (equip == 1) return QColor(200, 0, 0);
  if (equip == 2) return Qt::blue;
  if (equip == 3) return QColor(255, 150, 0);
  return Qt::red;
}

QColor DomViewTauler::aclara(QColor c, double p) {
  int r = c.red();
  int g = c.green();
  int b = c.blue();
  return QColor(r + (255 - r)*p,
                g + (255 - g)*p,
                b + (255 - b)*p);
}

void DomViewTauler::prepara(QPainter& painter, bool brush, QColor dins,
			    QColor fora, int gruix) {
  if (brush) painter.setBrush(dins);
  else painter.setBrush(Qt::NoBrush);
  painter.setPen(fora);
  QPen pen = painter.pen();
  pen.setWidth(gruix);
  painter.setPen(pen);
}

void DomViewTauler::initColors() {
  vC.resize(6);
  vC[0] = QColor("grey");
  vC[1] = color_e(0);
  vC[2] = color_e(1);
  vC[3] = color_e(2);
  vC[4] = color_e(3);
  vC[5] = QColor("black");

  vB.resize(6);
  fori(5) {
    vB[i] = QBrush(vC[i].light(170));
  }
  vB[5] = QBrush("grey");
}

void DomViewTauler::dibuixa(QPainter &painter, const Tauler &t, int turn) {
  int width = painter.device()->width();
  int height = painter.device()->height();
  assert(width==VIS and height==VIS);
  assert(turn>=0);

  painter.fillRect(0, 0, VIS, VIS, Qt::red);

  for (int x = 0; x < BOARD_SIZE; ++x)
    for (int y = 0; y < BOARD_SIZE; ++y) {
      int que = t.board[x][y].what;
      int id = t.board[x][y].id;
      int team = t.cycles[id].team() - 1;
      painter.fillRect(PIX*x, PIX*(BOARD_SIZE-1-y), PIX, PIX, color(que, team));
    }

  // pintem walls
  for (int i = 0; i < NUM_CYCLES; ++i ) {
    if (!t.cycles[i].dead) {
      int team = t.cycles[i].team() - 1;
      prepara(painter, true, color_e(team), color_e(team), PIX/2.5);
      Pos p = t.cycles[i].tail;
      while (p != t.cycles[i].head) {
	int dir = t.que(p).dir;
	Pos p2 = p.fwd(dir);
	painter.drawLine((p.x+0.5)*PIX, (BOARD_SIZE-1-p.y+0.5)*PIX,
			 (p2.x+0.5)*PIX, (BOARD_SIZE-1-p2.y+0.5)*PIX);
	p = p2;
      }
    }
  }
}
