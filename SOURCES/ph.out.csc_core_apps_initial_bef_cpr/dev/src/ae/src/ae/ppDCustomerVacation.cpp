
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCustomerVacation.cpp
   Author: R.Imschweiler
   made  : 14.05.2001

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include <customer.h>
#include "ppCustomerVacation.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCustomerVacation::SetVertriebsZentrumNr(const short s)
{
    m_srvVacation->SetVertriebszentrumnr(s);
}

void ppCustomerVacation::SetKundennr(const long s)
{
    m_srvVacation->SetKundennr(s);
}

void ppCustomerVacation::SetDatumgueltigab(const long s)
{
    m_srvVacation->SetDatumgueltigab(s);
}

void ppCustomerVacation::SetDatumgueltigbis(const long s)
{
    m_srvVacation->SetDatumgueltigbis(s);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCustomerVacation::GetVertriebsZentrumNr() const
{
    return m_srvVacation->GetVertriebszentrumnr();
}

const long ppCustomerVacation::GetKundennr() const
{
    return m_srvVacation->GetKundennr();
}

const long ppCustomerVacation::GetDatumgueltigab() const
{
    return m_srvVacation->GetDatumgueltigab();
}

const long ppCustomerVacation::GetDatumgueltigbis() const
{
    return m_srvVacation->GetDatumgueltigbis();
}

//----------------------------------------------------------------------------//
//--- Data-Get-Length-Methodes -----------------------------------------------//
//----------------------------------------------------------------------------//
/*  Beispiel
const ppFieldLength ppCustomerVacation::LengthVertriebsZentrumNr() const
{
   return L_MCALLPARAMATER_VERTRIEBSZENTRUMNR;
}
*/
