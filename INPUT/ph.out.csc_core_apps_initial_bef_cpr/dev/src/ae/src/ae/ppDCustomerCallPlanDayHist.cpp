
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlanDayHist.cpp
   Author: A.Schmidt-Rehschuh
   made  : 21.08.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlanDayHist.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//


void ppCustomerCallPlanDayHist::SetKundenNr(const long l)
{
    m_srvCustomer->SetKundennr(l);
}

void ppCustomerCallPlanDayHist::SetVertriebsZentrumNr(const short s)
{
   m_srvCustomer->SetVertriebszentrumnr(s);
}

void ppCustomerCallPlanDayHist::SetDatum(const long l)
{
    m_srvCustomer->SetDatum(l);
}

void ppCustomerCallPlanDayHist::SetUrRufzeit(const ppTime& t)
{
    m_srvCustomer->SetUrrufzeit(t);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const long  ppCustomerCallPlanDayHist::GetKundenNr() const
{
   return m_srvCustomer->GetKundennr();
}

const short ppCustomerCallPlanDayHist::GetVertriebsZentrumNr() const
{
   return m_srvCustomer->GetVertriebszentrumnr();
}

const long ppCustomerCallPlanDayHist::GetDatum() const
{
    return m_srvCustomer->GetDatum();
}

const ppTime& ppCustomerCallPlanDayHist::GetUrRufzeit()
{
    m_TimeBuf.SetTime(m_srvCustomer->GetUrrufzeit());
    return m_TimeBuf;
}

const ppTime& ppCustomerCallPlanDayHist::GetRufzeit()
{
    m_TimeBuf.SetTime(m_srvCustomer->GetRufzeit());
    return m_TimeBuf;
}

const short ppCustomerCallPlanDayHist::GetUmkStatus() const
{
    return m_srvCustomer->GetUmkstatus();
}

const ppCustomerCallPlanDayHist::t_callstate ppCustomerCallPlanDayHist::GetAnrufStatus() const
{
    return (t_callstate)m_srvCustomer->GetAnrufstatus();
}

const ppCustomerCallPlanDayHist::t_cEvents ppCustomerCallPlanDayHist::GetEreignis() const
{
    return (t_cEvents)m_srvCustomer->GetEreignis();
}

const short ppCustomerCallPlanDayHist::GetFilialNr() const
{
    return m_srvCustomer->GetFilialnr();
}

const long ppCustomerCallPlanDayHist::GetModemNr() const
{
    return m_srvCustomer->GetModemnr();
}

const ppTime ppCustomerCallPlanDayHist::GetUhrzeit() const
{
    ppTime time(m_srvCustomer->GetUhrzeit() / 1000, ppTime::display_hhmmss);
    return time;
}

const char* ppCustomerCallPlanDayHist::GetGeraeteID()
{
    return m_srvCustomer->GetGeraeteid(m_strBuf);
}


const char* ppCustomerCallPlanDayHist::GetUser()
{
    return m_srvCustomer->GetUsername(m_strBuf);
}

const char* ppCustomerCallPlanDayHist::GetEventMsg() const
{
    return ppCallPlanEvents::GetEventMsg(GetEreignis());
}

