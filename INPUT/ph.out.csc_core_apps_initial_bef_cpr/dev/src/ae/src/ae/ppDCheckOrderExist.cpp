
//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCheckOrderExist.h
   Author: R.Imschweiler
   made  : 30.08.2002
                            >No changes in this text may be made<
   declaration:

*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCheckOrderExist.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//


void ppCheckOrderExist::SetKdauftragnr(const long kdauftragnr)
{
    m_srvCheckOrder->SetKdauftragnr(kdauftragnr);
}

void ppCheckOrderExist::SetKundennr(const long kundennr)
{
    m_srvCheckOrder->SetKundennr(kundennr);
}

void ppCheckOrderExist::SetVertriebszentrumnr(const short vertriebszentrumnr)
{
   m_srvCheckOrder->SetVertriebszentrumnr(vertriebszentrumnr);
}

void ppCheckOrderExist::SetTm_time(const long time)
{
    m_srvCheckOrder->SetTm_time(time);
}


//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

const long  ppCheckOrderExist::GetKundennr() const
{
   return m_srvCheckOrder->GetKundennr();
}

const short ppCheckOrderExist::GetVertriebszentrumnr() const
{
   return m_srvCheckOrder->GetVertriebszentrumnr();
}

const long  ppCheckOrderExist::GetKdauftragnr() const
{
   return m_srvCheckOrder->GetKdauftragnr();
}

const long ppCheckOrderExist::GetTm_time() const
{
   return m_srvCheckOrder->GetTm_time();
}

