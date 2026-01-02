//(c)---------- Customer ClassModel ------------------------------------------//
/*
    Source: ppCallPlanDeviceCheck.cpp
    Author: R.von-der-Gruen
    made  : 19.07.2000

    declaration:
    logical part of callplanDeviceOverview-class, Persistence layer (modemanrufplan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanDeviceCheck.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCallPlanDeviceCheck::ppCallPlanDeviceCheck(const ppString& strPath, const short sLanguage)
    : ppError(strPath, sLanguage), m_Time(ppTime::display_hhmmss)
{
    Init();
    m_srvCallPlanDevice   = GetSrv();
    m_srvCallPlanDeviceUP = GetSrvUP();
    SetRegionenTyp();
}

//--- direct initialization --------------------------------------------------//

ppCallPlanDeviceCheck::ppCallPlanDeviceCheck(const short sSaleCenterNo,
                                             const ppString& strPath,
                                             const short sLanguage)
    : ppError(strPath, sLanguage)
{
    Init();
    m_srvCallPlanDevice   = GetSrv();
    m_srvCallPlanDeviceUP = GetSrvUP();
    SetVertriebsZentrumNr(sSaleCenterNo);
    SetRegionenTyp();
}

//--- deconstructor ----------------------------------------------------------//

ppCallPlanDeviceCheck::~ppCallPlanDeviceCheck()
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

bool ppCallPlanDeviceCheck::GetUni()
{
    SetErrorState(ppError::is_ok);

    if (GetVertriebsZentrumNr() == 0 || m_srvCallPlanDevice->GetRegionentyp() == 0 || !IsInitialized())
    {
        SetErrorState(ppError::is_not_initialized);
        return false; //only allowed, if a listselect was done before
    }

    m_srvCallPlanDevice->SelDeviceID();
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

//--- UpdateUMK(switch off/on umk-devices) -----------------------------------//

bool ppCallPlanDeviceCheck::UpdateUMK()
{
    if (GetFilialNr() == 0 || GetUmkNr() == 0)
    {
       SetErrorState(ppError::is_not_initialized);
       return false;
    }
    //set aktiv = true/false where filialnr = ? and umknr = ?
    if (m_srvCallPlanDevice->UpdUMKDecivePlan() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    SetErrorState(ppError::is_ok);
    return true;
}

//--- Update (update selected row) -------------------------------------------//

bool ppCallPlanDeviceCheck::Update()
{
    if (!IsInitialized())
        return false;
    else if (m_srvCallPlanDevice->GetStruct() == m_srvCallPlanDeviceUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvCallPlanDevice->UpdateDirect() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    m_srvCallPlanDeviceUP->SetStruct(m_srvCallPlanDevice->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppCallPlanDeviceCheck::StartBrowse()
{
    return ppDadeScroll<CMDEVICEPLANCHECK>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppCallPlanDeviceCheck::SetNextPage(const t_checktyp e)
{
    if (e == m_devicecheck)
        return ppDadeScroll<CMDEVICEPLANCHECK>::SetNextPage();
    else if (e == m_umkcheck)
        return ppDadeScroll<CMDEVICEPLANCHECK>::SetNextPage(ppDadeScroll<CMDEVICEPLANCHECK>::list_history);
    else
        return false;
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppCallPlanDeviceCheck::SetPreviousPage()
{
    return ppDadeScroll<CMDEVICEPLANCHECK>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppCallPlanDeviceCheck::GetNext(const t_checktyp e)
{
    if (e == m_devicecheck)
        return ppDadeScroll<CMDEVICEPLANCHECK>::GetNext();
    else if (e == m_umkcheck)
        return ppDadeScroll<CMDEVICEPLANCHECK>::GetNext(true, ppDadeScroll<CMDEVICEPLANCHECK>::list_history);
    else
        return false;
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppCallPlanDeviceCheck::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMDEVICEPLANCHECK>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- info about modem -------------------------------------------------------//
//----------------------------------------------------------------------------//

const ppCallPlanDeviceCheck::t_modem ppCallPlanDeviceCheck::GetModemState(const ppTime& time)
{
    if (!(ppBool)GetAktiv())
    {
        return m_isnotactive;
    }
    else if (GetSequenzNr() == 0)
    {
        return m_isfree;
    }
    else if ( GetSequenzNr() != 0 &&
              ((t_terminal)GetTerminalPos() == t_calling || (t_terminal)GetTerminalPos() == t_sending) )
    {
        return m_isengaged;
    }
    else if ( GetSequenzNr() != 0 &&
              (ppTime)time - (ppTime&)GetStartZeit() > (7 * 60) &&
              ((t_terminal)GetTerminalPos() == t_break_off || (t_terminal)GetTerminalPos() == t_call_is_ended) )
    {
        return m_iswarning;
    }

    return m_iserror;
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

//--- IsInitialized ----------------------------------------------------------//

bool ppCallPlanDeviceCheck::IsInitialized()
{
    if (GetFilialNr() == 0 || GetGeraeteId() == (char*)0)
    {
      SetErrorState(ppError::is_not_initialized);
      return false;
   }
   return true;
}

//--- Init -------------------------------------------------------------------//

void ppCallPlanDeviceCheck::Init()
{
    const int iTerminal[] = { 'F', 'B', 'D', 'A', 'R', ' ' };
    const ppString strText[] = { "frei", "wählt", "Dafü aktiv", "Dafüabbruch", "Dafü beendet", "frei" //TO_DO
        /*CResString::ex().getStrTblText(AETXT_FREI),
          CResString::ex().getStrTblText(AETXT_WAEHLT),
          CResString::ex().getStrTblText(AETXT_DAFUE_AKTIV),
          CResString::ex().getStrTblText(AETXT_DAFUE_ABBRUCH),
          CResString::ex().getStrTblText(AETXT_DAFUE_BEENDET),
          CResString::ex().getStrTblText(AETXT_FREI)*/
        /*, "interner Fehler"*/
    };

    for (int i = 0; i < t_max_entry; i++)
    {
        m_strText[i] = strText[i];
        m_iTerminal[i] = iTerminal[i];
    }

    m_straDevice[c_outcall]    = "Plan";   //TO_DO
    m_straDevice[c_incall]     = "R-Ruf";
    m_straDevice[c_nightorder] = "Nacht";
    /*m_straDevice[c_outcall]    = CResString::ex().getStrTblText(AETXT_PLAN);
      m_straDevice[c_incall]     = CResString::ex().getStrTblText(AETXT_R_RUF);
      m_straDevice[c_nightorder] = CResString::ex().getStrTblText(AETXT_NACHT);*/
}

//--- GetTerminalPos ---------------------------------------------------------//

const int ppCallPlanDeviceCheck::GetTerminalPos()
{
    for (int i = 0; i < t_max_entry; i++)
    {
        if (m_iTerminal[i] == m_srvCallPlanDevice->GetTerminalstatus())
            return i;
    }
    return t_error;
}

//--- Release ----------------------------------------------------------------//

void ppCallPlanDeviceCheck::Release()
{
    m_srvCallPlanDevice->SetSequenznr(0);
    m_srvCallPlanDevice->SetTerminalstatus('F');
    m_srvCallPlanDevice->SetStartzeit(0);
    m_srvCallPlanDevice->SetEndezeit(0);
    m_srvCallPlanDevice->SetVertriebszentrumnr(0);
    m_srvCallPlanDevice->SetKundennr(0);
    m_srvCallPlanDevice->SetUrrufzeit(0);
    m_srvCallPlanDevice->SetDatum(0);
    m_srvCallPlanDevice->SetAuftragstatus(' ');
    m_srvCallPlanDevice->SetKdauftragnr1(0);
}
