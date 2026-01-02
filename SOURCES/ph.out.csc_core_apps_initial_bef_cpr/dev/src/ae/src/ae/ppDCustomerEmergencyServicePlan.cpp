
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCustomerEmergencyServicePlan.cpp
   Author: R.Imschweiler
   made  : 14.05.2001

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include <customer.h>
#include "ppCustomerEmergencyServicePlan.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCustomerEmergencyServicePlan::SetVertriebsZentrumNr(const short s)
{
    m_srvServicePlan->SetVertriebszentrumnr(s);
}

void ppCustomerEmergencyServicePlan::SetKundennr(const long s)
{
    m_srvServicePlan->SetKundennr(s);
}

void ppCustomerEmergencyServicePlan::SetDatum(const long s)
{
    m_srvServicePlan->SetDatum(s);
}

void ppCustomerEmergencyServicePlan::SetUhrzeitvon(const long s)
{
    m_srvServicePlan->SetUhrzeitvon(s);
}

void ppCustomerEmergencyServicePlan::SetUhrzeitbis(const long s)
{
    m_srvServicePlan->SetUhrzeitbis(s);
}

void ppCustomerEmergencyServicePlan::SetIsbtm(const short s)
{
    m_srvServicePlan->SetIsbtm(s);
}

void ppCustomerEmergencyServicePlan::SetIskk(const short s)
{
    m_srvServicePlan->SetIskk(s);
}

void ppCustomerEmergencyServicePlan::SetIsk08(const short s)
{
    m_srvServicePlan->SetIsk08(s);
}

void ppCustomerEmergencyServicePlan::SetIsk20(const short s)
{
    m_srvServicePlan->SetIsk20(s);
}

void ppCustomerEmergencyServicePlan::SetBemerkungen(const char* str)
{
    m_srvServicePlan->SetBemerkungen(str);
}


//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCustomerEmergencyServicePlan::GetVertriebsZentrumNr() const
{
    return m_srvServicePlan->GetVertriebszentrumnr();
}

const long ppCustomerEmergencyServicePlan::GetKundennr() const
{
    return m_srvServicePlan->GetKundennr();
}

const long ppCustomerEmergencyServicePlan::GetDatum() const
{
    return m_srvServicePlan->GetDatum();
}

const long ppCustomerEmergencyServicePlan::GetUhrzeitvon() const
{
    return m_srvServicePlan->GetUhrzeitvon();
}

const long ppCustomerEmergencyServicePlan::GetUhrzeitbis() const
{
    return m_srvServicePlan->GetUhrzeitbis();
}

const short ppCustomerEmergencyServicePlan::GetIsbtm()
{
    return m_srvServicePlan->GetIsbtm();
}

const short ppCustomerEmergencyServicePlan::GetIskk()
{
    return m_srvServicePlan->GetIskk();
}

const short ppCustomerEmergencyServicePlan::GetIsk08()
{
    return m_srvServicePlan->GetIsk08();
}

const short ppCustomerEmergencyServicePlan::GetIsk20()
{
    return m_srvServicePlan->GetIsk20();
}

const char* ppCustomerEmergencyServicePlan::GetBemerkungen()
{
    return m_srvServicePlan->GetBemerkungen(m_strBuf);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Length-Methodes -----------------------------------------------//
//----------------------------------------------------------------------------//
/*  Beispiel
const ppFieldLength ppCustomerEmergencyServicePlan::LengthVertriebsZentrumNr() const
{
   return L_MCALLPARAMATER_VERTRIEBSZENTRUMNR;
}
*/
