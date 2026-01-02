
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlanDayHist.cpp
   Author: A.Schmidt-Rehschuh
   made  : 05.04.2000

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlanDayHist.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerCallPlanDayHist::ppCustomerCallPlanDayHist(const ppCustomerCallPlanDay* pCallPlanDay)
          : ppError(pCallPlanDay->GetPath(), pCallPlanDay->GetLanguage())
{
    m_srvCustomer = GetSrv();
    m_srvCustomerUP = GetSrvUP();
    m_pCallPlanDay = pCallPlanDay;
    SetVertriebsZentrumNr(m_pCallPlanDay->GetVertriebsZentrumNr());
    SetKundenNr(m_pCallPlanDay->GetKundenNr());
    SetDatum(m_pCallPlanDay->GetDatum());
    SetUrRufzeit(((ppCustomerCallPlanDay*)m_pCallPlanDay)->GetUrRufzeit());
}

//--- deconstructor ----------------------------------------------------------//

ppCustomerCallPlanDayHist::~ppCustomerCallPlanDayHist()
{
    if (m_srvCustomer)
        delete m_srvCustomer;
    if (GetSrvUP())
        delete m_srvCustomerUP;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCustomerCallPlanDayHist::StartBrowse()
{
    SetVertriebsZentrumNr(m_pCallPlanDay->GetVertriebsZentrumNr());
    SetKundenNr(m_pCallPlanDay->GetKundenNr());
    SetDatum(m_pCallPlanDay->GetDatum());
    SetUrRufzeit(((ppCustomerCallPlanDay*)m_pCallPlanDay)->GetUrRufzeit());
    return ppDadeScroll<CMCUSTOMERCALLPLANDAYHIST>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCustomerCallPlanDayHist::SetNextPage()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANDAYHIST>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCustomerCallPlanDayHist::SetPreviousPage()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANDAYHIST>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCustomerCallPlanDayHist::GetNext()
{
    SetErrorState(ppError::is_ok);

    bool bReturn = ppDadeScroll<CMCUSTOMERCALLPLANDAYHIST>::GetNext();

    if (!bReturn)
    {
        SetErrorState(ppError::is_notfound);
    }

    return bReturn;
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCustomerCallPlanDayHist::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCUSTOMERCALLPLANDAYHIST>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

//--- IsInitialized ----------------------------------------------------------//

bool ppCustomerCallPlanDayHist::IsInitialized()
{
    if (GetVertriebsZentrumNr() == 0 || GetKundenNr() == 0 || GetUrRufzeit() == 0 || GetDatum() == 0)
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
   }
   return true;
}
