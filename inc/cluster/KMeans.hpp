/******************************************************************************
* Filename      : KMeans.hpp
* Source File(s): KMeans.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef KMEANS_H
#define KMEANS_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <Vec.hpp>
#include <vector>

namespace algorithms
{
namespace clustering
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
class KMeans
{
    public:
        /* constructors */
        KMeans ( void ); /* default */
        KMeans ( int );
        KMeans ( const KMeans& ); /* copy */
        KMeans& operator= ( const KMeans& ); /* assign */
        ~KMeans ( void );
        /* functions */
        std::vector<int> cluster ( const Vec& , double );
        /* variables */
        int clusters;

    private:
};
}
}
#endif