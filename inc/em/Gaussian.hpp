/******************************************************************************
* Filename      : Gaussian.hpp
* Source File(s): Gaussian.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef GAUSSIAN_H
#define GAUSSIAN_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <Vec.hpp>
#include <vector>
namespace algorithms
{
namespace em
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
class Gaussian
{
    public:
        /* constructors */
        Gaussian ( void ); /* default */
        Gaussian ( const Gaussian& ); /* copy */
        Gaussian& operator= ( const Gaussian& ); /* assign */
        ~Gaussian ( void );

        /* functions */
        double probability ( Vec* );
        void estimate ( const std::vector< Vec* >&,
                        const std::vector<double>&,
                        double );

        double probability1d ( double xi );
        void estimate1d ( const std::vector<double>&,
                          const std::vector<double>& );



        /* variables */
        Vec* means;
        Vec* covariance;
        double maxprob;

        double mean1d;
        double variance1d;

    private:
};
}
}
#endif
