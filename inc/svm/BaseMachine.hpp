/******************************************************************************
* Filename      : BaseMachine.hpp
* Source File(s): BaseMachine.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef BaseMachine_H
#define BaseMachine_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <vector>
#include "Machine.hpp"
#include "Kernel.hpp"
#include <Vec.hpp>

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
class BaseMachine
{
    public:
        /* constructors */
        BaseMachine ( void ); /* default */
        BaseMachine ( const BaseMachine& ); /* copy */
        BaseMachine ( Machine*, const std::vector< Vec* >& , const std::vector<double>& );
        BaseMachine& operator= ( const BaseMachine& ); /* assign */
        virtual ~BaseMachine ( void );

        /* functions */
        void set_weightratio ( double );
        double get_weightratio ( void );
        void run ( void );

        virtual void run ( Vec* ) = 0;

        double estimatecomplexity ( Kernel&, const std::vector< Vec* >&);

        /* variables */
        std::vector<Vec*> Inputs;

        Vec* Outputs;

        Vec* SampleWeights;

        bool useComplexityHeuristic;
        bool useClassLabelProportion;

        double complexity;
        double positiveWeight;
        double negativeWeight;

        double Cpositive;
        double Cnegative;

        double weightRatio;

        // Support Vector Machine parameters
        Machine * machine;
        Kernel kernel;

        bool isLinear;

    private:
};
}
}
#endif
