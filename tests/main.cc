#include "aibase.h"
#include "tauler.h"
#include "common.h"

#include <iostream>
#include <cstdlib>  //'time' function, to select a seed
#include <cassert>
#include <algorithm>

#include <QApplication>
#include "DomWin.h"
#include "DomThread.h"

using namespace std;

vector<AIbase*> AIs;

map<string, string> parse(int argc, char **argv) {
  int esp = 0;
  string filename;
  map<string, string> m;
  for(int i=1;i<argc;++i) {
    string s(argv[i]);
    if (s.size()>2 and s[0]=='-' and s[1]=='-') {
      //      argv[i][0]=0; //never process the argument again
      int poseq = s.find_first_of('=');
      if (poseq!=(int)string::npos) {
	m[ s.substr(2, poseq-2) ] = s.substr(poseq+1);
      } else {
	m[ s.substr(2) ] = "";
      }
    }
    else {
      if (esp==0) filename=s;
      ++esp;
    }
  }
  if (esp==1) {
    //hi havia una unica opcio sense '--': es un fitxer
    m["in"] = filename;
  }
  return m;
}

void show_usage(char **argv) {
  cerr << "Usage:" << endl;
  cerr << "  "  << argv[0]
       << " <player1> <player2> <player3> <player4> (options) (<seed>)" << endl;
  cerr << "  "  << argv[0]
       << " <input-filename>" << endl;
  cerr << endl;
  AIbase::check_registrants(true);
  cerr << endl;
  cerr << "Options:" << endl;
  cerr << "  --seed=<seed>            (initial random seed)" << endl;
  cerr << "  --champ=<input-filename> (replay championship file)"
       << endl;
  cerr << "  --in=<input-filename>    (replay saved match)"
       << endl;
  cerr << "  --out=<output-filename>  (save match to file)"
       << endl;
  cerr << "  --nogui                  (play match without showing it)"
       << endl;
  cerr << "  --image                  (when replaying match, only save images)"
       << endl;
}



int play_game_from_file(map<string,string> &m, int argc, char **argv) {
  string ignore[] = {"nogui", "seed", "out", ""};
  {
    int i=-1;
    while (ignore[++i]!="") {
      if (m.find(ignore[i])!=m.end()) {
	cerr << "Ignoring command line argument '" << ignore[i]
	     << "'." << endl;
      }
    }
  }

  vector<string> matches;
  if (m.find("in")!=m.end()) {
    matches.push_back(m["in"]);
  }

  if (m.find("champ")!=m.end()) {
    ifstream fmat(m["champ"].c_str());
    string line;
    while (getline(fmat, line)) {
      if (not line.empty() and line[0]!='#') {
	matches.push_back(line);
      }
    }
  }

  assert(not matches.empty());

  bool fullscreen = false;
  int speed = DomViewTauler::default_speed_ms;
  int fontsize = 20;

  foreach(filein, matches) {
    //interpret commands from 'championship' file

    //some commands for visualization
    if ((*filein)[0] == '-') {
      string option = filein->substr(1);
      if (option=="fullscreen") fullscreen=true;
      else if (option=="normalscreen") fullscreen=false;
      else if (option.substr(0,6)=="speed ") {
	istringstream iss(option);
	string st;
	iss >> st >> speed;
      }
      else if (option.substr(0,9)=="fontsize ") {
	istringstream iss(option);
	string st;
	iss >> st >> fontsize;
      }
      continue;
    }

    //execute command
    if ((*filein)[0] == '`') {
      int ret = system(filein->substr(1).c_str());
      assert(ret!=-1);
      continue;
    }

    //otherwise: play file
    ifstream ifs(filein->c_str());
    if (not ifs) {
      cerr << "Could not open file '" << (*filein) << "' for reading." << endl;
      return 1;
    }

    string idline;
    string version;
    ifs >> idline >> version;
    bool cs_version;
    if (idline==string("_")+GAME_NAME+"_CS") cs_version=true;
    else if (idline==string("_")+GAME_NAME) cs_version=false;
    else {
      cerr << "File '" << (*filein)
	   << "' does not contain a valid match." << endl;
      cerr << "Are you sure it is a " << GAME_NAME << " file?" << endl;
      return 1;
    }

    if (version!=GAME_VERSION) {
      cerr << "File '" << (*filein)
	   << "' is in unsupported version " << version << endl;
      cerr << "(Current supported version(s): " << GAME_VERSION
	   << ")" << endl;
      return 1;
    }

    vector<string> names(4);
    fori(4) ifs >> names[i];
    int seed;
    ifs >> seed;

    if (not ifs) {
      cerr << "Could not process correctly file '" << (*filein) << "'." << endl;
      return 1;
    }

    vector<Tauler> vt;
    if (not cs_version) {
      assert(0);
    }
    else {
      //aqui hem de simular la partida amb les ordres.
      Tauler T;
      T.init(seed);
      vt.push_back(T); //tauler inicial

      while (not T.tauler_final()) {
	//ara, llegim les ordres del 'ifs'
	for (int i=1; i<=4; ++i) {
	  T.read_ordres(ifs, i);
	}

	T.fes_torn();
	vt.push_back(T);
	cerr << ".";
      }
      cerr << endl;
    }

    QApplication app(argc, argv);

    DomWin dw(names, fontsize);

    dw.dv->setSpeed(speed);
    dw.dv->setStop();

    foreach(i, vt) {
      dw.dv->addTauler(*i);
    }
    if (fullscreen) dw.setWindowState(Qt::WindowFullScreen);

    if (m.find("image")==m.end()) {
      dw.show();
      app.exec();
    }
    else {
      //no fa falta fer el show de "dw": n'hi ha prou amb
      //cridar al metode "saveImages"
      dw.dv->saveImages(*filein);
    }
  }
  return 0;
}



int play_game_from_arguments(map<string,string> &m, int argc, char **argv) {
  vector<string> names;

  int speed = DomViewTauler::default_speed_ms;
  ////read players from command line
  int par = 1;
  int i=0;
  while (par<argc and i<4) {
    string nom = string(argv[par++]);
    if (nom.size()>0 and nom[0]!='-') {
      names.push_back(nom);

      if ( (AIs[i++]=AIbase::instantiate_player(nom)) == NULL ) {
	cerr << "Cannot play match: there is no player AI with name  '" << nom
	     << "'." << endl;
	return 1;
      }
    }
  }

  //// do we have enough players?
  if (i<4) {
    cerr << "Not enough player AIs to play match." << endl;
    show_usage(argv);
    return 1;
  }

  //// seed
  int seed = 0;
  if (m.find("seed")!=m.end()) {
    seed = s2i(m["seed"]);
  }
  else {  //we look for a seed number at the end of the options
    bool seedfound = false;
    while (par<argc and not seedfound) {
      string s(argv[par++]);
      istringstream iss(s);
      if (iss >> seed) seedfound=true;
    }
    if (not seedfound) seed=time(0);
  }

  //default game parameters

  QApplication app(argc, argv);

  if (m.find("nogui")!=m.end()) {
    DomThread dt(AIs, seed, NULL,
		 m["out"],     //out: if empty, write no file
		 qApp);
    dt.run_in_own_thread();
    return 0;
  }
  else {
    DomWin dw(names);
    DomThread dt(AIs, seed, dw.dv,
		 m["out"],      //out: if empty, write no file
		 qApp);
    dw.dv->setSpeed(speed);
    dw.dv->setStop();
    dt.start();
    dw.show();
    return app.exec();
  }
}



int main(int argc, char **argv) {
  if (not AIbase::check_registrants()) {
    cerr << endl;
    cerr << "You must recompile " << argv[0] << endl;
    return 1;
  }

  AIs.resize(4);

  map<string, string> m = parse(argc, argv);

  set<string> known;
  known.insert("champ");
  known.insert("in");
  known.insert("out");
  known.insert("seed");
  known.insert("nogui");
  known.insert("image");

  foreach(i, m) {
    if (known.find(i->first)==known.end()) {
      cerr << "Warning: unknown option '" << i->first << "'." << endl;
    }
  }

  if (m.find("in")!=m.end() or m.find("champ")!=m.end()) {
    return play_game_from_file(m, argc, argv);
  }
  else {
    assert(m.find("image")==m.end());
    return play_game_from_arguments(m, argc, argv);
  }
}
