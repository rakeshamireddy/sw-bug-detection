/*******************************************************************************
 * Filename      : Instance.cpp
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
#include "Instance.hpp"

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
Instance::Instance ( void ) : data(NULL)
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
Instance::Instance ( const Instance& obj )
{
    label = obj.label;

    if ( obj.data != NULL )
    {
        Vec& s = *obj.data;
        data = new Vec(s);
    }
}
/*******************************************************************************
* Deconstructor:
* Description  :
* Arguments    :
* Remarks      :
********************************************************************************/
Instance::~Instance ( void )
{
    if ( data != NULL )
    {
        delete data;
    }
}
/*******************************************************************************
* Constructor  : (Assignment)
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
Instance& Instance::operator=( const Instance& obj )
{
    if ( this != &obj ) // prevent selfassignment
    {
        label = obj.label;
        if ( obj.data != NULL )
        {
            Vec& s = *obj.data;

            if ( data != NULL )
            {
                delete data;
            }
            data = new Vec(s);
        }
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

