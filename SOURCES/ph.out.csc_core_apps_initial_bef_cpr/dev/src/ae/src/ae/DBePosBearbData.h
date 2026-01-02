#pragma once

#include <vector>
#include <map>

struct CDBePosBearbData
{
    CString m_strArtNr;
    CString m_strAArt;
    CString m_strBestand;
    CString m_strBestMenge;
    CString m_strBestMengeNatra;
    BOOL    m_bVerbund;
    int     m_nPosVB;

    short m_sVerbFiliale;
    long  m_lPosState;          // Positionsstatus
    long  m_lMengeVerbund;
    long  m_lBestMenge;         // Bestellmenge

    // Setter
    bool  m_bKndMussKopfBem;    // Auftragskopfbemerkung erzwingen
    bool  m_bIgnoreNoWafo;      // Ignorieren Wafotyp
    long  m_lVerbMenge;

    bool m_bIsNLevelIBTCst;
    std::vector< std::map<int, CString> > m_List1;
    bool m_bStockTooLowAlert;
    int  m_nCbxVerbundPos;

    CStringArray m_ListOpenOrders;

    bool m_bEnableBtnNachlieferung;
    bool m_bEnableBtnDispo;
    bool m_bEnableBtnZugesagt;
    bool m_bEnableStcVerb1;
    bool m_bEnableCbxVerbFiliale;

    bool m_bShowListOffBest;
    bool m_bShowNatra;

    CString m_strAH;
    CString m_strLiefMenge;

    UINT m_uiDefID;
    UINT m_uiFocusId;

    CDBePosBearbData()
    {
        m_bVerbund = FALSE;
        m_nPosVB = 0;
        m_sVerbFiliale = 0;
        m_lMengeVerbund = 0L;
        m_lBestMenge = 0L;

        // Setter
        m_bKndMussKopfBem = false; //Auftragskopfbemerkung nicht erzwingen
        m_bIgnoreNoWafo = false;
        m_lVerbMenge = 0L;

        m_bIsNLevelIBTCst = false;
        m_bStockTooLowAlert = false;
        m_nCbxVerbundPos = 0;

        m_bEnableBtnNachlieferung = true;
        m_bEnableBtnDispo = true;
        m_bEnableBtnZugesagt = true;
        m_bEnableStcVerb1 = false;
        m_bEnableCbxVerbFiliale = false;

        m_bShowListOffBest = true;
        m_bShowNatra = false;
    }
};
