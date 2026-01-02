//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCallPlanUndertake.cpp
   Author: A.Schmidt-Rehschuh
   made  : 12.07.2000

   declaration:
   logical part of customerbase-class, Persistence layer (CallPlan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include <callplanundertake.h>
#include "ppCallPlanUndertake.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCallPlanUndertake::ppCallPlanUndertake(const ppString& strPath, const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvPlan   = new CMCALLPLANUNDERTAKE;
    m_srvPlanUP = new CMCALLPLANUNDERTAKE;
    m_lEntries = 0;
}

//--- direct initialization --------------------------------------------------//

ppCallPlanUndertake::ppCallPlanUndertake(const short sSaleCenterNo,
                                         const ppString& strPath,
                                         const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvPlan = new CMCALLPLANUNDERTAKE;
    m_srvPlanUP = new CMCALLPLANUNDERTAKE;
    m_srvPlan->SetVertriebszentrumnr(sSaleCenterNo);
    m_lEntries = 0;
}

//--- deconstructor ----------------------------------------------------------//

ppCallPlanUndertake::~ppCallPlanUndertake()
{
    if (m_srvPlan)
        delete m_srvPlan;
    if (m_srvPlanUP)
        delete m_srvPlanUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetCustomer (unique select) --------------------------------------------//

bool ppCallPlanUndertake::CheckEntries(const bool bIsSera /*=true*/)
{
    SetErrorState(ppError::is_ok);
    if (!IsInitialized())
    {
        return false;
    }

    if (bIsSera)
    {
        m_srvPlan->CheckAvailableEntries();
    }
    else
    {
        m_srvPlan->CheckAvailableEntriesPhon();
    }

    m_srvPlanUP->SetVertriebszentrumnr(-1);
    if (m_srvPlan->rc == IS_OK)
    {
        m_srvPlanUP->SetStruct(m_srvPlan->GetStruct());
        m_lEntries = m_srvPlan->GetKundennr();
        return true;
    }
    else if (m_srvPlan->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return false;
}

//--- DeleteEntries (unique select) ------------------------------------------//

bool ppCallPlanUndertake::DeleteEntries()
{
    if (!IsInitialized())
        return false;

    const short sSaleCenterNo = GetVertriebsZentrumNr();
    if (m_srvPlan->DelAll() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_lEntries = 0;
    m_srvPlan->ClearStruct();
    SetVertriebsZentrumNr(sSaleCenterNo);
    m_srvPlanUP->SetStruct(m_srvPlan->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteEvents (unique select) -------------------------------------------//

bool ppCallPlanUndertake::DeleteEvents()
{
    if (!IsInitialized())
        return false;

    const short sSaleCenterNo = GetVertriebsZentrumNr();
    if (m_srvPlan->DelEvents() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_lEntries = 0;
    m_srvPlan->ClearStruct();
    SetVertriebsZentrumNr(sSaleCenterNo);
    m_srvPlanUP->SetStruct(m_srvPlan->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- GetCustomer (unique select) --------------------------------------------//

bool ppCallPlanUndertake::Undertake()
{
    if (!IsInitialized())
        return false;

    if (m_srvPlan->UndertakeCallplan() != IS_OK)
    {
        if (m_srvPlan->rc == IS_NOTFOUND)
            SetErrorState(ppError::is_notfound);
        else
            SetErrorState(ppError::is_sqlerror);

        return false;
    }

    m_srvPlan->ClearStruct();
    m_srvPlanUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//--- GetCustomer (unique select) --------------------------------------------//

bool ppCallPlanUndertake::UndertakePhon()
{
    if (!IsInitialized())
        return false;

    if (m_srvPlan->UndertakeCallplanPhon() != IS_OK)
    {
        if (m_srvPlan->rc == IS_NOTFOUND)
            SetErrorState(ppError::is_notfound);
        else
            SetErrorState(ppError::is_sqlerror);

        return false;
    }

    m_srvPlan->ClearStruct();
    m_srvPlanUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteEntriesPhon (unique select) --------------------------------------//

bool ppCallPlanUndertake::DeleteEntriesPhon()
{
    if (!IsInitialized())
        return false;

    const short sSaleCenterNo = GetVertriebsZentrumNr();
    if (m_srvPlan->DelAllPhon() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_lEntries = 0;
    m_srvPlan->ClearStruct();
    SetVertriebsZentrumNr(sSaleCenterNo);
    m_srvPlanUP->SetStruct(m_srvPlan->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteEventsPhon (unique select) ---------------------------------------//

bool ppCallPlanUndertake::DeleteEventsPhon()
{
    if (!IsInitialized())
        return false;

    const short sSaleCenterNo = GetVertriebsZentrumNr();
    if (m_srvPlan->DelEventsPhon() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_lEntries = 0;
    m_srvPlan->ClearStruct();
    SetVertriebsZentrumNr(sSaleCenterNo);
    m_srvPlanUP->SetStruct(m_srvPlan->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCallPlanUndertake::IsInitialized()
{
    if (m_srvPlan->GetVertriebszentrumnr() == 0)
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

void ppCallPlanUndertake::SetVertriebsZentrumNr(const short vertriebsZentrumNr)
{
    m_srvPlan->SetVertriebszentrumnr(vertriebsZentrumNr);
}

void ppCallPlanUndertake::SetLadeDatum(const ppDate& ladeDatum)
{
    m_srvPlan->SetDatum(ladeDatum);
}

//--- get-methodes -----------------------------------------------------------//

const short ppCallPlanUndertake::GetVertriebsZentrumNr() const
{
    return m_srvPlan->GetVertriebszentrumnr();
}

const ppDate ppCallPlanUndertake::GetLadeDatum() const
{
    return m_srvPlan->GetDatum();
}

const long ppCallPlanUndertake::GetCount() const
{
    return m_lEntries;
}
