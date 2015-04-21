/*******************************************************************************
 * Filename      : Fold.cpp
 * Header File(s):
 * Description   :
 * Authors(s)    :
 * Date Created  :
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
/************************************
* Included Headers
************************************/
#include "Fold.hpp"

/************************************
* Namespaces
************************************/
using namespace std;

/************************************
* Local Variables
************************************/

/*******************************************************************************
* Constructor  : (Default)
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
Fold::Fold ( void )
{
    ;
}
/*******************************************************************************
* Constructor  : (Copy)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Fold::Fold ( const Fold& obj )
{
    num                 = obj.num;
    data_training_set   = obj.data_training_set;
    data_testing_set    = obj.data_testing_set;
}
/*******************************************************************************
* Deconstructor:
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
Fold::~Fold ( void )
{
    ;
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Fold& Fold::operator=( const Fold& obj )
{
    if ( this != &obj ) // prevent selfassignment
    {
        num                 = obj.num;
        data_training_set   = obj.data_training_set;
        data_testing_set    = obj.data_testing_set;
    }
    return *this;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/

