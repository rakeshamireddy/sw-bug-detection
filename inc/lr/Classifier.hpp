/******************************************************************************
* Filename      : Classifier.hpp
* Source File(s): Classifier.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef CLASSIFIER_H
#define CLASSIFIER_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <Vec.hpp>
#include <vector>

#include "Logistic.hpp"
#include "SingularValueDecomposition.hpp"

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
class Classifier
{
    public:
        /* constructors */
        Classifier ( void ); /* default */
        Classifier ( int, int ); /* default */
        Classifier ( int, int, int ); /* default */
        Classifier ( const Classifier& ); /* copy */
        Classifier& operator= ( const Classifier& ); /* assign */
        ~Classifier ( void );

        /* functions */
        Vec* mapfeatures ( Vec* );

        void run ( const std::vector< Vec* >& , const std::vector<int>&,
                   const std::vector< Vec* >& , const std::vector<int>& );
        void run_supervised ( const std::vector< Vec* >& , const std::vector<int>&,
                              const std::vector< Vec* >& , const std::vector<int>& );
        double learn_semisupervised ( const std::vector< Vec* >& , const std::vector<int>&,
                                      const std::vector< Vec* >& , const std::vector<int>& );
        double learn_supervised ( const std::vector< Vec* >& , const std::vector<int>&,
                                  const std::vector< Vec* >& , const std::vector<int>& );

        double f ( int, int );
        double g ( int, int );

        /* variables */
        int degree;
        double lambda;

        std::vector<Vec*> dataset;
        Vec* Z = NULL;
        double regulizer;

        Logistic model;
        Vec* Gradient = NULL;
        Vec* Previous = NULL;
        Vec* Solution = NULL;
        Vec* Deltas = NULL;
        Vec* Errors = NULL;
        Vec* Weights = NULL;
        Vec* LowerBound = NULL;
        Vec* XXT = NULL;



        int mappingdegree;
        int K;
        int M;
        int parameterCount;
        bool updateLowerBound;
        bool computeStandardErrors;
        SingularValueDecomposition decomposition;

        int iteration;
        int max_iterations;
        double min_delta;


    private:
};
}
}
#endif
