
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppRegion.cpp
   Author: A.Schmidt-Rehschuh
   made  : 21.07.2000

   declaration:
   logical part of callplanDeviceOverview-class, Persistence layer (modemanrufplan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "pp_pch.h"
#include "ppRegion.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppRegion::ppRegion(const ppString& strPath,
                   const short sLanguage)
: ppError(strPath, sLanguage)
{
    m_srvRegion   = GetSrv();
    m_srvRegionUP = GetSrvUP();
    SetClassName("ppRegion");
}

//--- direct initialization --------------------------------------------------//

ppRegion::ppRegion(const short sRegionNo,
                   const t_region eRegion,
                   const ppString& strPath,
                   const short sLanguage)
: ppError(strPath, sLanguage)
{
    m_srvRegion   = GetSrv();
    m_srvRegionUP = GetSrvUP();
    SetRegionNr(sRegionNo);
    SetRegionenTyp(eRegion);
    SetClassName("ppRegion");
}

//--- deconstructor ----------------------------------------------------------//

ppRegion::~ppRegion()
{
    if (m_srvRegion)
        delete m_srvRegion;
    if (m_srvRegionUP)
        delete m_srvRegionUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- Insert (insert row) ----------------------------------------------------//

bool ppRegion::Insert()
{
    SetFunctionName("Insert");
    if (!IsInitialized())
        return false;

    int rc = m_srvRegion->Insert();
    if (rc != IS_OK)
    {
        m_srvRegion->ClearStruct();
        m_srvRegionUP->ClearStruct();
        switch (rc)
        {
        case IS_NOTFOUND:
            SetErrorState(ppError::is_notfound);
            break;
        case IS_LOCKED:
            SetErrorState(ppError::is_locked);
            break;
        case IS_EXISTS:
            SetErrorState(ppError::is_exist);
            break;
        default:
            SetErrorState(ppError::is_sqlerror);
            break;
        }
        return false;
    }
    else if (!InsList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvRegionUP->SetStruct(m_srvRegion->GetStruct());
    SetErrorState(ppError::is_ok);
    return true;
}

//--- DeleteCustomer (delete selected row) -----------------------------------//

bool ppRegion::Delete()
{
    SetFunctionName("Delete");
    if (!IsInitialized())
    {
        return false;
    }

    if (m_srvRegion->DelRegion() != 0)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }
    else if (!DelList())
    {
        SetErrorState(ppError::is_out_of_memory);
        return false;
    }

    m_srvRegion->ClearStruct();
    m_srvRegionUP->ClearStruct();
    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- StartBrowse ------------------------------------------------------------//

bool ppRegion::StartBrowse()
{
    return ppDadeScroll<CMREGION>::StartBrowse();
}

//--- SetNextPage ------------------------------------------------------------//

bool ppRegion::SetNextPage()
{
    return ppDadeScroll<CMREGION>::SetNextPage();
}

//--- SetPreviousPage --------------------------------------------------------//

bool ppRegion::SetPreviousPage()
{
    return ppDadeScroll<CMREGION>::SetPreviousPage();
}

//--- GetNext ----------------------------------------------------------------//

bool ppRegion::GetNext()
{
    SetFunctionName("GetNext");

    bool bReturn = ppDadeScroll<CMREGION>::GetNext();

    if (!bReturn)
    {
       SetErrorState(is_notfound);
    }
    return bReturn;
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

bool ppRegion::SetElement(const unsigned nPos)
{
    SetFunctionName("SetElement");
    return ppDadeScroll<CMREGION>::SetElement(nPos);
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppRegion::IsInitialized()
{
    if (GetRegionNr() == 0)
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
    }
    return true;
}
