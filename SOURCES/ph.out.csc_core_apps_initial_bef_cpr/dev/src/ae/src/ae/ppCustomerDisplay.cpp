//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerDisplay.cpp
   Author: A.Schmidt-Rehschuh
   made  : 03.02.2000

   declaration:
   logical part of customerbase-class, Persistence layer (CallPlan)
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerDisplay.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppCustomerDisplay::ppCustomerDisplay(const ppString& strPath, const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvCustomer   = new CMCUSTOMERDISPLAY;
    m_srvCustomerUP = new CMCUSTOMERDISPLAY;
}

//--- direct initialization --------------------------------------------------//

ppCustomerDisplay::ppCustomerDisplay(const short sSaleCenterNo,
                                     const long lCustomerNo,
                                     const ppString& strPath,
                                     const short sLanguage)
    : ppError(strPath, sLanguage)
{
    m_srvCustomer = new CMCUSTOMERDISPLAY;
    m_srvCustomerUP = new CMCUSTOMERDISPLAY;
    m_srvCustomer->SetVertriebszentrumnr(sSaleCenterNo);
    m_srvCustomer->SetKundennr(lCustomerNo);
    GetUni();
}

//--- deconstructor ----------------------------------------------------------//

ppCustomerDisplay::~ppCustomerDisplay()
{
    if (m_srvCustomer)
        delete m_srvCustomer;
    if (m_srvCustomerUP)
        delete m_srvCustomerUP;
}

//----------------------------------------------------------------------------//
//--- direct access to data --------------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetCustomer (unique select) --------------------------------------------//

bool ppCustomerDisplay::GetUni()
{
    SetErrorState(ppError::is_ok);
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
        return true;

    m_srvCustomer->SelCustomer();
    m_srvCustomerUP->SetKundennr(-1);
    if (m_srvCustomer->rc == IS_OK)
    {
        m_srvCustomerUP->SetStruct(m_srvCustomer->GetStruct());
        return true;
    }
    else if (m_srvCustomer->rc == IS_NOTFOUND)
    {
        SetErrorState(ppError::is_notfound);
    }
    return false;
}

//--- Update (update selected row) --------------------------------------------//

bool ppCustomerDisplay::Update()
{
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvCustomer->UpdTelNo() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    SetErrorState(ppError::is_ok);
    return true;
}

//--- Update (update selected row) --------------------------------------------//

bool ppCustomerDisplay::UpdPropetries()
{
    if (!IsInitialized())
    {
        return false;
    }
    else if (m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct())
    {
        SetErrorState(ppError::is_not_modified);  // No fields modified
        return false;
    }

    if (m_srvCustomer->UpdProperties() != IS_OK)
    {
        SetErrorState(ppError::is_sqlerror);
        return false;
    }

    SetErrorState(ppError::is_ok);
    return true;
}

//----------------------------------------------------------------------------//
//--- required fields empty ?-------------------------------------------------//
//----------------------------------------------------------------------------//

bool ppCustomerDisplay::IsInitialized()
{
    if (m_srvCustomer->GetVertriebszentrumnr() == 0 || m_srvCustomer->GetKundennr() == 0)
    {
        SetErrorState(ppError::is_not_initialized);
        return false;
    }
    return true;
}

//--- IsChanged --------------------------------------------------------------//

bool ppCustomerDisplay::IsChanged()
{
    return !(m_srvCustomer->GetStruct() == m_srvCustomerUP->GetStruct());
}

//--- Restore ----------------------------------------------------------------//

void ppCustomerDisplay::Restore()
{
    if (IsChanged())
        m_srvCustomer->SetStruct(m_srvCustomerUP->GetStruct());
}
