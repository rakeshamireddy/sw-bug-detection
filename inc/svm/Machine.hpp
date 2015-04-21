/******************************************************************************
* Filename      : Machine.hpp
* Source File(s): Machine.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef Machine_H
#define Machine_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "Logit.hpp"
#include "Kernel.hpp"
#include <vector>

namespace algorithms
{
namespace svm
{
/*******************************************************************************
*  DEFINES
********************************************************************************/

/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class Machine
{
    public:
        /* constructors */
        Machine ( void ); /* default */
        Machine ( const Kernel&, int );
        Machine ( const Machine& ); /* copy */
        Machine& operator= ( const Machine& ); /* assign */
        ~Machine ( void );

        /* functions */
        int compute ( Vec*, double& );

        /* variables */
        Kernel kernel;
        Logit link;
        int inputCount;
        std::vector< Vec* > SupportVectors;
        Vec* Weights;
        double threshold;
        bool IsProbabilistic;
        bool IsCompact;

    private:
};
}
}
#endif
