//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlanDay.cpp
   Author: A.Schmidt-Rehschuh
   made  : 05.04.2000

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlanDay.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerCallPlanDay::ppCustomerCallPlanDay(const short sBranchNo,
                                             const ppString& strPath,
                                             const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_sBranchNo = sBranchNo;
    m_srvCustomer = GetSrv();
    m_srvCustomerUP = GetSrvUP();
    m_Callstate = s_set;
    m_lUID = -1;
    m_lCallTime = -1;
    m_bIsInitialized = false;
    m_bEndSession = true;
    if (m_srvCustomer->StartBrowse() != 0) //initilaized database querys
        SetErrorState(ppError::is_sqlerror);
    else
       m_bIsInitialized = true;
}

//--- copy constructor -------------------------------------------------------//

ppCustomerCallPlanDay::ppCustomerCallPlanDay(const ppCustomerCallPlanDay& right)
    : ppError(right.GetPath(), right.GetLanguage())
{
    m_srvCustomer = GetSrv();
    m_srvCustomerUP = GetSrvUP();
    m_Callstate = s_set;
    m_lUID = -1;
    m_lCallTime = -1;
    m_bEndSession = true;
    m_sBranchNo = right.m_sBranchNo;

    if (!right.m_bIsInitialized)
    {
        if (m_srvCustomer->StartBrowse() != IS_OK) //initilaized database querys
        {
            m_bIsInitialized = false;
            SetErrorState(ppError::is_sqlerror);
        }
        else
        {
            m_bIsInitialized = true;
        }
    }
    else
    {
        m_bEndSession = false;
    }
}

//--- deconstructor ----------------------------------------------------------//

ppCustomerCallPlanDay::~ppCustomerCallPlanDay()
{
    if (m_bEndSession)
        m_srvCustomer->EndBrowse(); //get memory free from database querys

    EndBrowse();
    if (m_srvCustomer)
        delete m_srvCustomer;
    if (GetSrvUP())
        delete m_srvCustomerUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetUni (unique select) -------------------------------------------------//

bool ppCustomerCallPlanDay::GetUni()
{
    SetErrorState(ppError::is_ok);
    if (!IsInitialized())
        return false;

    m_srvCustomer->SelCallPlanDay();
    if (m_srvCustomer->rc == IS_OK)
    {
        m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
        return true;
    }
    else if (m_srvCustomer->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return false;
}

//--- UpdateCustomer (update selected row) -----------------------------------//

bool ppCustomerCallPlanDay::Update(const bool bPostbone)
{
    if (!IsInitialized(true) && GetEvent() == ce_set)
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    CMCUSTOMERCALLPLANDAY srvCheck;
    if (!CheckCurrentCall(&srvCheck, bPostbone))
    {
        SetErrorState(ppError::is_changed);
        m_srvCustomer->SetStruct(srvCheck.GetStruct());
        m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
        return false;
    }

    SetHistoryData();
    if (m_srvCustomer->UpdCustomerCallPlanDay() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (SetList() == IS_OK)
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

   UnSetHistoryData();
   m_srvCustomer->SetIdfnr(m_lIdfNr);
   m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
   SetErrorState(ppError::is_ok);
   m_lCallTime = -1;
   return true;
}

//--- UpdateDirect (update selected row) -------------------------------------//

bool ppCustomerCallPlanDay::UpdateDirect()
{
    if (!IsInitialized(true))
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    SetHistoryData();
    if (m_srvCustomer->UpdCustomerCallPlanDay() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (SetList() == IS_OK)
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    UnSetHistoryData();
    m_srvCustomer->SetIdfnr(m_lIdfNr);
    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    m_lCallTime = -1;
    return true;
}

//--- UpdateDirect (update selected row) -------------------------------------//

bool ppCustomerCallPlanDay::SetCallToFree()
{
    if (!IsInitialized(true))
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    SetHistoryData();
    if (m_srvCustomer->SetCustomerCallFree() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (SetList() == IS_OK)
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    UnSetHistoryData();
    m_srvCustomer->SetIdfnr(m_lIdfNr);
    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    m_lCallTime = -1;
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCustomerCallPlanDay::Insert()
{
    if (!IsInitialized(true))
    {
        return false;
    }

    int rc;
    SetHistoryData();
    if ((rc = m_srvCustomer->Insert()) != IS_OK)
    {
        bool bClear = false;
        switch (rc)
        {
        case IS_NOTFOUND:
            SetErrorState(ppError::is_notfound); bClear = true;
            break;
        case IS_LOCKED:
            SetErrorState(ppError::is_locked); bClear = true;
            break;
        case IS_EXISTS:
            SetErrorState(ppError::is_exist);
            break;
        default:
            SetErrorState(ppError::is_sqlerror);
            break;
        }
        if (bClear)
        {
            m_srvCustomer->ClearStruct();
            m_srvCustomerUP->ClearStruct();
        }

        return false;
    }
    else if (!InsList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    UnSetHistoryData();
    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    m_lCallTime = -1;
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCustomerCallPlanDay::Delete()
{
   return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCustomerCallPlanDay::StartBrowse()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCustomerCallPlanDay::SetNextPage(const t_calltyp eTyp)
{
    if (eTyp == c_normal)
        return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::SetNextPage();
    else if (eTyp == c_ready)
        return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::SetNextPage(ppDadeScroll<CMCUSTOMERCALLPLANDAY>::list_history);
    else if (eTyp == c_rejected)
        return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::SetNextPage(ppDadeScroll<CMCUSTOMERCALLPLANDAY>::list_future);
    else
       return false;
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCustomerCallPlanDay::SetPreviousPage()
{
    return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCustomerCallPlanDay::GetNext(const t_calltyp eTyp)
{
    m_lUID = -1;
    if (eTyp == c_normal)
        return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::GetNext();
    else if (eTyp == c_ready)
        return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::GetNext(true, ppDadeScroll<CMCUSTOMERCALLPLANDAY>::list_history);
    else if (eTyp == c_rejected)
        return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::GetNext(true,ppDadeScroll<CMCUSTOMERCALLPLANDAY>::list_future);
    else
       return false;
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCustomerCallPlanDay::SetElement(const unsigned nPos)
{
    m_lUID = -1;
    return ppDadeScroll<CMCUSTOMERCALLPLANDAY>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

//--- IsInitialized ----------------------------------------------------------//

bool ppCustomerCallPlanDay::IsInitialized(const bool bIsUpdate)
{
    if (!bIsUpdate && (GetVertriebsZentrumNr() == 0 || GetKundenNr() == 0))
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
    }
    else if (bIsUpdate && (GetVertriebsZentrumNr() == 0 || GetKundenNr() == 0 || m_lUID == -1))
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
    }
    return true;
}

//--- SetHistoryData ---------------------------------------------------------//

void ppCustomerCallPlanDay::SetHistoryData()
{
    m_srvCustomer->SetPoolnr(m_sBranchNo /* FilialNr des Modems */);
    m_srvCustomer->SetModempoolnr(0 /*Modem auf dem gewählt wurde*/);
    m_lIdfNr = GetIdfNr();
    m_srvCustomer->SetIdfnr((long)GetEvent());
}

//--- UnSetHistoryData ---------------------------------------------------------//

void ppCustomerCallPlanDay::UnSetHistoryData()
{
    m_srvCustomer->SetPoolnr(0 /* FilialNr des Modems */);
    m_srvCustomer->SetModempoolnr(0 /*Modem auf dem gewählt wurde*/);
}

//----------------------------------------------------------------------------//
//--- checking data ----------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- IsChanged --------------------------------------------------------------//

bool ppCustomerCallPlanDay::CheckCurrentCall(CMCUSTOMERCALLPLANDAY* srvCheck, const bool bPostbone)
{
    srvCheck->SetStruct(m_srvCustomer->GetStruct());
    if (srvCheck->SelCallPlanDay() == IS_OK)
    {
        if (GetEvent() == ppCallPlanEvents::ce_order_reactivated &&
            srvCheck->GetAnrufstatus() != s_set &&
            srvCheck->GetAnrufstatus() != s_customer_isbusy &&
            srvCheck->GetAnrufstatus() != s_umk_isbusy &&
            srvCheck->GetAnrufstatus() != s_call_iscalled)
        {
            return true;
        }
        else
        {
            if (m_lCallTime == -1) //set call to ready
            {
                m_lCallTime = m_srvCustomer->GetRufzeit();
            }

            if (bPostbone)
            {
                return (srvCheck->GetAnrufstatus() == (short)m_Callstate &&
                        srvCheck->GetRufzeit() == m_lCallTime &&
                        srvCheck->GetUmkstatus() == m_srvCustomer->GetUmkstatus());
            }
            else
            {
                return (srvCheck->GetAnrufstatus() == (short)m_Callstate &&
                        srvCheck->GetAnrufzaehler() == m_srvCustomer->GetAnrufzaehler() &&
                        srvCheck->GetRufzeit() == m_lCallTime &&
                        srvCheck->GetUmkstatus() == m_srvCustomer->GetUmkstatus());
            }
        }
    }
    else if (srvCheck->rc == IS_NOTFOUND)
        SetErrorState(ppError::is_notfound);
    return false;
}

//--- IsChanged --------------------------------------------------------------//

bool ppCustomerCallPlanDay::IsChanged()
{
    return !(m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCustomerCallPlanDay::Restore()
{
    if (IsChanged())
        m_srvCustomer->SetStruct(m_srvCustomerUP->GetStruct());
}

//--- Clear ------------------------------------------------------------------//

void ppCustomerCallPlanDay::Clear()
{
    m_srvCustomer->ClearStruct();
}
