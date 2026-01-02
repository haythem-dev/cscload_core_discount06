
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppSaleCenter.cpp
   Author: A.Schmidt-Rehschuh
   made  : 29.08.2000

   declaration:
   logical part of callplanDeviceOverview-class, Persistence layer (modemanrufplan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "pp_pch.h"
#include "ppSaleCenter.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppSaleCenter::ppSaleCenter(const ppString& strPath,
                           const short sLanguage)
: ppError(strPath, sLanguage)
{
    m_srvSaleCenter   = GetSrv();
    m_srvSaleCenterUP = GetSrvUP();
}

//--- deconstructor ----------------------------------------------------------//

ppSaleCenter::~ppSaleCenter()
{
    if (m_srvSaleCenter)
        delete m_srvSaleCenter;
    if (m_srvSaleCenterUP)
        delete m_srvSaleCenterUP;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppSaleCenter::StartBrowse()
{
    return ppDadeScroll<CMSALECENTER>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppSaleCenter::SetNextPage()
{
    return ppDadeScroll<CMSALECENTER>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppSaleCenter::SetPreviousPage()
{
    return ppDadeScroll<CMSALECENTER>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppSaleCenter::GetNext()
{
    return ppDadeScroll<CMSALECENTER>::GetNext();
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppSaleCenter::SetElement(const unsigned nPos)
{
    return ppDadeScroll<CMSALECENTER>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- get methodes -----------------------------------------------------------//
//----------------------------------------------------------------------------//

const short ppSaleCenter::GetFilialNr() const
{
    return m_srvSaleCenter->GetFilialnr();
}

const char* ppSaleCenter::GetName()
{
    return m_srvSaleCenter->GetName(m_str);
}
