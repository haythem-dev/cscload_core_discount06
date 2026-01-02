// aaclasses.cpp :  implementation file
//
#include "stdafx.h"
#include "aaclasses.h"

COrdStat::COrdStat()
{
    for (int i = 0; i < 16; i++)
        Status[i] = '0';
}

COrdStat::COrdStat(const char *a)
{
    for (int i = 0; i < 16; i++)
        Status[i] = a[i];
}

void COrdStat::SetOrdStat(const char *a)
{
    for (int i = 0; i < 16; i++)
        Status[i] = a[i];
}

void COrdStat::GetOrdStatCStr(CString &CStatus)
{
        //Reihenfolge ist wichtig
        if      (Status[AEORD_POS_STORNIERT]        == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_STORNO);
        else if (Status[AEORD_POS_FAKTUR_ENDE]      == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_FAKTURENDE);
        else if (Status[AEORD_POS_BEREIT_ZUR_FAKTUR]== '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_BERFAKTUR);
        else if (Status[AEORD_POS_KOMMI_ENDE]       == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_KOMMIENDE);
        else if (Status[AEORD_POS_IN_KOMMI]         == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_INKOMMI);
        else if (Status[AEORD_POS_ERFASST]          == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_ERFASST);
        else if (Status[AEORD_POS_IN_AENDERUNG]     == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_INAENDERUNG);
        else if (Status[AEORD_POS_IN_ERFASSUNG]     == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG);
        else if (Status[AEORD_POS_ZURUECKGEST_DAFUE]== '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG);
        else if (Status[AEORD_POS_ZURUECKGESTELLT]  == '1' ) CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG);
        else                                                 CStatus = CResString::ex().getStrTblText(AETXT_ORDSTAT_KEIN);

}

/** CKOMBIART **************************************************************************/

CKombiArt::CKombiArt()
{
    m_csKindOfOrder = (char*)0;
    m_csKindOfCommision = (char*)0;
    m_csKindOfBooking = (char*)0;
    m_iStandard = 0;
    m_csTourId = (char*)0;
    m_sVZ = 0;
}

CKombiArt::CKombiArt(CString csOrd, CString csComm, CString csBook, int iStand, CString csTourId, short sVZ)
{
    m_csKindOfOrder = csOrd;
    m_csKindOfCommision = csComm;
    m_csKindOfBooking = csBook;
    m_iStandard = iStand;
    m_csTourId = csTourId;
    m_sVZ = sVZ;
}

CKombiArt::CKombiArt(const CKombiArt& cpy)
{
    m_csKindOfOrder     = cpy.m_csKindOfOrder;
    m_csKindOfCommision = cpy.m_csKindOfCommision;
    m_csKindOfBooking   = cpy.m_csKindOfBooking;
    m_iStandard         = cpy.m_iStandard;
    m_csTourId          = cpy.m_csTourId;
    m_sVZ               = cpy.m_sVZ;
}

/** CKOMBIAKBART ***********************************************************************/

CKombiAKBArt::CKombiAKBArt() : m_iNumber(0)
{
    m_cparaPara.s.FETCH_REL = 1;                    //normaler Fetch
    strcpy(m_cparaPara.s.KDAUFTRAGART, "  ");
    strcpy(m_cparaPara.s.BUCHART, "0");
    strcpy(m_cparaPara.s.KOART, "0");
    strcpy(m_cparaPara.s.TOURID, " ");
    m_cparaPara.s.VERTRIEBSZENTRUMNR = 0;
}

CKombiAKBArt::~CKombiAKBArt()
{
    POSITION   pos;
    CKombiArt* pKombiArt;

    for (int i = 0; i < m_iNumber && (pos = m_cplList.FindIndex(i)) != NULL; i++)
    {
        pKombiArt = (CKombiArt*)m_cplList.GetAt(pos);
        delete pKombiArt;
    }

    m_cplList.RemoveAll();
}

void CKombiAKBArt::RemoveData()
{
    POSITION   pos;
    CKombiArt* pKombiArt;

    for (int i = 0; i < m_iNumber && (pos = m_cplList.FindIndex(i)) != NULL; i++)
    {
        pKombiArt = (CKombiArt*)m_cplList.GetAt(pos);
        delete pKombiArt;
    }

    m_cplList.RemoveAll();
}

int CKombiAKBArt::InitData(short sVZ)
{
    RemoveData();   // delete old data
    m_iNumber = 0;
    GetData(sVZ);
    return 0;
}

int CKombiAKBArt::GetData(short sVZ)
{
    int found = -1;
    m_cparaPara.s.FETCH_REL = 1;
    m_cparaPara.s.VERTRIEBSZENTRUMNR = sVZ;
    for (;; m_iNumber++) // init new data
    {
        m_cparaPara.Server(AafilSelkabakomb);
        if (m_cparaPara.rc == SRV_SQLNOTFOUND)
        {
            m_cparaPara.s.FETCH_REL = 0;
            m_cparaPara.Server(AafilSelkabakomb);
            break;
        }
        else if (m_cparaPara.rc < SRV_OK)
            return m_cparaPara.rc;

        m_cplList.AddHead(new CKombiArt(
            m_cparaPara.s.KDAUFTRAGART,
            m_cparaPara.s.KOART,
            m_cparaPara.s.BUCHART,
            atoi(m_cparaPara.s.KZSTANDARD),
            m_cparaPara.s.TOURID,
            m_cparaPara.s.VERTRIEBSZENTRUMNR));
        found = 0;
    }

    return found;
}

void CKombiAKBArt::GetStandardOrderKomb(const CString csKindOfOrder, CString& csKindOfCommision, CString& csKindOfBooking,
    CString& csTourId, short sVZ)
{
    POSITION pos;
    CKombiArt* pKombiArt;
    int i;
    int found = 0;

    csKindOfCommision = "0";    // this is the standard
    csKindOfBooking   = "0";    // this is the standard
    csTourId          = " ";    // this is the standard

    for (found = 0; found == 0;)
    {
        for (i = 0; i < m_iNumber && (pos = m_cplList.FindIndex(i)) != NULL; i++)
        {
            pKombiArt = (CKombiArt*)m_cplList.GetAt(pos);

            // zuerst pruefen ob VZ schon geladen ist
            if (pKombiArt->GetVZ() == sVZ)
            {
                found = 1;
                if (pKombiArt->GetKindOfOrder() == csKindOfOrder && pKombiArt->GetStandard() == 1)
                {
                    csKindOfCommision   = pKombiArt->GetKindOfCommision();
                    csKindOfBooking     = pKombiArt->GetKindOfBooking();
                    csTourId            = pKombiArt->GetTourId();
                    break;
                }
            }
        }
        if (!found)
        {
            if (GetData(sVZ) != 0)
            {
                break;
            }
        }
    }
}
