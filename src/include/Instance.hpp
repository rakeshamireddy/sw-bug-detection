/******************************************************************************
* Filename      : Instance.hpp
* Source File(s): Instance.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef INSTANCE_H
#define INSTANCE_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <Vec.hpp>

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
class Instance
{
    public:
        /* constructors */
        Instance ( void ); /* default */
        Instance ( const Instance& ); /* copy */
        Instance& operator= ( const Instance& ); /* assign */
        ~Instance ( void );

        /* functions */

        /* variables */
        Vec* data;
        int label;

    private:
        /* variables */

        /* functions */
};
#endif
