//(c)---------- Customer ClassModel ------------------------------------------//
/*
    Source: ppCallPlanParameter.cpp
    Author: A.Schmidt-Rehschuh
    made  : 05.04.2000

    declaration:
    logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanParameter.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCallPlanParameter::ppCallPlanParameter(const ppString& strPath, const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvParameter = GetSrv();
    m_srvParameterUP = GetSrvUP();
}

ppCallPlanParameter::ppCallPlanParameter(const short sBranch,
                                         const ppString& strPath,
                                         const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvParameter = GetSrv();
    m_srvParameterUP = GetSrvUP();
    SetVertriebsZentrumNr(sBranch);
    GetUni();
}

//--- deconstructor ----------------------------------------------------------//

ppCallPlanParameter::~ppCallPlanParameter()
{
    EndBrowse();
    if (m_srvParameter)
        delete m_srvParameter;
    if (GetSrvUP())
        delete m_srvParameterUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetUni (unique select) -------------------------------------------------//

bool ppCallPlanParameter::GetUni()
{
    SetErrorState(ppError::is_ok);
    if (!IsInitialized())
        return false;

    m_srvParameter->SelCallParameter();
    if (m_srvParameter->rc == IS_OK)
    {
        m_srvParameterUP->SetStruct(m_srvParameter->GetStruct());
        return true;
    }
    else if (m_srvParameter->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return false;
}

//--- UpdateCustomer (update selected row) -----------------------------------//

bool ppCallPlanParameter::Update()
{
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvParameter->GetStruct() == m_srvParameterUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvParameter->UpdCallparameter() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvParameterUP->SetStruct(m_srvParameter->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCallPlanParameter::Insert()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc = m_srvParameter->Insert();
    if (rc != IS_OK)
    {
        m_srvParameter->ClearStruct();
        m_srvParameterUP->ClearStruct();
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

    m_srvParameterUP->SetStruct(m_srvParameter->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCallPlanParameter::Delete()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvParameter->DelCallParameter() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvParameter->ClearStruct();
    m_srvParameterUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCallPlanParameter::StartBrowse()
{
    return ppDadeScroll<CMCALLPARAMATER>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCallPlanParameter::SetNextPage()
{
    return ppDadeScroll<CMCALLPARAMATER>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCallPlanParameter::SetPreviousPage()
{
    return ppDadeScroll<CMCALLPARAMATER>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCallPlanParameter::GetNext()
{
    return ppDadeScroll<CMCALLPARAMATER>::GetNext();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCallPlanParameter::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCALLPARAMATER>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCallPlanParameter::IsInitialized()
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

bool ppCallPlanParameter::IsChanged()
{
    return !(m_srvParameter->GetStruct() == m_srvParameterUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCallPlanParameter::Restore()
{
    if (IsChanged())
        m_srvParameter->SetStruct(m_srvParameterUP->GetStruct());
}
