
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDCustomerAdress.cpp
   Author: R.von-der-Gruen
   made  : 07.07.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCallPlanLoad.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCallPlanLoad::SetVertriebsZentrumNr(const short sSaleCenterNo) /* part of unique key */
{
    m_srvCallPlanLoad->SetVertriebszentrumnr(sSaleCenterNo);
}

void ppCallPlanLoad::SetDatum(const ppDate& l)
{
    m_srvCallPlanLoad->SetDatum(l);
}

void ppCallPlanLoad::SetWochentag(const short s)
{
    ppString str((long)s);
    m_srvCallPlanLoad->SetWochentag(str);
}

void ppCallPlanLoad::SetLadeDatum(const ppDate& l)
{
    m_srvCallPlanLoad->SetLadedatum(l);
}

void ppCallPlanLoad::SetLadeVZ(const short s)
{
    m_srvCallPlanLoad->SetLadevz(s);
}

void ppCallPlanLoad::SetBundesland(const ppString& str)
{
    m_srvCallPlanLoad->SetBundesland(str);
}

void ppCallPlanLoad::SetTourID(const ppString& str)
{
    m_srvCallPlanLoad->SetTourid(str);
}

void ppCallPlanLoad::SetLadeZeitAb(const ppTime t)
{
    m_srvCallPlanLoad->SetLadezeitab(t);
}

void ppCallPlanLoad::SetLadeZeitBis(const ppTime t)
{
    m_srvCallPlanLoad->SetLadezeitbis(t);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppCallPlanLoad::GetVertriebsZentrumNr() const
{
   return m_srvCallPlanLoad->GetVertriebszentrumnr();
}

const ppDate ppCallPlanLoad::GetDatum() const
{
    return m_srvCallPlanLoad->GetDatum();
}

const ppDayType ppCallPlanLoad::GetWochenTag()
{
    return (ppDayType::t_day)atoi(m_srvCallPlanLoad->GetWochentag(m_str));
}

const ppDate ppCallPlanLoad::GetLadeDatum() const
{
    return m_srvCallPlanLoad->GetLadedatum();
}

const short ppCallPlanLoad::GetLadeVZ()
{
    return m_srvCallPlanLoad->GetLadevz();
}

const char* ppCallPlanLoad::GetBundesLand()
{
   return m_srvCallPlanLoad->GetBundesland(m_str);
}

const char* ppCallPlanLoad::GetTourID()
{
   return m_srvCallPlanLoad->GetTourid(m_str);
}

const ppTime ppCallPlanLoad::GetLadeZeitAb() const
{
    return m_srvCallPlanLoad->GetLadezeitab();
}

const ppTime ppCallPlanLoad::GetLadeZeitBis() const
{
    return m_srvCallPlanLoad->GetLadezeitbis();
}

const bool ppCallPlanLoad::IsAvailable() const
{
    return m_bIsAvailable;
}

