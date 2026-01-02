
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCustomerCallPlanTour.cpp
   Author: A.Schmidt-Rehschuh
   made  : 29.06.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlanTour.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCustomerCallPlanTour::SetVertriebsZentrumNr(const short s)
{
    m_srvTour->SetVertriebszentrumnr(s);
}

void ppCustomerCallPlanTour::SetKundenNr(const long l)
{
    m_srvTour->SetKundennr(l);
}

void ppCustomerCallPlanTour::SetWeekday(const ppDayType::t_day eDay)
{
    m_srvTour->SetWeekday( static_cast<short>(eDay) );
}

void ppCustomerCallPlanTour::SetDatumKommi(const long l)
{
    m_srvTour->SetDatumkommi(l);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCustomerCallPlanTour::GetVertriebsZentrumNr() const
{
    return m_srvTour->GetVertriebszentrumnr();
}

const ppDate ppCustomerCallPlanTour::GetDatumKommi() const
{
    return m_srvTour->GetDatumkommi();
}

const ppBool ppCustomerCallPlanTour::GetIstVerbundTour() const
{
    return m_srvTour->GetIstverbundtour();
}

const short ppCustomerCallPlanTour::GetKundenNr() const
{
    return static_cast<short>( m_srvTour->GetKundennr() );
}

const char* ppCustomerCallPlanTour::GetTourID()
{
    return m_srvTour->GetTourid(m_str);
}

const char* ppCustomerCallPlanTour::GetPreparedTourID()
{
   ppString str(m_srvTour->GetTourid(m_str));
   if (str.length() < 6)
       return m_str.c_str();

   m_str = str.substr(4,2) + "/" + str.substr(0, 2) + ":" + str.substr(2, 2);
   return m_str.c_str();
}

const ppTime& ppCustomerCallPlanTour::GetTourIDTime(const ppString& strTourID)
{
    ppString strTime = strTourID.empty() ? GetTourID() : strTourID;

    strTime = strTime.substr(0, 2) + strTime.substr(2, 2);
    m_Time = strTime.stol();
    return m_Time;
}

const short ppCustomerCallPlanTour::GetWeekday()
{
    return m_srvTour->GetWeekday();
}

const short ppCustomerCallPlanTour::GetFilialNr() const
{
    return m_srvTour->GetFilialnr();
}


