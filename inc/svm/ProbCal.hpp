/******************************************************************************
* Filename      : ProbCal.hpp
* Source File(s): ProbCal.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef ProbCal_H
#define ProbCal_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <vector>
#include "Machine.hpp"
#include "Kernel.hpp"

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
class ProbCal
{
    public:
        /* constructors */
        ProbCal ( void ); /* default */
        ProbCal ( const ProbCal& ); /* copy */
        ProbCal ( Machine*, const std::vector< Vec* >& , const std::vector<double>& );
        ProbCal& operator= ( const ProbCal& ); /* assign */
        ~ProbCal ( void );

        /* functions */
        double run ( void );
        double run ( bool );
        double loglikelihood ( const std::vector< Vec* >&, Vec* );
        double log1p ( double );

        /* variables */
        std::vector< Vec* > Inputs;
        Vec* Outputs;

        Vec* Distances;
        Vec* Targets;

        Machine * machine;

        // Parameter setting
        int maxIterations;
        double minStepSize;
        double sigma;
        double tolerance;

        int negatives;
        int positives;


    private:
};
}
}
#endif
