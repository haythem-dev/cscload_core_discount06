
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCallPlanParameter.cpp
   Author: A.Schmidt-Rehschuh
   made  : 29.06.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanParameter.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCallPlanParameter::SetVertriebsZentrumNr(const short s)
{
    m_srvParameter->SetVertriebszentrumnr(s);
}

void ppCallPlanParameter::SetRufzeitVerschieben(const short s)
{
    m_srvParameter->SetRufzeitverschieben(s);
}

void ppCallPlanParameter::SetAnzrufWiederholung(const short s)
{
    m_srvParameter->SetAnzrufwiederholung(s);
}

void ppCallPlanParameter::SetKabrufWiederholung(const short s)
{
    m_srvParameter->SetKabrufwiederholung(s);
}

void ppCallPlanParameter::SetUmkrufWiederholung(const short s)
{
    m_srvParameter->SetUmkrufwiederholung(s);
}

void ppCallPlanParameter::SetZeitfensterAuftrag(const short s)
{
    m_srvParameter->SetZeitfensterauftrag(s);
}

void ppCallPlanParameter::SetZeitAnzPosAuftrag(const short s)
{
    m_srvParameter->SetZeitanzposauftrag(s);
}

void ppCallPlanParameter::SetLoginID(const long l)
{
    m_srvParameter->SetLoginid(l);
}

void ppCallPlanParameter::SetAnzRufVerschieben(const short s)
{
    m_srvParameter->SetAnzrufverschieben(s);
}

void ppCallPlanParameter::SetMinRufVerschieben(const short s)
{
    m_srvParameter->SetMinrufverschieben(s);
}

void ppCallPlanParameter::SetCallplanStartStop(const ppBool& b)
{
    m_srvParameter->SetCallplanstartstop(b);
}

void ppCallPlanParameter::SetStopStartZeit(const ppTime& t)
{
    long time = static_cast<long>(t);
    m_srvParameter->SetStopstartzeit( static_cast<short>(time) );
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCallPlanParameter::GetVertriebsZentrumNr() const
{
    return m_srvParameter->GetVertriebszentrumnr();
}

const short ppCallPlanParameter::GetRufzeitVerschieben() const
{
    return m_srvParameter->GetRufzeitverschieben();
}

const short ppCallPlanParameter::GetAnzrufWiederholung() const
{
    return m_srvParameter->GetAnzrufwiederholung();
}

const short ppCallPlanParameter::GetKabrufWiederholung() const
{
    return m_srvParameter->GetKabrufwiederholung();
}

const short ppCallPlanParameter::GetUmkrufWiederholung() const
{
    return m_srvParameter->GetUmkrufwiederholung();
}

const short ppCallPlanParameter::GetZeitfensterAuftrag() const
{
    return m_srvParameter->GetZeitfensterauftrag();
}

const short ppCallPlanParameter::GetZeitAnzPosAuftrag() const
{
    return m_srvParameter->GetZeitanzposauftrag();
}

const long ppCallPlanParameter::GetLoginID() const
{
    return m_srvParameter->GetLoginid();
}

const ppDate ppCallPlanParameter::GetDate() const
{
    return m_srvParameter->GetTm_date();
}

const ppTime ppCallPlanParameter::GetTime() const
{
    return m_srvParameter->GetTm_time();
}

const short ppCallPlanParameter::GetRufabweichungPH() const
{
    return m_srvParameter->GetRufabweichungph();
}

const short ppCallPlanParameter::GetRufabweichungDP() const
{
    return m_srvParameter->GetRufabweichungdp();
}

const short ppCallPlanParameter::GetRufabweichungDS() const
{
    return m_srvParameter->GetRufabweichungds();
}

const short ppCallPlanParameter::GetAnzRufVerschieben() const
{
    return m_srvParameter->GetAnzrufverschieben();
}

const short ppCallPlanParameter::GetMinRufVerschieben() const
{
    return m_srvParameter->GetMinrufverschieben();
}

const ppBool ppCallPlanParameter::GetCallplanStartStop() const
{
    return m_srvParameter->GetCallplanstartstop();
}

const ppTime ppCallPlanParameter::GetStopStartZeit() const
{
    return m_srvParameter->GetStopstartzeit();
}

//----------------------------------------------------------------------------//
//--- Data-Get-Length-Methodes -----------------------------------------------//
//----------------------------------------------------------------------------//

const ppFieldLength ppCallPlanParameter::LengthVertriebsZentrumNr() const
{
   return L_MCALLPARAMATER_VERTRIEBSZENTRUMNR;
}

const ppFieldLength ppCallPlanParameter::LengthRufzeitVerschieben() const
{
   return L_MCALLPARAMATER_RUFZEITVERSCHIEBEN;
}

const ppFieldLength ppCallPlanParameter::LengthAnzrufWiederholung() const
{
   return L_MCALLPARAMATER_ANZRUFWIEDERHOLUNG;
}

const ppFieldLength ppCallPlanParameter::LengthZeitfensterAuftrag() const
{
   return L_MCALLPARAMATER_ZEITFENSTERAUFTRAG;
}

const ppFieldLength ppCallPlanParameter::LengthZeitAnzPosAuftrag() const
{
   return L_MCALLPARAMATER_ZEITANZPOSAUFTRAG;
}

const ppFieldLength ppCallPlanParameter::LengthLoginID() const
{
   return L_MCALLPARAMATER_LOGINID ;
}

const ppFieldLength ppCallPlanParameter::LengthDate() const
{
   return 8;
}

const ppFieldLength ppCallPlanParameter::LengthTime() const
{
   return 6;
}

