
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCallPlanDeviceCheck.cpp
   Author: R.von-der-Gruen
   made  : 19.07.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanDeviceCheck.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCallPlanDeviceCheck::SetVertriebsZentrumNr(const short sSaleCenterNo)
{
   m_srvCallPlanDevice->SetVertriebszentrumnr(sSaleCenterNo);
}

void ppCallPlanDeviceCheck::SetAktiv(const ppBool& b)
{
   m_srvCallPlanDevice->SetAktiv(b);
}

void ppCallPlanDeviceCheck::SetRegionenTyp(const ppRegion::t_region eRegion)
{
    m_srvCallPlanDevice->SetRegionentyp((short)eRegion);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCallPlanDeviceCheck::GetFilialNr() const
{
   return m_srvCallPlanDevice->GetFilialnr();
}

const char* ppCallPlanDeviceCheck::GetGeraeteId()
{
   return m_srvCallPlanDevice->GetGeraeteid(m_str);
}

const short ppCallPlanDeviceCheck::GetUmkNr() const
{
    return m_srvCallPlanDevice->GetUmknr();
}

const long ppCallPlanDeviceCheck::GetGeraetNst() const
{
    return m_srvCallPlanDevice->GetGeraetnst();
}

const ppCallPlanDeviceCheck::t_modemcontrol ppCallPlanDeviceCheck::GetGeraeteVerw1() const
{
    t_modemcontrol nModem;

    switch(m_srvCallPlanDevice->GetGeraeteverw1())
    {
        case is_callout   : nModem = c_outcall; break;
        case is_callin    : nModem = c_incall; break;
        case is_nightorder: nModem = c_nightorder; break;
        default           : nModem = c_incall; break;
    }
    return nModem;
}

const char* ppCallPlanDeviceCheck::GetGeraeteVerw1Text() const
{
    t_modemcontrol nModem;

    switch(m_srvCallPlanDevice->GetGeraeteverw1())
    {
        case is_callout   : nModem = c_outcall; break;
        case is_callin    : nModem = c_incall; break;
        case is_nightorder: nModem = c_nightorder; break;
        default           : nModem = c_incall; break;
    }

    return m_straDevice[nModem].c_str();
}

const long  ppCallPlanDeviceCheck::GetSequenzNr() const
{
   return m_srvCallPlanDevice->GetSequenznr();
}

const ppCallPlanDeviceCheck::t_terminal ppCallPlanDeviceCheck::GetTerminalStatus()
{
   return (t_terminal)GetTerminalPos();
}

const ppTime& ppCallPlanDeviceCheck::GetStartZeit()
{
   ppTime t(m_srvCallPlanDevice->GetStartzeit(), ppTime::display_hhmmss);
   m_Time = t;
   return m_Time;
}

const ppTime& ppCallPlanDeviceCheck::GetEndeZeit()
{
   ppTime t(m_srvCallPlanDevice->GetEndezeit(), ppTime::display_hhmmss);
   m_Time = t;
   return m_Time;
}

const ppTime ppCallPlanDeviceCheck::GetUrrufZeit() const
{
   return m_srvCallPlanDevice->GetUrrufzeit();
}

const short ppCallPlanDeviceCheck::GetVertriebsZentrumNr() const
{
   return m_srvCallPlanDevice->GetVertriebszentrumnr();
}

const long ppCallPlanDeviceCheck::GetKundenNr() const
{
   return m_srvCallPlanDevice->GetKundennr();
}

const ppDate ppCallPlanDeviceCheck::GetDatum() const
{
   return m_srvCallPlanDevice->GetDatum();
}

const char ppCallPlanDeviceCheck::GetAuftragstatus() const
{
   return m_srvCallPlanDevice->GetAuftragstatus();
}

const long ppCallPlanDeviceCheck::GetKdauftragnr1() const
{
   return m_srvCallPlanDevice->GetKdauftragnr1();
}

const short ppCallPlanDeviceCheck::GetPoolnr() const
{
   return m_srvCallPlanDevice->GetPoolnr();
}

const char* ppCallPlanDeviceCheck::GetTerminalStatusText()
{
   return m_strText[GetTerminalPos()].c_str();
}

const ppBool ppCallPlanDeviceCheck::GetAktiv() const
{
   return m_srvCallPlanDevice->GetAktiv();
}

const ppBool ppCallPlanDeviceCheck::GetIsAktiv() const
{
    return m_srvCallPlanDevice->GetStartzeit() > 0 ? true : false;
}


