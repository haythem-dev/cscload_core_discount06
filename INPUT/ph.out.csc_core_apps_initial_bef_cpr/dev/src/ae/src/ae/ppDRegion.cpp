
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDRegion.cpp
   Author: A.Schmidt-Rehschuh
   made  : 21.07.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppRegion.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppRegion::SetRegionNr(const short sSaleCenterNo)
{
   m_srvRegion->SetRegionnr(sSaleCenterNo);
}

void ppRegion::SetRegionTeilNr(const short s)
{
   m_srvRegion->SetRegionteilnr(s);
}

void ppRegion::SetRegionenTyp(const t_region eRegion)
{
    m_srvRegion->SetRegionentyp((short)eRegion);
}

void ppRegion::SetLoginID(const long l)
{
   m_srvRegion->SetLoginid(l);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppRegion::GetRegionNr() const
{
   return static_cast<short>( m_srvRegion->GetRegionnr() );
}

const short ppRegion::GetRegionTeilNr() const
{
   return static_cast<short>( m_srvRegion->GetRegionteilnr() );
}

const ppRegion::t_region ppRegion::GetRegionenTyp() const
{
    return (t_region)m_srvRegion->GetRegionentyp();
}

const ppDate ppRegion::GetDate() const
{
   return m_srvRegion->GetTm_date();
}

const ppTime ppRegion::GetTime() const
{
   return m_srvRegion->GetTm_time();
}

const long ppRegion::GetLoginID() const
{
   return m_srvRegion->GetLoginid();
}

const char* ppRegion::GetName()
{
    return m_srvRegion->GetName(m_str);
}




