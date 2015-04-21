/******************************************************************************
* Filename      : SMO.hpp
* Source File(s): SMO.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef SMO_H
#define SMO_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "BaseMachine.hpp"
#include "Machine.hpp"
#include "KernelCache.hpp"
#include <vector>
#include <unordered_set>
#include <mutex>

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
class SMO : public BaseMachine
{
    public:
        enum selstrat { SEQUENTIAL=0, WORSTPAIR };

        /* constructors */
        SMO ( void ); /* default */
        SMO ( Machine*,
              const std::vector< Vec* >&,
              const std::vector<double>& );
        SMO ( const SMO& ); /* copy */
        SMO& operator= ( const SMO& ); /* assign */
        ~SMO ( void );

        /* functions */
        void run ( void );
        //void run ( const std::vector<double>& );
        void run ( Vec* );

        /* variables */

        // Learning algorithm parameters
        double tolerance;
        double epsilon;
        Vec * C;

        // Support Vetor Machine parameters
        Vec * Alpha;
        Vec * Weights;

        bool isCompact;

        std::unordered_set<int> activeExamples;
        std::unordered_set<int> nonBoundExamples;
        std::unordered_set<int> atBoundsExamples;

        // Keerthi's improvements
        int i_lower;
        int i_upper;
        double b_upper;
        double b_lower;

        Vec* Errors;

        int cacheSize;
        KernelCache * kernelCache;

        enum selstrat strategy;

        int maxChecks;

        std::mutex _mutex;

    private:
        bool examineExample ( int );
        bool takeStep ( int, int );
        int I ( int );
        void updateSets ( int, double );
        double computeNoBias ( int );
};
}
}
#endif
