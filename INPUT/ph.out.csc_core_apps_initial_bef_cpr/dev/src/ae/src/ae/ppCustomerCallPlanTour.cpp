
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlanTour.cpp
   Author: A.Schmidt-Rehschuh
   made  : 05.04.2000

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlanTour.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerCallPlanTour::ppCustomerCallPlanTour(const ppCustomerDisplay* pCustomer,
                                               const ppString& strPath,
                                               const short sLanguage)
            : ppError(strPath, sLanguage)
{
    m_srvTour = GetSrv();
    m_srvTourUP = GetSrvUP();
    m_pCustomer = pCustomer;
}


//--- deconstructor ----------------------------------------------------------//

ppCustomerCallPlanTour::~ppCustomerCallPlanTour()
{
    EndBrowse();
    if (m_srvTour)
        delete m_srvTour;
    if (GetSrvUP())
        delete m_srvTourUP;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCustomerCallPlanTour::StartBrowse()
{
    m_srvTour->SetVertriebszentrumnr(m_pCustomer->GetVertriebsZentrumNr());
    m_srvTour->SetKundennr(m_pCustomer->GetKundenNr());
    m_srvTour->SetFilialnr(m_pCustomer->GetFilialNr());

    return ppDadeScroll<CMCUSTOMERCALLPLANTOUR>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCustomerCallPlanTour::SetNextPage()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANTOUR>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCustomerCallPlanTour::SetPreviousPage()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANTOUR>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCustomerCallPlanTour::GetNext()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANTOUR>::GetNext();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCustomerCallPlanTour::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCUSTOMERCALLPLANTOUR>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCustomerCallPlanTour::IsInitialized()
{
   if (GetVertriebsZentrumNr() == 0  || GetFilialNr() == 0)
   {
        SetErrorState(ppError::is_not_initialized);
        return false;
   }
   return true;
}

//----------------------------------------------------------------------------//
//--- checking data ----------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- IsChanged --------------------------------------------------------------//

bool ppCustomerCallPlanTour::IsChanged()
{
    return !(m_srvTour->GetStruct() == m_srvTourUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCustomerCallPlanTour::Restore()
{
    if (IsChanged())
        m_srvTour->SetStruct(m_srvTourUP->GetStruct());
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

const char* ppCustomerCallPlanTour::GetCurrentTourID(const ppTime& TimeCurrent, const short sMinutes )
{
    m_str = "";
    if (GetSrv()->beginList() == GetSrv()->endList())
        return m_str.c_str();

    vector<mcustomercallplantourS>::iterator itBegin = GetSrv()->beginList();
    ppTime TimeMax = TimeCurrent;
    TimeMax.Add(sMinutes);
    ppTime TimeTour;
    for (; itBegin != GetSrv()->endList(); itBegin++)
    {
        if (atol(ppString(itBegin->TOURID).substr(0, 4).c_str()) > 2359)
        {
            TimeTour.SetTime("2359");
        }
        else
        {
            TimeTour.SetTime(ppString(itBegin->TOURID).substr(0,4).c_str());
        }
        if (TimeTour > TimeMax)
        {
          m_str = itBegin->TOURID;
          break;
       }
    }

    if (m_str.empty())
    {
        m_str = (GetSrv()->endList() - 1)->TOURID;
    }

    return m_str.c_str();
}
