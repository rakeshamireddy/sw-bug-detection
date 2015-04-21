/******************************************************************************
* Filename      : KernelCache.hpp
* Source File(s): KernelCache.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef KERNELCACHE_H
#define KERNELCACHE_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "Kernel.hpp"
#include <unordered_map>
#include <list>
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
class KernelCache
{
    public:
        /* constructors */
        KernelCache ( void ); /* default */
        KernelCache ( const Kernel&, const std::vector< Vec* >&, int );
        KernelCache ( const KernelCache& ); /* copy */
        KernelCache& operator= ( const KernelCache& ); /* assign */
        ~KernelCache ( void );

        /* functions */
        double GetOrCompute ( int );
        double GetOrCompute ( int, int );

        /* variables */
        int size;
        int capacity;
        int collectionCapacity;
        std::unordered_map<int,double> data;

        std::list<int> lruIndices;
        std::unordered_map<int,std::list<int>::iterator> lruIndicesLookupTable;

        Vec* Diagonal;
        std::vector< Vec* > Inputs;
        Kernel kernel;

        int misses;
        int hits;

        Vec * Matrix;


    private:
};
}
}
#endif
