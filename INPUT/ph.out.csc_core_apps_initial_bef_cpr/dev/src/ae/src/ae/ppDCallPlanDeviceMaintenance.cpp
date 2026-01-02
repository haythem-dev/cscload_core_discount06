
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCallPlanDeviceMaintenance
   Author: A.Schmidt-Rehschuh
   made  : 21.07.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanDeviceMaintenance.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCallPlanDeviceMaintenance::SetVertriebsZentrumNr(const short sSaleCenterNo)
{
   m_sSaleCenterNo = sSaleCenterNo;
   m_srvCallPlanDevice->SetVertriebszentrumnr(sSaleCenterNo);
}

void ppCallPlanDeviceMaintenance::SetRegionenTyp(const ppRegion::t_region eRegion)
{
    m_srvCallPlanDevice->SetRegionentyp((short)eRegion);
}

void ppCallPlanDeviceMaintenance::SetFilialNr(const short s)
{
    m_srvCallPlanDevice->SetFilialnr(s);
}

void ppCallPlanDeviceMaintenance::SetGeraeteID(const ppString& s)
{
    m_srvCallPlanDevice->SetGeraeteid(s);
}

void ppCallPlanDeviceMaintenance::SetGeraeteArt(const char ch)
{
    m_srvCallPlanDevice->SetGeraeteart(ch);
}

void ppCallPlanDeviceMaintenance::SetGeraetNst(const long l)
{
    m_srvCallPlanDevice->SetGeraetnst(l);
}

void ppCallPlanDeviceMaintenance::SetGeraeteverw1(const ppCallPlanDeviceMaintenance::t_modemcontrol t)
{
    i_modemcontrol nModem;

    switch (t)
    {
        case c_outcall:      nModem = ic_outcall; break;
        case c_nightorder:   nModem = ic_nightorder; break;
        case c_incall:       nModem = ic_incall; break;
        default:             nModem = ic_incall; break;
    }

    m_srvCallPlanDevice->SetGeraeteverw1( static_cast<char>(nModem) );
}

void ppCallPlanDeviceMaintenance::SetModemTyp(const char ch)
{
   m_srvCallPlanDevice->SetModemtyp(ch);
}

void ppCallPlanDeviceMaintenance::SetUmkNr(const short s)
{
   m_srvCallPlanDevice->SetUmknr(s);
}

void ppCallPlanDeviceMaintenance::SetLoginID(const long l)
{
   m_srvCallPlanDevice->SetLoginid(l);
}

void ppCallPlanDeviceMaintenance::SetAktiv(const ppBool& l)
{
   m_srvCallPlanDevice->SetAktiv(l);
}

void ppCallPlanDeviceMaintenance::SetUmkNst(const short s)
{
   m_srvCallPlanDevice->SetUmknst(s);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCallPlanDeviceMaintenance::GetVertriebsZentrumNr() const
{
   return m_srvCallPlanDevice->GetVertriebszentrumnr();
}

const short ppCallPlanDeviceMaintenance::GetFilialNr() const
{
   return m_srvCallPlanDevice->GetFilialnr();
}

const char* ppCallPlanDeviceMaintenance::GetGeraeteId()
{
   return m_srvCallPlanDevice->GetGeraeteid(m_str);
}

const short ppCallPlanDeviceMaintenance::GetUmkNr() const
{
    return m_srvCallPlanDevice->GetUmknr();
}

const long ppCallPlanDeviceMaintenance::GetGeraetNst() const
{
    return m_srvCallPlanDevice->GetGeraetnst();
}

const char* ppCallPlanDeviceMaintenance::GetGeraeteVerw1Text() const
{
    return m_straDevice[GetGeraeteVerw1()].c_str();
}

const char* ppCallPlanDeviceMaintenance::GetGeraeteVerw1Text(const ppCallPlanDeviceMaintenance::t_modemcontrol t) const
{
    return m_straDevice[t].c_str();
}

const ppCallPlanDeviceMaintenance::t_modemcontrol ppCallPlanDeviceMaintenance::GetGeraeteVerw1() const
{
    t_modemcontrol nModem;

    switch (m_srvCallPlanDevice->GetGeraeteverw1())
    {
        case ic_outcall:     nModem = c_outcall; break;
        case ic_nightorder:  nModem = c_nightorder; break;
        case ic_incall:      nModem = c_incall; break;
        default:             nModem = c_incall; break;
    }
    return nModem;
}

const char ppCallPlanDeviceMaintenance::GetGeraeteArt() const
{
   return m_srvCallPlanDevice->GetGeraeteart();
}

const char ppCallPlanDeviceMaintenance::GetModemTyp() const
{
   return m_srvCallPlanDevice->GetModemtyp();
}

const long ppCallPlanDeviceMaintenance::GetLoginID() const
{
   return m_srvCallPlanDevice->GetLoginid();
}

const ppDate ppCallPlanDeviceMaintenance::GetDate() const
{
   return m_srvCallPlanDevice->GetTm_date();
}

const ppTime ppCallPlanDeviceMaintenance::GetTime() const
{
   return m_srvCallPlanDevice->GetTm_time();
}

const ppBool ppCallPlanDeviceMaintenance::GetAktiv() const
{
   return m_srvCallPlanDevice->GetAktiv();
}

const short ppCallPlanDeviceMaintenance::GetUmkNst() const
{
   return m_srvCallPlanDevice->GetUmknst();
}

