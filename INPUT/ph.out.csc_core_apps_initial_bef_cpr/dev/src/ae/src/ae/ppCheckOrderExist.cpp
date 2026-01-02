//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCheckOrderExist.cpp
   Author: R.Imschweiler
   made  : 30.08.2002

   declaration:
   logical part of customerbase-class, Persistence layer (Kunde)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCheckOrderExist.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCheckOrderExist::ppCheckOrderExist(const short sBranchNo,
                                     const ppString& strPath,
                                     const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvCheckOrder = GetSrv();
    m_srvCheckOrderUP = GetSrvUP();
    m_sBranchNo = sBranchNo;
}

//--- copy constructor -------------------------------------------------------//

ppCheckOrderExist::ppCheckOrderExist(const ppCheckOrderExist& right)
    : ppError(right.GetPath(), right.GetLanguage())
{
    m_srvCheckOrder = GetSrv();
    m_srvCheckOrderUP = GetSrvUP();
    m_sBranchNo = right.m_sBranchNo;
}

//--- deconstructor ----------------------------------------------------------//

ppCheckOrderExist::~ppCheckOrderExist()
{
    if (m_srvCheckOrder != NULL)
    {
        delete m_srvCheckOrder;
    }
    if (m_srvCheckOrderUP != NULL)
    {
        delete m_srvCheckOrderUP;
    }
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetUni (unique select) -------------------------------------------------//

long ppCheckOrderExist::GetOrder(short sVzNr, long lKundenNr, short sZeitdiff, short sAnz)
{
   m_srvCheckOrder->SetVertriebszentrumnr(sVzNr);
   m_srvCheckOrder->SetKundennr(lKundenNr);
   m_srvCheckOrder->SetTm_time(sZeitdiff);
   m_srvCheckOrder->SetKdauftragnr(sAnz);
   m_srvCheckOrder->SelAuftrag();
   if (m_srvCheckOrder->rc == IS_NOTFOUND)
   {
      SetErrorState(ppError::is_notfound);
   }
   return m_srvCheckOrder->GetKdauftragnr();
}
