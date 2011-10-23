#include "taulerbase.h"
using namespace std;


int TaulerBase::uniforme(int e, int d) {
  assert(es_jugador());
  if (e > d) {
    error("uniforme invocat amb " + num(e) + " " + num(d));
    return -1;
  }
  return at[jugador].uniforme(e, d);
}

vector<int> TaulerBase::permutacio(int n) {
  assert(es_jugador());
  if (n < 0) {
    error("permutacio invocat amb " + num(n));
    return vector<int>(0);
  }
  return at[jugador].permutacio(n);
}

bool TaulerBase::probabilitat(double p) {
  assert(es_jugador());
  if (p < 0 or p > 1) {
    error("probabilitat invocat amb " + num_real(p));
    return false;
  }
  return at[jugador].probabilitat(p);
}

void TaulerBase::read_ordres(istream &is, int equip) {
  assert(es_principal());

  // comprovacions
  int readtorn, readjugador, readllavor;
  is >> readtorn >> readjugador >> readllavor;
  if (readtorn!=torn or readjugador!=equip) {
    error("ignorem read_ordres equip "+num(equip));
    return;
  }
  at[equip]=atzar(readllavor);
  
  joc_read_ordres(is, equip);
}

void TaulerBase::write_ordres(ostream &os, int equip) const {
  if (equip==-1) equip = jugador;
  assert(equip>0);
  os << torn 
     << " " << equip
     << " " << at[equip].llavor
     << " ";
  joc_write_ordres(os, equip);
}

void TaulerBase::read_tauler(istream &is) {
  int llavor;
  is >> torn >> jugador >> llavor;
  assert(es_jugador());
  at = vector<atzar>(5);
  at[jugador]=atzar(llavor);
  joc_read_tauler(is);
}

void TaulerBase::write_tauler(ostream &os, int equip) const {
  //nomes es pot cridar en un taulell principal
  assert(es_principal()); 
  os << torn 
     << " " << equip              //<-- equip, i no pas jugador
     << " " << at[equip].llavor  //<-- nomes la llavor propia
     << " ";
  joc_write_tauler(os, equip);
}

int TaulerBase::puntuacio(int equip) const {
  assert(equip>=1 and equip<=num_jugadors());
  return joc_puntuacio(equip);
}

void TaulerBase::fes_torn() {
  joc_fes_torn();
  ++torn;
}

void TaulerBase::init(int llavor) {
  torn = 1;
  jugador = 0;
  
  int num_jug = num_jugadors();
  A = atzar(llavor);
  at = vector<atzar>(num_jug+1);
  for (int i = 1; i <= num_jug; ++i) at[i] = atzar(A.uniforme(1, 100000));

  joc_init();
}

//  Retorna cert si aquest és el tauler final del joc, amb l'estat final
// de la partida. (Les AIs no es criden en l'ultim tauler).
bool TaulerBase::tauler_final() const {
  return joc_tauler_final();
}

// Retorna el numero de jugadors del joc (per defecte, 4, pero
// es pot overloadejar en Tauler)
int TaulerBase::num_jugadors() const {
  return joc_num_jugadors();
}





