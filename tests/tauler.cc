// **************************************************
// DO NOT CHANGE THIS FILE
// **************************************************

#include "tauler.h"
#include "serialize.h"

using namespace std;
using namespace serialize;



const int Pos::dx[5] = {0, 0, -1, 0, 1};
const int Pos::dy[5] = {0, -1, 0, 1, 0};

int Cycle::team() const {
    if (id == -1) return -1;
    return 1 + id/NUM_CYCLES_TEAM;
}

/// Serialitzacions per a tipus especifics de tauler

istream &operator>>(istream &is, Pos &p) {
    return is >> p.x >> p.y;
}

ostream &operator<<(ostream &os, const Pos &p) {
    return os << p.x << " " << p.y;
}

istream &operator>>(istream& is, Info& i) {
    return is >> i.what >> i.id >> i.dir;
}

ostream &operator<<(ostream& os, const Info& i) {
    return os << i.what << " " << i.id << " " << i.dir;
}

istream &operator>>(istream& is, Cycle& c) {
    return is >> c.head >> c.tail >> c.id >> c.dir >> c.dead;
}

ostream &operator<<(ostream& os, const Cycle& c) {
    return os << c.head << " " << c.tail << " "
           << c.id << " " << c.dir << " " << c.dead;
}


/// ***********************************************************
/// Metodes que és necessari implementar
///

/// joc_init()
///
/// Aquest metode crea el tauler inicial, i inicialitza totes les
/// variables que necessita un tauler (tant aquelles que es guardaran a
/// l'estat de la partida, com les que no). Si el taulell inicial es
/// aleatori, ha de fer servir el generador de nombres aleatoris 'A'
/// per a crear-lo (d'aquesta manera es garantitza que partides amb la
/// mateixa llavor tindran la mateixa posicio inicial).
///
void Tauler::joc_init() {
    const Info buida(EMPTY, -1, -1);
    board = VVInfo(BOARD_SIZE, VInfo(BOARD_SIZE, buida));

    // Pantalla no toroidal
    const Info block(BLOCK, -1, -1);
    for (int i=0;i<BOARD_SIZE;++i) {
        board[i][0] = board[i][BOARD_SIZE-1] =
                          board[0][i] = board[BOARD_SIZE-1][i] = block;
    }

    /*

    const int NUM_MAX_BLOCKS = 4;
    const int NUM_MIN_BLOCKS = 6;
    const int SIZE_MAX_BLOCKS = 8;
    const int SIZE_MIN_BLOCKS = 4;

    // Genera blocks a l'atzar
    int num_blocks = A.uniforme(NUM_MIN_BLOCKS, NUM_MAX_BLOCKS);
    for (int i=0; i<num_blocks; ++i) {
        int m = A.uniforme(SIZE_MIN_BLOCKS, SIZE_MAX_BLOCKS);
        int x = A.uniforme(m, BOARD_SIZE-m-1);
        int y = A.uniforme(m, BOARD_SIZE-m-1);
        afegeix_block(x, y, m);
    }


    // Genera rombos a l'atzar
    num_blocks = A.uniforme(NUM_MIN_BLOCKS, NUM_MAX_BLOCKS);
    for (int i=0; i<num_blocks; ++i) {
        int m = 1+2*A.uniforme(1,8);
        int x = A.uniforme(m, BOARD_SIZE-m-1);
        int y = A.uniforme(m, BOARD_SIZE-m-1);
        afegeix_rombo(x, y, m);
    }
    */



    {
        int b = BOARD_SIZE/4;
        int m = 5+ 2*A.uniforme(2, 3);
        if (A.uniforme(0,1)) afegeix_block(b, b, m); else afegeix_rombo(b-m, b-m, m*2+1);
        m = 5+ 2*A.uniforme(2, 3);
        if (A.uniforme(0,1)) afegeix_block(3*b, 3*b, m); else afegeix_rombo(3*b-m, 3*b-m, m*2+1);
        m = 5+ 2*A.uniforme(2, 3);
        if (A.uniforme(0,1)) afegeix_block(3*b, b, m); else afegeix_rombo(3*b-m, b-m, m*2+1);
        m = 5+ 2*A.uniforme(2, 3);
        if (A.uniforme(0,1)) afegeix_block(b, 3*b, m); else afegeix_rombo(b-m, 3*b-m, m*2+1);

    }

    for (int i=1; i<BOARD_SIZE-1; ++i) {
        for (int j=1; j<BOARD_SIZE-1; ++j) {
            if (!A.uniforme(0,10)) {
                board[i][j] = Info(EMPTY, -1, -1);
    }   }   }


    if (!A.uniforme(0,5)) {
        for (int i=4; i<BOARD_SIZE-4; ++i) {
            board[i][BOARD_SIZE/2] = block;
            board[BOARD_SIZE/2][i] = block;
        }
        board[BOARD_SIZE/2][BOARD_SIZE/2] = Info(EMPTY, -1, -1);
        board[BOARD_SIZE/2+1][BOARD_SIZE/2] = Info(EMPTY, -1, -1);
        board[BOARD_SIZE/2-1][BOARD_SIZE/2] = Info(EMPTY, -1, -1);
        board[BOARD_SIZE/2][BOARD_SIZE/2+1] = Info(EMPTY, -1, -1);
        board[BOARD_SIZE/2][BOARD_SIZE/2-1] = Info(EMPTY, -1, -1);
        for (int i=0;i<A.uniforme(1,3); ++i) {
            int k = A.uniforme(10, BOARD_SIZE/2-10);
            board[BOARD_SIZE/2][BOARD_SIZE/2+k] = Info(EMPTY, -1, -1);
            board[BOARD_SIZE/2][BOARD_SIZE/2-k] = Info(EMPTY, -1, -1);
            board[BOARD_SIZE/2+k][BOARD_SIZE/2] = Info(EMPTY, -1, -1);
            board[BOARD_SIZE/2-k][BOARD_SIZE/2] = Info(EMPTY, -1, -1);
        }
    }


    // Posiciona les motos
    cycles = VCycle(NUM_CYCLES);
    for (int i = 0; i < NUM_CYCLES; ++i) {
        afegeix_moto(i);
    }

    // Ordres
    ordres = VE(NUM_CYCLES);
}


/// joc_fes_torn()
///
/// Fes avancar un torn l'estat actual de la partida. Quan s'executa aquest
/// metode, assumeix que has rebut les ordres de tots els jugadors. Si el joc
/// te comportament aleatori, fes servir el generador de nombres aleatoris A.
void Tauler::joc_fes_torn() {
    // Primer fem avancar un pas a totes les motos que van rapid

    // els consistency_check estan per a debugar: no haurien de saltar mai
    consistency_check();

    vector<int> nous_morts(NUM_CYCLES, false);
    vector<Pos> posicio_on_mor(NUM_CYCLES, Pos());
    vector<int> perm = A.permutacio(NUM_CYCLES);
    // Primer: fem avancar les motos que van a doble velocitat un paset
    for (int i = 0; i < NUM_CYCLES; ++i) {
        const int id = perm[i];
        // Nomes les no-mortes i les que van a doble velocitat
        if (!cycles[id].dead && cycles[id].dir == ordres[id]) {
            const Pos p2 = cycles[id].head.fwd(ordres[id]);
            if (que(p2).what != EMPTY) {
                nous_morts[id] = true;
                posicio_on_mor[id] = p2;
                //	cycles[id].head = p2;
                //	cycles[id].dead = quin_torn(); // el torn actual
                if (que(p2).what == CYCLE) {
                    // Xoc frontal: mor una altra moto!
                    const int id2 = que(p2).id;
                    nous_morts[id2] = true;
                    posicio_on_mor[id2] = p2;
                    //	  cycles[id2].dead = quin_torn(); // el torn actual
                }
            } else {
                // Pot avancar sense problema.
                mut_que(cycles[id].head).what = WALL;
                cycles[id].head = p2;
                mut_que(p2) = Info(CYCLE, id, cycles[id].dir);
            }
        }
    }

    consistency_check();

    // Segon: totes les motos avancen ara un paset
    for (int i = 0; i < NUM_CYCLES; ++i) {
        const int id = perm[i];
        if (!cycles[id].dead && !nous_morts[id]) {
            int dir = ordres[id];
            if (dir == NO_DIR) dir = cycles[id].dir;
            assert(dir >= DIR_FIRST && dir <= DIR_LAST);
            assert(que(cycles[id].head).what == CYCLE);
            Pos p2 = cycles[id].head.fwd(dir);
            if (que(p2).what != EMPTY) {
                nous_morts[id] = true;
                posicio_on_mor[id] = p2;
                //	cycles[id].head = p2;
                //	cycles[id].dead = quin_torn(); // el torn actual
                if (que(p2).what == CYCLE) {
                    // Xoc frontal: mor una altra moto!
                    int id2 = que(p2).id;
                    nous_morts[id2] = true;
                    posicio_on_mor[id2] = p2;
                    //	  cycles[id2].dead = quin_torn(); // el torn actual
                }
            } else {
                // Pot avancar sense problema.
                mut_que(cycles[id].head).what = WALL;
                mut_que(cycles[id].head).dir = dir;
                cycles[id].head = p2;
                cycles[id].dir = dir;
                mut_que(p2) = Info(CYCLE, id, cycles[id].dir);
            }
        }
    }

    consistency_check();

    // Esborrem les esteles de les morts que han dead aquest torn, "a sac".
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Info &info = board[i][j];
            if ((info.what==WALL or info.what==CYCLE) and nous_morts[info.id]) {
                info = Info(EMPTY, -1, -1);
            }
        }
    }
    // A mes, netegem la informacio de cycles
    for (int i = 0; i < NUM_CYCLES; ++i) {
        if (nous_morts[i]) {
            cycles[i].dead = quin_torn();
            cycles[i].dir = -1;
            cycles[i].head = cycles[i].tail = Pos();
        }
    }

    consistency_check();

    // Si una moto ha xocat contra un Wall d'algu (viu), retallem la cua del
    // troc on ha xocat.
    for (int i = 0; i < NUM_CYCLES; ++i) {
        Pos ptall = posicio_on_mor[i];
        if (ptall != Pos() and que(ptall).what == WALL) {
            const int id_cua = que(ptall).id;
            Pos p = cycles[id_cua].tail;
            int dir = que(p).dir;
            while (p != ptall) {
                assert(que(p).what == WALL and que(p).id == id_cua);
                mut_que(p) = Info(EMPTY, -1, -1);
                p = p.fwd(dir);
                dir = que(p).dir;
            }
            cycles[id_cua].tail = p;
        }
    }

    consistency_check();
}

/// joc_puntuacio(int equip)
///
/// Calcula la puntuacio de l'equip (1-4) demanat. No facis servir nombres
/// negatius.
int Tauler::joc_puntuacio(int equip) const {
    int vius = 0;
    int maxtorn = 0;
    for (int i = 0; i < NUM_CYCLES_TEAM; ++i) {
        const int id = (equip - 1)*NUM_CYCLES_TEAM + i;
        if (!cycles[id].dead) vius++;
        else maxtorn = max(maxtorn, cycles[id].dead);
    }
    if (vius == 0) return maxtorn; // s'ha acabat la seva partida
    else return quin_torn() + vius*10000;
}

/// joc_write_tauler(os, int equip)
///
/// Serialitza aquella part del tauler que el programa principal ha de
/// passar al jugador equip per a que aquest pugui fer el seu
/// torn. Aquesta informacio sera llegida per joc_read_tauler, creant
/// un 'tauler de jugador' en el proces del jugador destinatari
/// (d'aquesta manera la informacio secreta no arribara a viure en el
/// proces del jugador). Si el joc no es d'informacio secreta, no cal
/// amagar res.
void Tauler::joc_write_tauler(ostream &os, int /* equip */) const {
    os << board << " " << cycles;
}

/// joc_read_tauler(is)
///
/// Rep el tauler, tal i com el veuria un jugador (es a dir: potser no
/// hi ha la informacio complerta, sino nomes la informacio que el
/// jugador necessita). Inicialitza els vectors o les dades
/// addicionals que necessitis. Quan aquest metode s'executa, pots
/// assumir que tens acces al torn actula (quin_torn()) i al jugador
/// per al qual estas llegint la informacio (qui_soc()).
void Tauler::joc_read_tauler(istream &is) {
    is >> board >> cycles;
    ordres = VE(NUM_CYCLES);
}

/// joc_write_ordres(os, int equip)
///
/// Com joc_write_tauler, pero per a passar les ordres del jugador
/// equip (1-4) al tauler. A diferencia del cas anterior, les dades no
/// es llegiran en un tauler buit, sino que es llegiran en un tauler
/// ja inicialitzat.
void Tauler::joc_write_ordres(ostream &os, int /* e equip*/) const {
    os << ordres;
}

/// joc_read_ordres(os, int equip)
///
/// Llegeix les ordres emeses pel jugador equip (1-4). Aquest metode es
/// crida des d'un tauler ja inicialitzat. Comprova, a mes a mes, que les
/// ordres siguin vàlides.
void Tauler::joc_read_ordres(istream &is, int equip) {
    VE ordres_llegides;
    is >> ordres_llegides;
    for (int i = 0; i < NUM_CYCLES_TEAM; ++i) {
        const int id = (equip - 1)*NUM_CYCLES_TEAM + i;
        ordres[id] = ordres_llegides[id];

        if (cycles[id].dead && ordres[id] != NO_DIR) {
            error("Equip " + num(equip) +
                  " dona ordre " + num(ordres[id]) +
                  " a MOTO MORTA amb id " + num(id));
            ordres[id] = NO_DIR;
        } else if (ordres[id] < NO_DIR or ordres[id] > DIR_LAST) {
            error("Equip " + num(equip) +
                  " dona ORDRE INVALIDA " + num(ordres[id]) +
                  " a moto amb id " + num(id));
            ordres[id] = NO_DIR;
        }
    }
}

/// joc_tauler_final
///
/// Retorna cert si aquest es l'ultim tauler del joc. La puntuacio dels
/// jugadors
bool Tauler::joc_tauler_final() const {
    map<int, int> last_torn_team;
    for (int i = 0; i < NUM_CYCLES; ++i) {
        const int team = cycles[i].team();
        if (cycles[i].dead) {
            last_torn_team[team] = max(last_torn_team[team],
                                       cycles[i].dead);
        } else {
            last_torn_team[team] = max(last_torn_team[team],
                                       1000000000);
	}
    }
    int torn_ref = quin_torn() - EXTRA_ROUNDS;
    int equips_vius = 0;
    for (int i = 1; i <= 4; ++i) {
        if (last_torn_team[i] >= torn_ref) ++equips_vius;
    }
    return equips_vius <= 1;
}

Info Tauler::que(int x, int y) const {
    if (x < 0 or x >= BOARD_SIZE or y < 0 or y >= BOARD_SIZE) {
        error("que(x,y) invocat amb x=" + num(x) + " y=" + num(y));
        return Info();
    }
    return board[x][y];
}

Info Tauler::que(const Pos& p) const {
    const int x = p.x, y = p.y;
    if (x < 0 or x >= BOARD_SIZE or y < 0 or y >= BOARD_SIZE) {
        error("que(p) invocat amb p.x=" + num(x) + " p.y=" + num(y));
        return Info();
    }
    return board[x][y];
}

Cycle Tauler::moto(int id) const {
    if (id < 0 or id > NUM_CYCLES-1) {
        error("moto(id) invocat amb id=" + num(id));
        return Cycle();
    }
    return cycles[id];
}

Cycle Tauler::moto(int x, int y) const {
    if (x < 0 or x >= BOARD_SIZE or y < 0 or y >= BOARD_SIZE) {
        error("moto(x,y) invocat amb x=" + num(x) + " y=" + num(y));
        return Cycle();
    }
    if (board[x][y].what == WALL or board[x][y].what == CYCLE) {
        return cycles[board[x][y].id];
    }
    return Cycle();
}

Cycle Tauler::moto(const Pos& p) const {
    const int x = p.x, y = p.y;
    if (x < 0 or x >= BOARD_SIZE or y < 0 or y >= BOARD_SIZE) {
        error("moto(p) invocat amb p.x=" + num(x) + " p.y=" + num(y));
        return Cycle();
    }
    if (board[x][y].what == WALL or board[x][y].what == CYCLE) {
        return cycles[board[x][y].id];
    }
    return Cycle();
}

void Tauler::ordena(int id, int dir) {
    int equip = qui_soc() - 1;
    if (id < NUM_CYCLES_TEAM*equip or id >= NUM_CYCLES_TEAM*(equip + 1)) {
        error("ordena(id,dir) invocat amb moto aliena id=" + num(id));
        return;
    }
    if (dir < NO_DIR or dir > DIR_LAST) {
        error("ordena(id,dir) invocat amb direccio dir=" + num(dir));
        return;
    }
    ordres[id] = dir;
}



void Tauler::consistency_check() {
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            Info i = board[x][y];
            if (i.what == EMPTY || i.what == BLOCK) {
                assert(i.id == -1 && i.dir == -1);
            } else if (i.what == CYCLE || i.what == WALL) {
                assert(i.id >=0 && i.id < NUM_CYCLES);
                assert(i.dir >= DIR_FIRST && i.dir <= DIR_LAST);
                assert(cycles[i.id].dead == 0);
            }
        }
    }
    for (int i = 0; i < NUM_CYCLES; ++i) {
        assert(cycles[i].id == i);
        if (cycles[i].dead) {
            assert(cycles[i].head == Pos());
            assert(cycles[i].tail == Pos());
            assert(cycles[i].dir == -1);
        } else {
            assert(que(cycles[i].tail).what == WALL);
            assert(que(cycles[i].tail).id == i);
            assert(que(cycles[i].head).what == CYCLE);
            assert(que(cycles[i].head).id == i);
            Pos p = cycles[i].tail;
            int dir = que(cycles[i].tail).dir;
            while (p != cycles[i].head) {
                assert(que(p).what == WALL);
                assert(que(p).id == i);
                p = p.fwd(dir);
                dir = que(p).dir;
                assert(dir >= DIR_FIRST && dir <= DIR_LAST);
            }
        }
    }
}


void Tauler::afegeix_block(int x, int y, int size) {
    int style = 0;
    const Info buida(EMPTY, -1, -1);
    const Info block(BLOCK, -1, -1);
    for (int i = -size+1; i < size; ++i) {
        int a = min(i-(-size+1), (size-1)-i);
        for (int j = -size+1; j < size; ++j) {
            int b = min(j-(-size+1), (size-1)-j);
            const Info &bl = (style || min(a,b)%2==0) ? block : buida;
            int px = x + i;
            int py = y + j;
            if (px<0 || py<0 || px>BOARD_SIZE-1 || py>BOARD_SIZE-1) continue;
            board[px][py] = bl;
        }
    }
}



void Tauler::afegeix_rombo(int x, int y, int size) {
    const Info buida(EMPTY, -1, -1);
    const Info block(BLOCK, -1, -1);

    int n = size;
    int m = n/2;

    for (int i=0; i<=m; ++i) {
        for (int j=m-i; j<=m; j+=3) {
            board[x+i][y+j]=block;
            board[x+i][y+n-j-1]=block;
            board[x+n-i-1][y+j]=block;
            board[x+n-i-1][y+n-j-1]=block;
        }
    }
}



void Tauler::afegeix_moto(int id) {
    const int FREE_DIST = 2;
    int dir = DIR_FIRST+id/4;
    int x, y;
    bool free_space;
    int retry = 0;
    do {
        ++retry;
        x = A.uniforme(BOARD_SIZE/6, BOARD_SIZE*5/6);
        y = BOARD_SIZE-A.uniforme(FREE_DIST+1, BOARD_SIZE/6);
        for (int k = 0; k < id/NUM_CYCLES_TEAM; ++k) rota(x, y);

        // comprovem que la moto tingui un espai buit de radi FREE_DIST
        free_space = true;
        for (int i = -FREE_DIST; free_space && i <= FREE_DIST; ++i)
            for (int j = -FREE_DIST; free_space && j <= FREE_DIST; ++j) {
                int cx = x+i;
                int cy = y+j;
                if (cx < 0 or cy < 0 or cx > BOARD_SIZE-1 or cy > BOARD_SIZE-1) {
                    continue;
                }
                if (board[cx][cy].what != EMPTY) free_space = false;
            }
    } while (retry < 1000 && !free_space);
    assert(retry < 1000);

    Pos p(x,y);
    board[p.x][p.y] = Info(CYCLE, id, dir);
    Pos p2 = p.back(dir);
    board[p2.x][p2.y] = Info(WALL, id, dir);
    cycles[id] = Cycle(p, p2, id, dir);
}
