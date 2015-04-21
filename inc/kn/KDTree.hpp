/******************************************************************************
* Filename      : KDTree.hpp
* Source File(s): KDTree.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef KDTREE_H
#define KDTREE_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include "KDNode.hpp"
#include <cstdlib>
#include <vector>

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
class KDTree
{
    public:
        /* constructors */
        KDTree ( void );
        KDTree ( int );
        ~KDTree ( void );
        KDTree ( const KDTree& ); /* copy */
        /* variables */
        bool add ( Vec*, int );
        std::vector<KDNode*> find_k_nearest ( Vec*, int );


    private:
        /* functions */
         bool is_nearest ( KDNode* );
        KDNode* find_nearest( Vec* );
        void deallocate ( KDNode* );
        void check_subtree ( KDNode*, Vec* );
        void set_bounding_cube ( KDNode*, Vec* );
        KDNode* search_parent ( KDNode*, Vec* );
        bool compare_vec ( Vec*, Vec* );

        /* variables */
        KDNode * Root;
        double d_min;
        KDNode * nearest_neighbour;

        unsigned long KD_id;

        std::vector< KDNode* > neighbors;

        Vec * x_min;
        Vec * x_max;
        Vec * max_boundary;
        Vec * min_boundary;

        int n_boundary;
        int dim;

};
}
}
#endif
