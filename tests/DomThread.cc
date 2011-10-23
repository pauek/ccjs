#include "DomThread.h"
#include "DomView.h"
#include "aibase.h"
#include <cassert>
#include <algorithm>
#include <iomanip>


DomThread::~DomThread() {}


DomThread::DomThread(vector<AIbase*> &ais, int seed,
		     DomView *dv, const string &output_filename,
		     QObject *parent): QThread(parent) {
  AIs = ais;
  T.init(seed);

  domview = dv;
  if (domview) domview->addTauler(T);

  write_output = output_filename!="";

  if (write_output) {
    ofs2.open(output_filename.c_str());
    if (not ofs2) {
      cerr << "Could not open file '" << (output_filename+".cs")
	   << "' for writting." << endl;
    }
    else {
      // CS: compressed info. No guardem la coleccio de taulers, sino la
      // coleccio d'ordres que han donat lloc als taulers.
      ofs2 << "_" << GAME_NAME << "_CS " << GAME_VERSION << endl;
      fori(4) {
	string name = ais[i]->name();
	assert(name.find_first_of(' ')==string::npos); //no valen espais!
	ofs2 << name << endl;
      }
      ofs2 << seed << endl;
      ofs2.flush();
    }
  }
}

void DomThread::run() {
  for (int i=0; i<4; ++i) {
    stringstream ssnom;
    ssnom << AIs[i]->name() << "(" << i+1 << ")";
  }

  int torn = 0;
  while (not T.tauler_final()) {
    ++torn;
    cerr << "Torn " << torn << "..." << endl;
    
    for (int i = 0; i<4; ++i) {
      stringstream ss1;
      T.write_tauler(ss1, i+1);
      
      AIs[i]->_T.read_tauler(ss1);      
      cerr << " " << (i+1) << "..." << endl;
      AIs[i]->juga();

      stringstream ss2;      
      AIs[i]->_T.write_ordres(ss2);
      T.read_ordres(ss2, i+1);
    }

    T.fes_torn();

    if (domview) domview->addTauler(T);

    if (write_output) {
      //guardem les ordres donades...
      for (int i = 0; i<4; ++i) {
	AIs[i]->_T.write_ordres(ofs2);
	ofs2 << endl;
      }
      ofs2.flush();
    }
  }
  cerr << endl << "The match is finished." << endl;
  
  cerr << endl << "Result:" << endl;
  for(int i=0;i<4;++i) {
    cout << T.puntuacio(i+1) << endl;
  }
}

