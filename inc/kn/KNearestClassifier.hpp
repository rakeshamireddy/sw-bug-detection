/******************************************************************************
* Filename      : KNearestClassifier.hpp
* Source File(s): Classifier.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef KNEARESTCLASSIFIER_H
#define KNEARESTCLASSIFIER_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "KDTree.hpp"
#include <string>
#include <vector>
#include <Vec.hpp>

namespace algorithms
{
namespace knearest
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
class Classifier
{
    public:
        /* constructors */
        Classifier ( void ); /* default */
        Classifier ( int );
        Classifier ( int,int );
        Classifier ( const Classifier& ); /* copy */
        Classifier& operator= ( const Classifier& ); /* assign */
        ~Classifier ( void );

        /* functions */
        //void add_example  ( const std::vector<double>&, int );
        void add_example  ( Vec*, int );

        //int compute_label ( const std::vector<double>& );
        int classify ( Vec* );

        int brutefoce_classify ( const std::vector< Vec* >&, const std::vector<int>&, Vec* );

        /* variables */
        KDTree tree;
        int k;

    private:
        /* variables */

        /* functions */
};
}
}
#endif
