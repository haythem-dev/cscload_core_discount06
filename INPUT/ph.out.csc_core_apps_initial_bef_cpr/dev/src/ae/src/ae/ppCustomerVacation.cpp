
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerVacation.cpp
   Author: R.Imschweiler
   made  : 09.05.2001

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include <customer.h>
#include "ppCustomerVacation.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerVacation::ppCustomerVacation(const ppString& strPath, const short sLanguage)
            : ppError(strPath, sLanguage)
{
    m_srvVacation = GetSrv();
    m_srvVacationUP = GetSrvUP();
}

ppCustomerVacation::ppCustomerVacation(const short sBranch,
                                         const ppString& strPath,
                                         const short sLanguage)
            : ppError(strPath, sLanguage)
{
    m_srvVacation = GetSrv();
    m_srvVacationUP = GetSrvUP();
    SetVertriebsZentrumNr(sBranch);
}

//--- deconstructor ----------------------------------------------------------//

ppCustomerVacation::~ppCustomerVacation()
{
    EndBrowse();
    if (m_srvVacation)
        delete m_srvVacation;
    if (GetSrvUP())
        delete m_srvVacationUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- UpdateCustomer (update selected row) -----------------------------------//

bool ppCustomerVacation::Update()
{
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvVacation->GetStruct() == m_srvVacationUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvVacation->Update() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvVacationUP->SetStruct(m_srvVacation->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCustomerVacation::Insert()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc = m_srvVacation->Insert();
    if (rc != IS_OK)
    {
        m_srvVacation->ClearStruct();
        m_srvVacationUP->ClearStruct();
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

    m_srvVacationUP->SetStruct(m_srvVacation->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCustomerVacation::Delete()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvVacation->Delete() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvVacation->ClearStruct();
    m_srvVacationUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}


//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCustomerVacation::StartBrowse()
{
    return ppDadeScroll<CMCUSTOMERVACATION>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCustomerVacation::SetNextPage()
{
    return ppDadeScroll<CMCUSTOMERVACATION>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCustomerVacation::SetPreviousPage()
{
    return ppDadeScroll<CMCUSTOMERVACATION>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCustomerVacation::GetNext()
{
    return ppDadeScroll<CMCUSTOMERVACATION>::GetNext();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCustomerVacation::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCUSTOMERVACATION>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCustomerVacation::IsInitialized()
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

bool ppCustomerVacation::IsChanged()
{
    return !(m_srvVacation->GetStruct() == m_srvVacationUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCustomerVacation::Restore()
{
    if (IsChanged())
        m_srvVacation->SetStruct(m_srvVacationUP->GetStruct());
}
