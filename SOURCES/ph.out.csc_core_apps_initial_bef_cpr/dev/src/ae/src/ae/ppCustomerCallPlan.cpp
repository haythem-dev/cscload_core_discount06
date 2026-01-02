
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlan.cpp
   Author: A.Schmidt-Rehschuh
   made  : 05.04.2000

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlan.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerCallPlan::ppCustomerCallPlan(const ppCustomerDisplay* pCustomer,
                                       const ppDayType& Day)
            : ppError(pCustomer->GetPath(), pCustomer->GetLanguage())
{
    m_srvCustomer = GetSrv();
    m_srvCustomerUP = GetSrvUP();
    m_srvCustomer->SetTagnr(Day.c_char());
    m_pCustomer = pCustomer;
    m_bIsTimeChange = false;
    m_bAllCallsAreDisabled = false;

    const char* paDataTransfer[] = {"DP","DS","PH","DA"};
    for ( int i = 0; i < sizeof(paDataTransfer)/4; i++)
    {
        strcpy(m_szaCallRecord[i], paDataTransfer[i]);
    }

    const char* paDataType[] = {"Normal","Sonderruf","kein Ruf b.S.", "gesperrt" }; //TO_DO
/*      CResString::ex().getStrTblText(AETEXT_NORMAL),
        CResString::ex().getStrTblText(AETXT_SONDERRUF),
        CResString::ex().getStrTblText(AETXT_KEIN_RUF),
        CResString::ex().getStrTblText(AETXT_GESPERRT)
        };  */
    for ( int i = 0; i < sizeof(paDataType)/4; i++)
    {
        strcpy(m_szaCallType[i], paDataType[i]);
    }
}

//--- deconstructor ----------------------------------------------------------//

ppCustomerCallPlan::~ppCustomerCallPlan()
{
    EndBrowse();
    if (m_srvCustomer)
        delete m_srvCustomer;
    if (GetSrvUP())
        delete m_srvCustomerUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- UpdateCustomer (update selected row) -----------------------------------//

bool ppCustomerCallPlan::Update()
{
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    int rc;
    if (m_bIsTimeChange)
    {
        m_bIsTimeChange = false;
        rc = m_srvCustomer->UpdTimeCustomerCallPlan();
    }
    else
        rc = m_srvCustomer->UpdCustomerCallPlan();

    if (rc != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCustomerCallPlan::Insert()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc = m_srvCustomer->Insert();
    if (rc != IS_OK)
    {
        m_srvCustomer->ClearStruct();
        m_srvCustomerUP->ClearStruct();
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

    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    m_bAllCallsAreDisabled = false;
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCustomerCallPlan::Delete()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvCustomer->DelCustomerCallPlan() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCustomerCallPlan::DeleteGeneral()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvCustomer->DelAllCustomerCallPlan() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCustomerCallPlan::InsertGeneral()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc = m_srvCustomer->InsertAll();
    if (rc != IS_OK)
    {
        m_srvCustomer->ClearStruct();
        m_srvCustomerUP->ClearStruct();
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

    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    m_bAllCallsAreDisabled = false;
    return true;
}

//--- UpdateGeneral (update selected row) ------------------------------------//

bool ppCustomerCallPlan::UpdateGeneral()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc;
    if (m_bIsTimeChange)
    {
        m_bIsTimeChange = false;
        rc = m_srvCustomer->UpdTimeAllCustomerCallPlan();
    }
    else
        rc = m_srvCustomer->UpdAllCustomerCallPlan();

    if (rc)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- EnableCompletly (update all selected rows) -----------------------------//

bool ppCustomerCallPlan::EnableCompletly(const bool bEnable)
{
    m_srvCustomer->SetVertriebszentrumnr(m_pCustomer->GetVertriebsZentrumNr());
    m_srvCustomer->SetKundennr(m_pCustomer->GetKundenNr());
    SetCallDisabledAll();

    if (!IsInitialized())
        return false;
    int rc = bEnable ? m_srvCustomer->UpdCallPlanEnable() : m_srvCustomer->UpdCallPlanDisable();
    if (rc != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_bAllCallsAreDisabled = !bEnable;
    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- CheckAllDisabled (look after there are all calls disabled) -------------//

bool ppCustomerCallPlan::CheckAllDisabled()
{
    m_srvCustomer->SetVertriebszentrumnr(m_pCustomer->GetVertriebsZentrumNr());
    m_srvCustomer->SetKundennr(m_pCustomer->GetKundenNr());
    SetCallDisabledAll();
    if (!IsInitialized())
        return false;
    else if (m_srvCustomer->SelAllDisabled() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_bAllCallsAreDisabled = m_srvCustomer->GetLoginid() == 0 ? true : false;
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCustomerCallPlan::DeleteGeneralWithoutSaturday()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvCustomer->DelAllWithoutSaturday() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    SetErrorState(ppError::is_ok);
    return true;
}

//--- DestroyCompletly (delete selected row) ---------------------------------//

bool ppCustomerCallPlan::DestroyCompletly()
{
    m_srvCustomer->SetVertriebszentrumnr(m_pCustomer->GetVertriebsZentrumNr());
    m_srvCustomer->SetKundennr(m_pCustomer->GetKundenNr());
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvCustomer->DelCallPlanCompletly() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_srvCustomer->ClearStruct();
    m_srvCustomerUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCustomerCallPlan::InsertGeneralWithoutSaturday()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc;
    if ((rc = m_srvCustomer->InsertAllWithoutSaturday()) != IS_OK)
    {
        m_srvCustomer->ClearStruct();
        m_srvCustomerUP->ClearStruct();
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

    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    m_bAllCallsAreDisabled = false;
    return true;
}

//--- UpdateGeneral (update selected row) ------------------------------------//

bool ppCustomerCallPlan::UpdateGeneralWithoutSaturday()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc;
    if (m_bIsTimeChange)
    {
        m_bIsTimeChange = false;
        rc = m_srvCustomer->UpdTimeAllWithoutSaturday();
    }
    else
        rc = m_srvCustomer->UpdAllWithoutSaturday();

    if (rc)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCustomerCallPlan::StartBrowse()
{
    m_srvCustomer->SetVertriebszentrumnr(m_pCustomer->GetVertriebsZentrumNr());
    m_srvCustomer->SetKundennr(m_pCustomer->GetKundenNr());
    return ppDadeScroll<CMCUSTOMERCALLPLAN>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCustomerCallPlan::SetNextPage(const t_type eTyp)
{
    if (eTyp == c_normal)
        return ppDadeScroll<CMCUSTOMERCALLPLAN>::SetNextPage();
    else if (eTyp == c_print)
        return ppDadeScroll<CMCUSTOMERCALLPLAN>::SetNextPage(ppDadeScroll<CMCUSTOMERCALLPLAN>::list_history);
    else
        return false;
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCustomerCallPlan::SetPreviousPage()
{
    return ppDadeScroll<CMCUSTOMERCALLPLAN>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCustomerCallPlan::GetNext(const t_type eTyp)
{
    bool bReturn;
    if (eTyp == c_normal)
        bReturn = ppDadeScroll<CMCUSTOMERCALLPLAN>::GetNext();
    else if (eTyp == c_print)
        bReturn = ppDadeScroll<CMCUSTOMERCALLPLAN>::GetNext(true, ppDadeScroll<CMCUSTOMERCALLPLAN>::list_history);
    else
        return false;

    return bReturn;
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCustomerCallPlan::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCUSTOMERCALLPLAN>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCustomerCallPlan::IsInitialized()
{
    if (GetVertriebsZentrumNr() == 0 || GetKundenNr() == 0)
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

bool ppCustomerCallPlan::IsChanged()
{
    return !(m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCustomerCallPlan::Restore()
{
    if (IsChanged())
        m_srvCustomer->SetStruct(m_srvCustomerUP->GetStruct());
}
