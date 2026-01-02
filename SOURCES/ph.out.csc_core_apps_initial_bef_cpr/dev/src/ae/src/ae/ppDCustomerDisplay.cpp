
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCustomerAdress.cpp
   Author: K.Hinz
   made  : 29.02.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerDisplay.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCustomerDisplay::SetVertriebsZentrumNr(const short sSaleCenterNo) /* part of unique key */
{
    m_srvCustomer->SetVertriebszentrumnr(sSaleCenterNo);
}

void ppCustomerDisplay::SetKundenNr(long t)
{
    m_srvCustomer->SetKundennr(t);
}

void ppCustomerDisplay::SetTelnr(const ppString& s)
{
    m_srvCustomer->SetTelnr(s);
}

void ppCustomerDisplay::SetTelnrDafue(const ppString& s)
{
    m_srvCustomer->SetTelnrdafue(s);
}

void ppCustomerDisplay::SetTelKurzwahl(const ppString& s)
{
    m_srvCustomer->SetTelkurzwahl(s);
}

void ppCustomerDisplay::SetSkdAnrufGenerell(const ppBool& b)
{
    m_srvCustomer->SetSkdanrufgenerell(b);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const long  ppCustomerDisplay::GetIdfNr() const
{
   return m_srvCustomer->GetIdfnr();
}

const short ppCustomerDisplay::GetVertriebsZentrumNr() const
{
   return m_srvCustomer->GetVertriebszentrumnr();
}

const short ppCustomerDisplay::GetFilialNr() const
{
   return m_srvCustomer->GetFilialnr();
}

const char* ppCustomerDisplay::GetNameApo()
{
   return m_srvCustomer->GetNameapo(m_str);
}

const char* ppCustomerDisplay::GetNameInhaber()
{
   return m_srvCustomer->GetNameinhaber(m_str);
}

const char* ppCustomerDisplay::GetStrasse()
{
   return m_srvCustomer->GetStrasse(m_str);
}

const char* ppCustomerDisplay::GetOrt()
{
   return m_srvCustomer->GetOrt(m_str);
}

const char* ppCustomerDisplay::GetPostleitZahl()
{
   return m_srvCustomer->GetPostleitzahl(m_str);
}

const long ppCustomerDisplay::GetKundenNr() const
{
   return m_srvCustomer->GetKundennr();
}

const ppCustomerDisplay::t_adress ppCustomerDisplay::GetAnredeKz() const
{
   return (t_adress)m_srvCustomer->GetAnredekz();
}

const char* ppCustomerDisplay::GetTelnr()
{
    return m_srvCustomer->GetTelnr(m_str);
}

const char* ppCustomerDisplay::GetTelnrDafue()
{
    return m_srvCustomer->GetTelnrdafue(m_str);
}

const char* ppCustomerDisplay::GetTelKurzwahl()
{
    return m_srvCustomer->GetTelkurzwahl(m_str);
}

const ppBool ppCustomerDisplay::GetSkdKundeAeGesperrt() const
{
    return m_srvCustomer->GetSkdkundeaegesperrt();
}

const ppBool ppCustomerDisplay::GetSkdAnrufGenerell() const
{
    return m_srvCustomer->GetSkdanrufgenerell();
}




