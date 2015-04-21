/******************************************************************************
* Filename      : DBScan.hpp
* Source File(s): DBScan.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef DBSCAN_H
#define DBSCAN_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <vector>
#include <Vec.hpp>

namespace algorithms
{
namespace clustering
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
class DBScan
{
    public:
        /* constructors */
        DBScan ( void ); /* default */
        DBScan ( double, int );
        DBScan ( const DBScan& ); /* copy */
        DBScan& operator= ( const DBScan& ); /* assign */
        ~DBScan ( void );
        /* functions */
        void set_weights ( const std::vector<double>& );
        void cluster ( const std::vector< std::vector<double> >& );
        void cluster ( const std::vector< std::vector<double> >&, double );
        void cluster ( const std::vector< std::vector<double> >&, const std::vector<double>& );
        void initialize_weights ( int, double );
        void initialize_weights ( const std::vector<double>& );
        void initialize_labels ( int, int );
        void initialize_dist_matrix ( const std::vector< std::vector<double> >& );

        /* variables */
        double init_weights;
        double eps;
        int min_elems;
        double dist_min;
        double dist_max;

    private:
        std::vector<unsigned int> find_neighbors ( unsigned int );
        void run ( const std::vector< std::vector<double> >& );

        Vec * feature_weights;
        Vec * data;
        Vec * distance_matrix;
        Vec * neighbors;
        Vec * labels;

};
}
}
#endif
