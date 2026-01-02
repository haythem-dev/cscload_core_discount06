//(c)---------- Customer ClassModel ------------------------------------------//
/*
    Source: ppCallPlanLoad.cpp
    Author: R.von-der-Gruen
    made  : 07.07.2000

    declaration:
    logical part of callplanload-class, Persistence layer (LoadCallPlan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanLoad.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCallPlanLoad::ppCallPlanLoad(const ppString& strPath, const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvCallPlanLoad   = GetSrv();
    m_srvCallPlanLoadUP = GetSrvUP();
    m_bIsAvailable = false;
}

//--- direct initialization --------------------------------------------------//

ppCallPlanLoad::ppCallPlanLoad(const short sSaleCenterNo,
                               const long lDatum,
                               const ppString& strPath,
                               const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvCallPlanLoad = GetSrv();
    m_srvCallPlanLoadUP = GetSrvUP();
    SetVertriebsZentrumNr(sSaleCenterNo);
    SetLadeDatum(lDatum);
    m_bIsAvailable = false;
    GetUni();
}

//--- deconstructor ----------------------------------------------------------//

ppCallPlanLoad::~ppCallPlanLoad()
{
    if (m_srvCallPlanLoad)
        delete m_srvCallPlanLoad;
    if (m_srvCallPlanLoadUP)
        delete m_srvCallPlanLoadUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetUni (unique select) -------------------------------------------------//

bool ppCallPlanLoad::GetUni(const bool bAlways)
{
    SetErrorState(ppError::is_ok);
    if (!IsInitialized())
    {
        return false;
    }
    else if (!bAlways && m_srvCallPlanLoad->GetStruct() == m_srvCallPlanLoadUP->GetStruct())
        return true;

    IsDataAvailable();
    m_srvCallPlanLoad->GetInitializeData();
    m_srvCallPlanLoadUP->SetDatum(-1);
    if (m_srvCallPlanLoad->rc == IS_OK)
    {
        m_srvCallPlanLoadUP->SetStruct(m_srvCallPlanLoad->GetStruct());
        return true;
    }
    else if (m_srvCallPlanLoad->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return false;
}

//--- GetUni (unique select) -------------------------------------------------//

bool ppCallPlanLoad::IsDataAvailable()
{
    m_srvCallPlanLoad->SelCallPlanLoad();
    if (m_srvCallPlanLoad->rc == IS_OK)
    {
        return (m_bIsAvailable = true);
    }
    else if (m_srvCallPlanLoad->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return (m_bIsAvailable = false);
}

//--- Update (update ) -------------------------------------------------------//

bool ppCallPlanLoad::Update()
{
    if (m_srvCallPlanLoad->GetStruct() == m_srvCallPlanLoadUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvCallPlanLoad->UpdCallPlanLoad() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCallPlanLoadUP->SetStruct(m_srvCallPlanLoad->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- Insert (insert row) ----------------------------------------------------//

bool ppCallPlanLoad::Insert()
{
    if (!IsInitialized())
    {
        return false;
    }

    int rc = m_srvCallPlanLoad->Insert();
    if (rc != IS_OK)
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
            m_srvCallPlanLoad->ClearStruct();
            m_srvCallPlanLoadUP->ClearStruct();
        }

        return false;
    }
    else if (!InsList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_bIsAvailable = true;
    m_srvCallPlanLoadUP->SetStruct(m_srvCallPlanLoad->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- Delete (delete selected row) -------------------------------------------//

bool ppCallPlanLoad::Delete()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvCallPlanLoad->DelCallPlanLoad() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_srvCallPlanLoad->ClearStruct();
    m_srvCallPlanLoadUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCallPlanLoad::IsInitialized()
{
    if (m_srvCallPlanLoad->GetVertriebszentrumnr() == 0 || m_srvCallPlanLoad->GetLadedatum() == 0)
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCallPlanLoad::StartBrowse()
{
    SetVertriebsZentrumNr(m_srvCallPlanLoad->GetVertriebszentrumnr());
    return ppDadeScroll<CMCALLPLANLOAD>::StartBrowse();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCallPlanLoad::GetNext()
{
    SetErrorState(ppError::is_ok);

    bool bReturn = ppDadeScroll<CMCALLPLANLOAD>::GetNext();

    if (!bReturn)
    {
        SetErrorState(ppError::is_notfound);
    }

    return bReturn;
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCallPlanLoad::SetNextPage()
{
    return ppDadeScroll<CMCALLPLANLOAD>::SetNextPage();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCallPlanLoad::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMCALLPLANLOAD>::SetElement(nPos);
}
