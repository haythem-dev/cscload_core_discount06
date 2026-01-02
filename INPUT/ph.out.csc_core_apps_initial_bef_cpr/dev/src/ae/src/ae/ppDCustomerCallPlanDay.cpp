
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlanDay.cpp
   Author: A.Schmidt-Rehschuh
   made  : 29.02.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlanDay.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//


void ppCustomerCallPlanDay::SetKundenNr(const long l)
{
    m_srvCustomer->SetKundennr(l);
}

void ppCustomerCallPlanDay::SetIdfnr(const long l)
{
    m_srvCustomer->SetIdfnr(l);
}

void ppCustomerCallPlanDay::SetVertriebsZentrumNr(const short s)
{
   m_srvCustomer->SetVertriebszentrumnr(s);
}

void ppCustomerCallPlanDay::SetDatum(const long l)
{
    m_srvCustomer->SetDatum(l);
}

void ppCustomerCallPlanDay::SetUrRufzeit(const ppTime t)
{
    m_srvCustomer->SetUrrufzeit(t);
}

void ppCustomerCallPlanDay::SetRufzeit(const ppTime& t)
{
    m_lCallTime = GetRufzeit();
    m_srvCustomer->SetRufzeit(t);
}

void ppCustomerCallPlanDay::SetUmkStatus(const short s)
{
    m_srvCustomer->SetUmkstatus(s);
}

void ppCustomerCallPlanDay::SetAnrufStatus(const t_callstate s)
{
    m_Callstate = GetAnrufStatus(); //save the old state
    m_srvCustomer->SetAnrufstatus((short)s);
}

void ppCustomerCallPlanDay::SetAnrufZaehler(const short s)
{
    m_srvCustomer->SetAnrufzaehler(s);
}

void ppCustomerCallPlanDay::SetTourID(const ppString& str)
{
    m_srvCustomer->SetTourid(str);
}

void ppCustomerCallPlanDay::SetSTourDefinitiv(const ppBool& b)
{
    m_srvCustomer->SetStourdefinitiv(b);
}

void ppCustomerCallPlanDay::SetTagNr(const short s)
{
    m_srvCustomer->SetTagnr(static_cast<char>(s + '0'));
}

void ppCustomerCallPlanDay::SetRufProtokoll(const t_callrecord e)
{
    m_srvCustomer->SetRufprotokoll(static_cast<char>(static_cast<int>(e) + '0'));
}

void ppCustomerCallPlanDay::SetRufSteuerung(const t_calltime eCallTime)
{
    m_srvCustomer->SetRufsteuerung((short)eCallTime);
}

void ppCustomerCallPlanDay::SetRufEinstellung(const ppBool& b)
{
    m_srvCustomer->SetRufeinstellung(b);
}

void ppCustomerCallPlanDay::SetUID(const long l)
{
    ppString s(l);
    m_lUID = l;
    m_srvCustomer->SetTelnr(s);
}

void ppCustomerCallPlanDay::SetAnrufEreignis(const t_cEvents eEvent)
{
    m_srvCustomer->SetUmkstatus((short)eEvent);
}

void ppCustomerCallPlanDay::SetSkdAnrufGenerell(const ppBool& b)
{
    m_srvCustomer->SetSkdanrufgenerell(b);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const long  ppCustomerCallPlanDay::GetKundenNr() const
{
   return m_srvCustomer->GetKundennr();
}

const short ppCustomerCallPlanDay::GetVertriebsZentrumNr() const
{
   return m_srvCustomer->GetVertriebszentrumnr();
}

const long  ppCustomerCallPlanDay::GetIdfNr() const
{
   return m_srvCustomer->GetIdfnr();
}

const char* ppCustomerCallPlanDay::GetNameApo()
{
   return m_srvCustomer->GetNameapo(m_strBuf);
}

const char* ppCustomerCallPlanDay::GetOrt()
{
   return m_srvCustomer->GetOrt(m_strBuf);
}

const char* ppCustomerCallPlanDay::GetTelNr()
{
   return m_srvCustomer->GetTelnr(m_strBuf);
}

const char* ppCustomerCallPlanDay::GetTelKurzWahl()
{
   return m_srvCustomer->GetTelkurzwahl(m_strBuf);
}

const char* ppCustomerCallPlanDay::GetKzKDKlasse()
{
   return m_srvCustomer->GetKzkdklasse(m_strBuf);
}

const long ppCustomerCallPlanDay::GetDatum() const
{
    return m_srvCustomer->GetDatum();
}

const ppTime& ppCustomerCallPlanDay::GetUrRufzeit()
{
    m_TimeBuf.SetTime(m_srvCustomer->GetUrrufzeit());
    return m_TimeBuf;
}

const ppTime& ppCustomerCallPlanDay::GetRufzeit()
{
    m_TimeBuf.SetTime(m_srvCustomer->GetRufzeit());
    return m_TimeBuf;
}

const short ppCustomerCallPlanDay::GetUmkStatus() const
{
    return m_srvCustomer->GetUmkstatus();
}

const ppCustomerCallPlanDay::t_callstate ppCustomerCallPlanDay::GetAnrufStatus() const
{
    return (t_callstate)m_srvCustomer->GetAnrufstatus();
}

const short ppCustomerCallPlanDay::GetPoolNr() const
{
    return m_srvCustomer->GetPoolnr();
}

const short ppCustomerCallPlanDay::GetAnrufZaehler() const
{
    return m_srvCustomer->GetAnrufzaehler();
}

const short ppCustomerCallPlanDay::GetModemPoolNr() const
{
    return m_srvCustomer->GetModempoolnr();
}

const short ppCustomerCallPlanDay::GetTagNr() const
{
    return m_srvCustomer->GetTagnr() - '0';
}

const char* ppCustomerCallPlanDay::GetTourID()
{
    return m_srvCustomer->GetTourid(m_strBuf);
}

const char* ppCustomerCallPlanDay::GetPreparedTourID()
{
   ppString str(m_srvCustomer->GetTourid(m_strBuf));
   if (str.length() < 6)
       return m_strBuf.c_str();

   m_strBuf = str.substr(4,2) + "/" + str.substr(0, 2) + ":" + str.substr(2, 2);
   return m_strBuf.c_str();
}

const ppBool ppCustomerCallPlanDay::GetSTourDefinitiv() const
{
    return m_srvCustomer->GetStourdefinitiv();
}

const char ppCustomerCallPlanDay::GetAnruftyp() const
{
    return m_srvCustomer->GetAnruftyp();
}

const ppCustomerCallPlanDay::t_callrecord ppCustomerCallPlanDay::GetRufProtokoll() const
{
    return (t_callrecord)(m_srvCustomer->GetRufprotokoll() - '0');
}

const ppCustomerCallPlanDay::t_calltime ppCustomerCallPlanDay::GetRufSteuerung() const
{
    return (t_calltime)m_srvCustomer->GetRufsteuerung();
}

const char ppCustomerCallPlanDay::GetRufEinstellung() const
{
    return m_srvCustomer->GetRufeinstellung();
}

const ppBool ppCustomerCallPlanDay::GetSkdAnrufGenerell() const
{
    return m_srvCustomer->GetSkdanrufgenerell();
}

