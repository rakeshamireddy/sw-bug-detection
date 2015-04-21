/******************************************************************************
* Filename      : KDNode.hpp
* Source File(s): KDNode.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef KDNODE_H
#define KDNODE_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
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
class KDNode
{
    public:
        /* constructors */
        KDNode ( void );
        KDNode ( Vec*, int );
        KDNode ( const KDNode& ); /* copy */
        KDNode ( KDNode* ); /* copy */
        ~KDNode ( void );
        KDNode& operator= ( const KDNode& ); /* assign */
        KDNode* operator= ( KDNode* ); /* assign */
        bool operator==( const KDNode & );
        double operator[] ( size_t );

        /* functions */
        KDNode * Insert  ( Vec* );
        KDNode * FindParent ( Vec* );
        bool compare_vec ( Vec* );
        double distance2 ( Vec* );

        KDNode * Parent ;
        KDNode * Left ;
        KDNode * Right ;

        /* variables */
        int axis;
        Vec* x;
        unsigned long id;
        bool orientation;
        int  label;


    private:
        /* functions */

        /* variables */

};
}
}
#endif
