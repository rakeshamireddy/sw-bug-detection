/******************************************************************************
* Filename      : Domain.hpp
* Source File(s): Domain.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef DOMAIN_H
#define DOMAIN_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
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
class Domain
{
    public:
        /* constructors */
        Domain ( void ); /* default */
        Domain ( float, float, int );
        Domain ( const Domain& ); /* copy */
        Domain& operator= ( const Domain& ); /* assign */
        ~Domain ( void );

        /* functions */
        int discretize ( float );

        /* variables */
        float min_value;
        float max_value;
        int   value_count;

    private:

};
}
}
#endif
