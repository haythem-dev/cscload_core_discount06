
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerCallPlan.cpp
   Author: A.Schmidt-Rehschuh
   made  : 29.02.2000

   declaration:
   only set and get-methodes for customeradress-class
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//
#include "pp_pch.h"
#include "ppCustomerCallPlan.h"

//----------------------------------------------------------------------------//
//--- Data-Set-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

void ppCustomerCallPlan::SetOldTime(const long lOldTime)
{
    m_bIsTimeChange = lOldTime > 0 ? true : false;
    m_srvCustomer->SetFetch_rel(lOldTime);
}

void ppCustomerCallPlan::SetUrRufzeit(const long lUrRufzeit)
{
    m_srvCustomer->SetUrrufzeit(lUrRufzeit);
}

void ppCustomerCallPlan::SetRufProtokoll(const t_callrecord rufProtokoll)
{
    m_srvCustomer->SetRufprotokoll(static_cast<char>(static_cast<int>(rufProtokoll) + '0'));
}

void ppCustomerCallPlan::SetRufProtokoll(const ppString& rufProtokoll)
{
    char ch = r_datatransfer_serial + '0';
    for (int i = 0; i < r_end_of_list; i++)
    {
        if (rufProtokoll == m_szaCallRecord[i])
        {
            ch = static_cast<char>(i + '0');
            break;
        }
    }
    m_srvCustomer->SetRufprotokoll(ch);
}

void ppCustomerCallPlan::SetRufSteuerung(const t_calltime eCallTime)
{
    m_srvCustomer->SetRufsteuerung((short)eCallTime);
}

void ppCustomerCallPlan::SetPoolNr(const short sPoolNr)
{
    m_srvCustomer->SetPoolnr(sPoolNr);
}

void ppCustomerCallPlan::SetModemPoolNr(const short sModemPoolNr)
{
    m_srvCustomer->SetModempoolnr(sModemPoolNr);
}

void ppCustomerCallPlan::SetRufEinstellung(const ppBool& bRufEinstellung)
{
    m_srvCustomer->SetRufeinstellung(bRufEinstellung);
}

void ppCustomerCallPlan::SetDoNotCall(const ppBool& bDoNotCall)
{
    if (bDoNotCall)
        m_srvCustomer->SetAnruftyp(t_is_notcall + '0');
}

void ppCustomerCallPlan::SetSpecialCall(const ppBool& bSpecialCall)
{
    if (bSpecialCall)
        m_srvCustomer->SetAnruftyp(t_is_special + '0');
}

void ppCustomerCallPlan::SetNormalCall(const ppBool& bNormalCall)
{
    if (bNormalCall)
        m_srvCustomer->SetAnruftyp(t_is_normal + '0');
}

void ppCustomerCallPlan::SetCallDisabled(const ppBool& bCallDisabled)
{
    if (bCallDisabled)
    {
        const int iTyp = m_srvCustomer->GetAnruftyp() - '0';
        if (iTyp < t_is_disabled)
        {
            m_srvCustomer->SetAnruftyp(static_cast<char>((iTyp + t_is_disabled) + '0'));
        }
    }
    else
    {
        const int iTyp = m_srvCustomer->GetAnruftyp() - '0';
        if (iTyp >= t_is_disabled)
        {
            m_srvCustomer->SetAnruftyp(static_cast<char>((iTyp - t_is_disabled) + '0'));
        }
    }
}

void ppCustomerCallPlan::SetCallDisabledAll()
{
    m_srvCustomer->SetAnruftyp(t_is_disabled + '0');
}

void ppCustomerCallPlan::SetAllCallsAreDisabled(const bool bAllCallsAreDisabled)
{
    m_bAllCallsAreDisabled = bAllCallsAreDisabled;
}

void ppCustomerCallPlan::SetLoginID(const long loginID)
{
    m_srvCustomer->SetLoginid(loginID);
}

void ppCustomerCallPlan::SetTourID(const ppString& tourID)
{
    m_srvCustomer->SetTourid(tourID);
}

void ppCustomerCallPlan::SetSkdAnrufGenerell(const ppBool& bSkdanrufgenerell)
{
    m_srvCustomer->SetSkdanrufgenerell(bSkdanrufgenerell);
}

void ppCustomerCallPlan::SetBemerkung(const ppString& bemerkung)
{
    m_srvCustomer->SetBemerkung(bemerkung);
}

//----------------------------------------------------------------------------//
//--- Data-Get-Methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//
const ppCustomerDisplay* ppCustomerCallPlan::GetCustomer() const
{
    return m_pCustomer;
}

const long  ppCustomerCallPlan::GetKundenNr() const
{
    return m_srvCustomer->GetKundennr();
}

const short ppCustomerCallPlan::GetVertriebsZentrumNr() const
{
    return m_srvCustomer->GetVertriebszentrumnr();
}

const long ppCustomerCallPlan::GetUrRufzeit() const
{
    return m_srvCustomer->GetUrrufzeit();
}

const char* ppCustomerCallPlan::GetRufProtokollText() const
{
    return m_szaCallRecord[m_srvCustomer->GetRufprotokoll() - '0'];
}

const ppCustomerCallPlan::t_callrecord ppCustomerCallPlan::GetRufProtokoll() const
{
    return (t_callrecord)(m_srvCustomer->GetRufprotokoll() - '0');
}

const ppCustomerCallPlan::t_calltime ppCustomerCallPlan::GetRufSteuerung() const
{
    return (t_calltime)m_srvCustomer->GetRufsteuerung();
}

const short ppCustomerCallPlan::GetPoolNr() const
{
    return m_srvCustomer->GetPoolnr();
}

const short ppCustomerCallPlan::GetModemPoolNr() const
{
    return m_srvCustomer->GetModempoolnr();
}

const ppBool ppCustomerCallPlan::GetRufEinstellung() const
{
    return m_srvCustomer->GetRufeinstellung();
}

const bool ppCustomerCallPlan::GetDoNotCall() const
{
    return m_srvCustomer->GetAnruftyp() == t_is_notcall + '0' ? true : false;
}

const bool ppCustomerCallPlan::GetSpecialCall() const
{
    return m_srvCustomer->GetAnruftyp() == t_is_special + '0' ? true : false;
}

const bool ppCustomerCallPlan::GetNormalCall() const
{
    return m_srvCustomer->GetAnruftyp() == t_is_normal + '0' ? true : false;
}

const ppBool ppCustomerCallPlan::GetCallDisabled() const
{
    return m_srvCustomer->GetAnruftyp() - '0' >= t_is_disabled ? true : false;
}

const char* ppCustomerCallPlan::GetAnrufTyp() const
{
    if (m_srvCustomer->GetAnruftyp() - '0' < t_is_disabled)
        return m_szaCallType[m_srvCustomer->GetAnruftyp() - '0'];
    else
        return m_szaCallType[t_is_disabled];
}

const long ppCustomerCallPlan::GetLoginID() const
{
    return m_srvCustomer->GetLoginid();
}

const short ppCustomerCallPlan::GetTagNr() const
{
    return m_srvCustomer->GetTagnr() - '0';
}

const char* ppCustomerCallPlan::GetTourID()
{
    return m_srvCustomer->GetTourid(m_str);
}

const ppBool ppCustomerCallPlan::GetSkdAnrufGenerell() const
{
    return m_srvCustomer->GetSkdanrufgenerell();
}

const char* ppCustomerCallPlan::GetBemerkung()
{
    return m_srvCustomer->GetBemerkung(m_str);
}

const bool ppCustomerCallPlan::IsAllCallsAreDisabled() const
{
    return m_bAllCallsAreDisabled;
}
