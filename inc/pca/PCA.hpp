/******************************************************************************
* Filename      : PCA.hpp
* Source File(s): PCA.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef PCA_H
#define PCA_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <vector>

namespace algorithms
{
namespace pca
{
/*******************************************************************************
*  DEFINES
********************************************************************************/
#define SIGN(a, b) ( (b) < 0 ? -fabs(a) : fabs(a) )

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
class PCA
{
    public: 
        /* constructors */
        PCA ( void ); /* default */
        PCA ( const PCA& ); /* copy */
        PCA& operator= ( const PCA& ); /* assign */
        ~PCA ( void );

        /* functions */
        std::vector< std::vector<double> > reduce ( std::vector<std::vector<double> > );

        /* variables */

    private:
        /* functions */
        std::vector< std::vector<double> > run ( std::vector<std::vector<double> >, int );
        void tqli ( std::vector<double>&, std::vector<double>&, int, std::vector< std::vector<double> >& );
        void tred2 ( std::vector< std::vector<double> >&, int, std::vector<double>&, std::vector<double>& );
        void scpcol ( std::vector< std::vector<double> >&, int, int, std::vector< std::vector<double> >& );
        void covcol ( std::vector< std::vector<double> >&, int, int, std::vector< std::vector<double> >& );
        void corcol ( std::vector< std::vector<double> >&, int, int, std::vector< std::vector<double> >& );        

        /* variables */

};
}
}
#endif
