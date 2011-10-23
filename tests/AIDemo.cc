
/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER Demo


/* ****************************************************************** */
/* Add any standard header you need here.                             */
/* ****************************************************************** */

#include "aibase.h"                           // Do not change this line
#include <vector>
using namespace std;


namespace NAMEPLAYER {                        // Do not change this line

    /* ************************************************************** */
    /* IMPORTANT! Do not use global variables.                        */
    /* However, it is okay to define const variables, functions       */
    /* typedefs, or structs/classes. Please do it here.               */
    /* ************************************************************** */

  const int P = 10;


    struct AIstruct: public AIbase {          // Do not change this line

        #include "initializer.h"              // Do not change this line

        /* ********************************************************** */
        /* Implement the function 'juga' here.                        */
        /* ********************************************************** */

        void juga() {
            for (int i = 0; i < NUM_CYCLES; ++i) {
                if (moto(i).team() == qui_soc() and not moto(i).dead) {
		    Pos next = moto(i).head.fwd(moto(i).dir);
		    // Canviem de direccio cada cert temps (a l'atzar),
		    // o quan estem a punt de pegar-nos-la
                    if (uniforme(0, 10) == 0 or que(next).what != EMPTY) {
	  	        // DIR_FIRST i DIR_LAST son la primera i la
		        // darrera direccio.
		        vector<int> dirs;
		        for (int j = DIR_FIRST; j <= DIR_LAST; ++j) {
			    next = moto(i).head.fwd(j);
			    if (que(next).what == EMPTY) {
			        dirs.push_back(j);
			    }
			}
			if (not dirs.empty()) {
			    ordena(i, dirs[uniforme(0, dirs.size()-1)]);
			}
			// El codi anterior no te en compte el
			// problema de la doble velocitat: aixo es
			// feina vostra.
                    }
                }
            }
        }

    };                                        // Do not change this line
    AIstruct::Static_Initializer init;        // Do not change this line
};                                            // Do not change this line

