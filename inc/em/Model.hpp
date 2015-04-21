/******************************************************************************
* Filename      : Model.hpp
* Source File(s): Model.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef MODEL_H
#define MODEL_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "Gaussian.hpp"
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
class Model
{
    public:
        /* constructors */
        Model ( void ); /* default */
        Model ( const Model& ); /* copy */
        Model& operator= ( const Model& ); /* assign */
        ~Model ( void );

        /* functions */
        double  run ( const std::vector< Vec* >&,
                      const std::vector<int>&,
                      const std::vector< Vec* >&,
                      const std::vector<int>& );

        void  gaussian_test ( const std::vector< Vec* >&,
                              const std::vector<int>&,
                              const std::vector< Vec* >&,
                              const std::vector<int>& );

        void train ( const std::vector< Vec*>&,
                     const std::vector<int>& );
        int predict ( Vec* );

        void test ( void );
        void test1d ( void );

        /* variables */
        unsigned int max_iterations;
        double max_probability;
        std::vector<Gaussian> gaussians;
        unsigned int k;
        bool trained;
        bool shuffle;

    private:
};
}
}
#endif
