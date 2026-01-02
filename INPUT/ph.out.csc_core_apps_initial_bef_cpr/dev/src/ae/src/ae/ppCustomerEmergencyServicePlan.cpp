
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerEmergencyServicePlan.cpp
   Author: R.Imschweiler
   made  : 09.05.2001

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include <customer.h>
#include "ppCustomerEmergencyServicePlan.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerEmergencyServicePlan::ppCustomerEmergencyServicePlan(const ppString& strPath, const short sLanguage)
            : ppError(strPath, sLanguage)
{
    m_srvServicePlan = GetSrv();
    m_srvServicePlanUP = GetSrvUP();
}

ppCustomerEmergencyServicePlan::ppCustomerEmergencyServicePlan(const short sBranch,
                                         const ppString& strPath,
                                         const short sLanguage)
            : ppError(strPath, sLanguage)
{
    m_srvServicePlan = GetSrv();
    m_srvServicePlanUP = GetSrvUP();
    SetVertriebsZentrumNr(sBranch);
}

//--- deconstructor ----------------------------------------------------------//

ppCustomerEmergencyServicePlan::~ppCustomerEmergencyServicePlan()
{
    EndBrowse();
    if (m_srvServicePlan)
        delete m_srvServicePlan;
    if (GetSrvUP())
        delete m_srvServicePlanUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- UpdateCustomer (update selected row) -----------------------------------//

bool ppCustomerEmergencyServicePlan::Update()
{
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvServicePlan->GetStruct() == m_srvServicePlanUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvServicePlan->Update() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvServicePlanUP->SetStruct(m_srvServicePlan->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCustomerEmergencyServicePlan::Insert()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc = m_srvServicePlan->Insert();
    if (rc != IS_OK)
    {
        m_srvServicePlan->ClearStruct();
        m_srvServicePlanUP->ClearStruct();
        switch (rc)
        {
        case IS_NOTFOUND:
            SetErrorState(ppError::is_notfound);
            break;
        case IS_LOCKED:
            SetErrorState(ppError::is_locked);
            break;
        case IS_EXISTS:
            SetErrorState(ppError::is_exist);
            break;
        default:
            SetErrorState(ppError::is_sqlerror);
            break;
        }
        return false;
    }
    else if (!InsList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvServicePlanUP->SetStruct(m_srvServicePlan->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCustomerEmergencyServicePlan::Delete()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvServicePlan->Delete() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvServicePlan->ClearStruct();
    m_srvServicePlanUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}


//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCustomerEmergencyServicePlan::StartBrowse()
{
    return ppDadeScroll<CMCUSTOMEREMERGENCYSERVICEPLAN>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCustomerEmergencyServicePlan::SetNextPage()
{
    return ppDadeScroll<CMCUSTOMEREMERGENCYSERVICEPLAN>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCustomerEmergencyServicePlan::SetPreviousPage()
{
    return ppDadeScroll<CMCUSTOMEREMERGENCYSERVICEPLAN>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCustomerEmergencyServicePlan::GetNext()
{
    return ppDadeScroll<CMCUSTOMEREMERGENCYSERVICEPLAN>::GetNext();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCustomerEmergencyServicePlan::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCUSTOMEREMERGENCYSERVICEPLAN>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCustomerEmergencyServicePlan::IsInitialized()
{
    if (GetVertriebsZentrumNr() == 0)
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

bool ppCustomerEmergencyServicePlan::IsChanged()
{
    return !(m_srvServicePlan->GetStruct() == m_srvServicePlanUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCustomerEmergencyServicePlan::Restore()
{
    if (IsChanged())
        m_srvServicePlan->SetStruct(m_srvServicePlanUP->GetStruct());
}
