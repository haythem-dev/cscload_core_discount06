//(c)---------- Customer ClassModel ------------------------------------------//
/*
    Source: ppCheckRecallProcess.cpp
    Author: A.Schmidt-Rehschuh
    made  : 12.07.2000

    declaration:
    logical part of customerbase-class, Persistence layer (CallPlan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCheckRecallProcess.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCheckRecallProcess::ppCheckRecallProcess(const ppCustomerCallPlanDay* pCallPlan,
                                           const long lUID,
                                           const short sBranchNo)
    : ppError(pCallPlan->GetPath(), pCallPlan->GetLanguage())
{
    m_srvPlan   = new CMCUSTOMERCALLPLANRECALLINWORK;
    m_pCallPlan = pCallPlan;
    m_srvPlan->SetFilialnr(sBranchNo);
    m_srvPlan->SetUid(lUID);
    m_eCheck = is_error;
}

//--- deconstructor ----------------------------------------------------------//

ppCheckRecallProcess::~ppCheckRecallProcess()
{
    if (m_srvPlan)
        delete m_srvPlan;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetCustomer (unique select) --------------------------------------------//

bool ppCheckRecallProcess::CheckEntry()
{
    m_eCheck = is_error;
    SetErrorState(ppError::is_ok);
    m_srvPlan->SetVertriebszentrumnr(m_pCallPlan->GetVertriebsZentrumNr());
    m_srvPlan->SetKundennr(m_pCallPlan->GetKundenNr());
    m_srvPlan->SetDatum(m_pCallPlan->GetDatum());
    m_srvPlan->SetUrrufzeit(((ppCustomerCallPlanDay*)m_pCallPlan)->GetUrRufzeit());

    if (!IsInitialized())
        return false;

    const long lUID = m_srvPlan->GetUid();
    m_srvPlan->Select();
    if (m_srvPlan->rc == IS_OK)
    {
        SetUID(lUID);
        m_eCheck = is_in_use;
        return false;
    }
    else if (m_srvPlan->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
        return SetEntry();
    }

    return false;
}

//--- DeleteEntry (unique select) --------------------------------------------//

bool ppCheckRecallProcess::DeleteEntry()
{
    if (!IsInitialized())
        return false;

    if (m_eCheck == is_ok || m_eCheck == is_used_by_own)
    {
        const long lUID = m_srvPlan->GetUid();
        if (m_srvPlan->Delete() != IS_OK)
        {
            SetErrorState(ppError::is_sqlerror);
            return false;
        }

        m_srvPlan->ClearStruct();
        SetUID(lUID);
    }

    m_eCheck = is_deleted;
    SetErrorState(ppError::is_ok);
    return true;
}

//--- GetCustomer (unique select) --------------------------------------------//

bool ppCheckRecallProcess::SetEntry()
{
    m_srvPlan->SetVertriebszentrumnr(m_pCallPlan->GetVertriebsZentrumNr());
    m_srvPlan->SetKundennr(m_pCallPlan->GetKundenNr());
    m_srvPlan->SetDatum(m_pCallPlan->GetDatum());
    m_srvPlan->SetUrrufzeit(((ppCustomerCallPlanDay*)m_pCallPlan)->GetUrRufzeit());

    if (!IsInitialized())
        return false;

    if (m_srvPlan->Insert() == IS_OK)
    {
        SetErrorState(ppError::is_ok);
        m_eCheck = is_ok;
        return true;
    }
    else if (m_srvPlan->rc == IS_EXISTS)
    {
        m_eCheck = is_used_by_own;
        SetErrorState(ppError::is_exist);
    }
    else
        SetErrorState(ppError::is_sqlerror);

    return false;
}

//--- UpdateEntry (unique update) --------------------------------------------//

bool ppCheckRecallProcess::UpdateEntry()
{
    if (!IsInitialized())
        return false;

    if (m_srvPlan->Update() == IS_OK)
    {
        SetErrorState(ppError::is_ok);
        return true;
    }

    SetErrorState(ppError::is_sqlerror);
    return false;
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCheckRecallProcess::IsInitialized()
{
    if (m_srvPlan->GetVertriebszentrumnr() == 0 ||
        m_srvPlan->GetKundennr() == 0 ||
        m_srvPlan->GetDatum() == 0 ||
        m_srvPlan->GetUrrufzeit() == 0 ||
        m_srvPlan->GetUid() == 0)
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------//
//--- get/set-methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- set-methodes -----------------------------------------------------------//

void ppCheckRecallProcess::SetUID(const long l)
{
    m_srvPlan->SetUid(l);
}

const ppCheckRecallProcess::t_check ppCheckRecallProcess::GetCheckState() const
{
    return m_eCheck;
}
