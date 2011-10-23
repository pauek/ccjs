
/* ****************************************************************** */
/* IMPORTANT! Write here the name of your player.                     */
/* ****************************************************************** */

#define NAMEPLAYER null


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


    struct AIstruct: public AIbase {          // Do not change this line

        #include "initializer.h"              // Do not change this line

        /* ********************************************************** */
        /* Implement the function 'juga' here.                        */
        /* ********************************************************** */

        void juga() {
        }

    };                                        // Do not change this line
    AIstruct::Static_Initializer init;        // Do not change this line
};                                            // Do not change this line

