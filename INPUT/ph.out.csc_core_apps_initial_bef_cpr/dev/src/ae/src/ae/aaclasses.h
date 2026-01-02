#pragma once

#include "aeorderstat.h"
#include <param.h>

class COrdStat
{
private:
    char Status[16];
public:
    COrdStat();
    COrdStat(const char* a);
    void SetOrdStat(const char* a);
    void GetOrdStatCStr(CString& CStatus);
};

class CKombiAKBArt
{
private:
    CPARKABAKOMB m_cparaPara;
    int          m_iNumber;
    CObList      m_cplList;

public:
    CKombiAKBArt();
    ~CKombiAKBArt();

    int InitData(short sVZ);
    int GetData(short sVZ);
    void RemoveData();
    void GetStandardOrderKomb(const CString csKindOfOrder,
                              CString &csKindOfCommision,
                              CString &csKindOfBooking,
                              CString &csTourId,
                              short sVZ);
};

class CKombiArt:public CObject
{
    //DECLARE_SERIAL(CKombiArt)
private:
    CString m_csKindOfOrder;
    CString m_csKindOfCommision;
    CString m_csKindOfBooking;
    int     m_iStandard;
    CString m_csTourId;
    short   m_sVZ;

public:
    CKombiArt();
    CKombiArt(CString csOrd, CString csComm, CString csBook, int iStand, CString m_csTourId, short sVZ);
    CKombiArt(const CKombiArt& cpy);

    CString GetKindOfOrder() { return m_csKindOfOrder; }
    CString GetKindOfCommision() { return m_csKindOfCommision; }
    CString GetKindOfBooking() { return m_csKindOfBooking; }
    int     GetStandard() { return m_iStandard; }
    CString GetTourId() { return m_csTourId; }
    short   GetVZ() { return m_sVZ; }

    const CKombiArt& operator=(const CKombiArt& list)
    {
          m_csKindOfOrder     = list.m_csKindOfOrder;
          m_csKindOfCommision = list.m_csKindOfCommision;
          m_csKindOfBooking   = list.m_csKindOfBooking;
          m_iStandard         = list.m_iStandard;
          m_csTourId          = list.m_csTourId;
          m_sVZ               = list.m_sVZ;
          return *this;
    }

    BOOL operator==(CKombiArt& list)
    {
          return m_csKindOfOrder     == list.m_csKindOfOrder &&
                 m_csKindOfCommision == list.m_csKindOfCommision &&
                 m_csKindOfBooking   == list.m_csKindOfBooking &&
                 m_iStandard         == list.m_iStandard ? TRUE : FALSE &&
                 m_csTourId          == list.m_csTourId &&
                 m_sVZ               == list.m_sVZ;
    }
};
