/******************************************************************************
* Filename      : NaiveBayesClassifier.hpp
* Source File(s): Classifier.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <string>
#include <vector>
#include <map>
#include "Domain.hpp"
#include <Vec.hpp>

namespace algorithms
{
namespace naivebayes
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
        Classifier ( const std::vector<Domain>&, Domain );
        Classifier ( const Classifier& ); /* copy */
        Classifier& operator= ( const Classifier& ); /* assign */
        ~Classifier ( void );

        /* functions */
        int  classify    ( Vec* );
        void add_example ( Vec*, int );
        void print_prior ( void );

        /* variables */

    private:
        /* variables */
        std::vector<Domain>              inputdomains;
        Domain                           outputdomain;
        int                              totalexamples;
        std::map<unsigned long, double>  posteriors;
        std::vector<double>              priors;

         /* functions */
        unsigned long     calc_mapkey       ( int, int, int );
        void              update_prior      ( int );
        void              update_posterior ( Vec*, int );
};
}
}
#endif
