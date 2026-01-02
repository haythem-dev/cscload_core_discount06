//(c)---------- Customer ClassModel ------------------------------------------//
/*
    Source: ppCallPlanDeviceMaintenance.cpp
    Author: R.von-der-Gruen
    made  : 19.07.2000

    declaration:
    logical part of callplanDeviceOverview-class, Persistence layer (modemanrufplan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanDeviceMaintenance.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCallPlanDeviceMaintenance::ppCallPlanDeviceMaintenance(const ppString& strPath, const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_sSaleCenterNo = 0;
    Init();
}

//--- direct initialization --------------------------------------------------//

ppCallPlanDeviceMaintenance::ppCallPlanDeviceMaintenance(const short sSaleCenterNo,
                                                         const ppString& strPath,
                                                         const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_sSaleCenterNo = sSaleCenterNo;
    Init();
}

//--- deconstructor ----------------------------------------------------------//

ppCallPlanDeviceMaintenance::~ppCallPlanDeviceMaintenance()
{
    if (m_srvCallPlanDevice)
        delete m_srvCallPlanDevice;
    if (m_srvCallPlanDeviceUP)
        delete m_srvCallPlanDeviceUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetUni (unique select) -------------------------------------------------//

bool ppCallPlanDeviceMaintenance::GetUni()
{
    SetVertriebsZentrumNr(m_sSaleCenterNo);
    SetRegionenTyp();
    SetErrorState(ppError::is_ok);
    if (!IsInitialized())
        return false;
    else if (m_srvCallPlanDevice->GetStruct() == m_srvCallPlanDeviceUP->GetStruct())
        return true;

    m_srvCallPlanDevice->SelDevicePlanUni();
    if (m_srvCallPlanDevice->rc == IS_OK)
    {
        m_srvCallPlanDeviceUP->SetStruct(m_srvCallPlanDevice->GetStruct());
        return true;
    }
    else if (m_srvCallPlanDevice->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return false;
}

//--- UpdateCustomer (update selected row) -----------------------------------//

bool ppCallPlanDeviceMaintenance::Update()
{
    if (!IsInitialized())
        return false;
    else if (m_srvCallPlanDevice->GetStruct() == m_srvCallPlanDeviceUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvCallPlanDevice->UpdDevicePlan() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!SetList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCallPlanDeviceUP->SetStruct(m_srvCallPlanDevice->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- InsertCustomer (insert row) --------------------------------------------//

bool ppCallPlanDeviceMaintenance::Insert()
{
    SetVertriebsZentrumNr(m_sSaleCenterNo);
    SetRegionenTyp();

    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvCallPlanDevice->SelNst() == IS_OK)
    {
        SetErrorState(ppError::is_exist);
        return false;
    }

    int rc = m_srvCallPlanDevice->InsertDevice();
    if (rc != IS_OK)
    {
        m_srvCallPlanDevice->ClearStruct();
        m_srvCallPlanDeviceUP->ClearStruct();
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
        default: SetErrorState(ppError::is_sqlerror);
        }
        return false;
    }
    else if (!InsList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCallPlanDeviceUP->SetStruct(m_srvCallPlanDevice->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppCallPlanDeviceMaintenance::Delete()
{
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvCallPlanDevice->Delete() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvCallPlanDevice->ClearStruct();
    m_srvCallPlanDeviceUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCallPlanDeviceMaintenance::StartBrowse()
{
    SetVertriebsZentrumNr(m_sSaleCenterNo);
    SetRegionenTyp();
    return ppDadeScroll<CMDEVICEPLANMAINTENANCE>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCallPlanDeviceMaintenance::SetNextPage()
{
    return ppDadeScroll<CMDEVICEPLANMAINTENANCE>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCallPlanDeviceMaintenance::SetPreviousPage()
{
    return ppDadeScroll<CMDEVICEPLANMAINTENANCE>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCallPlanDeviceMaintenance::GetNext()
{
    return ppDadeScroll<CMDEVICEPLANMAINTENANCE>::GetNext();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCallPlanDeviceMaintenance::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMDEVICEPLANMAINTENANCE>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCallPlanDeviceMaintenance::IsInitialized()
{
    if (GetFilialNr() == 0)
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

bool ppCallPlanDeviceMaintenance::IsChanged()
{
    return !(m_srvCallPlanDevice->GetStruct() == m_srvCallPlanDeviceUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCallPlanDeviceMaintenance::Restore()
{
    if (IsChanged())
        m_srvCallPlanDevice->SetStruct(m_srvCallPlanDeviceUP->GetStruct());
}

//----------------------------------------------------------------------------//
//--- const text-strings -----------------------------------------------------//
//----------------------------------------------------------------------------//

const char* ppCallPlanDeviceMaintenance::GetTextDeviceTyp()
{
    if (m_iPosDevice > c_max || m_iPosDevice < 0)
        m_iPosDevice = 0;
    else if (m_iPosDevice == c_max)
    {
        ++m_iPosDevice;
        return NULL;
    }
    return m_straDevice[m_iPosDevice++].c_str();
}

const char* ppCallPlanDeviceMaintenance::GetTextModemTyp()
{
    if (m_iPosDeviceTyp > c_max || m_iPosDeviceTyp < 0)
        m_iPosDeviceTyp = 0;
    else if (m_iPosDeviceTyp == c_max)
    {
        ++m_iPosDeviceTyp;
        return NULL;
    }
    return m_staDevice[m_iPosDeviceTyp++].GetDeviceTyp();
}

const int ppCallPlanDeviceMaintenance::FindModemTypPos(const char chModemTyp)
{
    int iTyp = chModemTyp;

    for (int i = 0; i < m_max; i++)
    {
        if (iTyp == m_staDevice[i].GetModemTyp())
            return i;
    }

    return -1;
}

const ppCallPlanDeviceMaintenance::t_modemtyp ppCallPlanDeviceMaintenance::FindModemTyp(const ppString& strModemTyp)
{
    for (int i = 0; i < m_max; i++)
    {
        if (strModemTyp == m_staDevice[i].GetDeviceTyp())
            return m_staDevice[i].GetModemTyp();
    }

    return m_staDevice[0].GetModemTyp();
}

//----------------------------------------------------------------------------//
//--- initialize data --------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- Init -------------------------------------------------------------------//

void ppCallPlanDeviceMaintenance::Init()
{
    m_srvCallPlanDevice   = GetSrv();
    m_srvCallPlanDeviceUP = GetSrvUP();
    SetRegionenTyp();
    m_straDevice[c_outcall]    = "Plan"; //TO_DO
    m_straDevice[c_incall]     = "R-Ruf";
    m_straDevice[c_nightorder] = "Nacht" ;
    m_iPosDevice = 0;
    m_straDeviceTyp[0] = "Seriell"; //TO_DO
    m_straDeviceTyp[1] = "Parallel";
    m_straDeviceTyp[2] = "Direktabschluss" ;
    m_iPosDevice = 0;
    m_staDevice[0].Add("Sera", m_seriel );
    m_staDevice[1].Add("Para", m_para );
    m_staDevice[2].Add("Direct", m_direct );
/*  m_straDevice[c_outcall]    = CResString::ex().getStrTblText(AETXT_PLAN);
    m_straDevice[c_incall]     = CResString::ex().getStrTblText(AETXT_R_RUF);
    m_straDevice[c_nightorder] = CResString::ex().getStrTblText(AETXT_NACHT);
    m_iPosDevice = 0;
    m_straDeviceTyp[0] = CResString::ex().getStrTblText(AETXT_SERIELL);
    m_straDeviceTyp[1] = CResString::ex().getStrTblText(AETXT_PARALLEL);
    m_straDeviceTyp[2] = CResString::ex().getStrTblText(AETXT_DIREKT);
    m_iPosDevice = 0;
    m_staDevice[0].Add(CResString::ex().getStrTblText(AETXT_SERA_TXT), m_seriel );
    m_staDevice[1].Add(CResString::ex().getStrTblText(AETXT_PARA_TXT), m_para );
    m_staDevice[2].Add(CResString::ex().getStrTblText(AETXT_DIRECT), m_direct );
*/  m_iPosDeviceTyp = 0;
}
