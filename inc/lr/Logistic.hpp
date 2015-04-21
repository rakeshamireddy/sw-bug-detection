/******************************************************************************
* Filename      : Logistic.hpp
* Source File(s): Logistic.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <Vec.hpp>
#include "LogitLink.hpp"
namespace algorithms
{
namespace regression
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
class Logistic
{
    public:
        /* constructors */
        Logistic ( void ); /* default */
        Logistic ( int );
        Logistic ( int, int );
        Logistic ( const Logistic& ); /* copy */
        Logistic& operator= ( const Logistic& ); /* assign */
        ~Logistic ( void );
        /* functions */
        Vec* compute ( Vec* );
        double compute2 ( Vec* );
        double odds ( int );
        double odds ( int, int );

        /* variables */
        Vec* Coefficients = NULL;
        Vec* StandardErrors = NULL;
        int inputs;
        int categories;
        LogitLink linkfunction;

    private:
};
}
}
#endif
