/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxCustBase:

REVISION HISTORY

05 June 2014 V1.00 REV 00 written by Ysbrand.Bouma
*/

#include "pxcstbas.hpp"
//#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxparameter.hpp"
#include "tourmanager.hpp"
#include "types/origintypeenum.inc"
#include <sstream>

/*----------------------------------------------------------------------------*/
const basar::VarString pxCustBase::getFaxNrCountry()
{
    basar::VarString retval(FaxNr()());
    retval.trim(basar::VarString::FIRST_END);
    if (0 == retval.length())
    {
        return retval;
    }

    pxParameter param(Session(), 0, "KSC", "Phone", "CountryPhoneCode");
    int rc = param.Get();
    if (rc != cDBXR_NORMAL)
    {
        return retval;
    }
    else
    {
        std::stringstream ss;
        ss << "00" << param.Wert() << retval.substr(1, retval.length() - 1);
        retval = ss.str().c_str();
        return retval;
    }
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
TourManager* pxCustBase::getTourManager()
{
    if( NULL == this->m_TourManager )
    {
        m_TourManager = new TourManager( Session(), 0, this->Vertriebszentrum(), this->IDFNr(), NULL );
    }
    return m_TourManager;
}

/*----------------------------------------------------------------------------*/
/*  getCustomersNextTourId: to get the next TourId, an info order will be     */
/*  opened to get information from the pxOrder::RoutAssign methode.           */
/*  TourId and DatumAuslieferung are transferred to callers variables         */
/*----------------------------------------------------------------------------*/
int pxCustBase::getCustomersNextTourId(nString& TourId, nDate& DatumAuslieferung)
{
    int retval = 0;

    TourInfo ti = this->getTourManager()->determineTour();
    if( ti.getTourFound() )
    {
        TourId = ti.getTourID();
        DatumAuslieferung = ti.getCustomerDeliveryDateTimeMin();
    }
    return retval;
}
