/******************************************************************************
* Filename      : SingularValueDecomposition.hpp
* Source File(s): SingularValueDecomposition.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef SINGULARVALUEDECOMPOSITION_H
#define SINGULARVALUEDECOMPOSITION_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <Vec.hpp>
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
class SingularValueDecomposition
{
    public:
        /* constructors */
        SingularValueDecomposition ( void ); /* default */
        SingularValueDecomposition ( Vec*, bool, bool, bool );
        SingularValueDecomposition ( const SingularValueDecomposition& ); /* copy */
        SingularValueDecomposition& operator= ( const SingularValueDecomposition& ); /* assign */
        ~SingularValueDecomposition ( void );
        /* functions */
        Vec* solve ( Vec* );
        Vec* inverse ( void );

        /* variables */
        bool computeLeftSingularVectors;
        bool computeRightSingularVectors;
        bool autoTranspose;
        bool swapped;
        bool aux;

        int n;
        int m;

        Vec* S = NULL;
        Vec* U = NULL;
        Vec* V = NULL;

        Vec* SI = NULL;

    private:
        double hypotenuse ( double, double );
        double threshold ( void );
};
}
}
#endif
