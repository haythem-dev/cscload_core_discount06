#include "stdafx.h"
#include "DBePosBearbPresenter.h"
#include "DBePosBearbData.h"
#include "DBePosBearbModel.h"
#include <artsel.h>
#include <aasrv.h>
#include "IBTListctrlDefines.h"
#include "resource.h"

CDBePosBearbPresenter::CDBePosBearbPresenter(CDBePosBearbData& rBePosBearbData, CDBePosBearbModelIF& rBePosBearbModel)
    : m_Data(rBePosBearbData), m_Model(rBePosBearbModel)
{
}

void CDBePosBearbPresenter::InitDialog()
{
    //Liefermoeglichkeiten ausgeben
    ARTAESEL article;
    m_Model.ReadArticle(atol(m_Data.m_strArtNr), article);

    if (AllgBitleisteN((Bitleiste)article.ETARTSCHALTER1, 3))
    {
        m_Data.m_bEnableBtnNachlieferung = false;
        m_Data.m_bEnableBtnDispo = false;
        m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_AUSSERHANDEL);
    }
    else if (AllgBitleisteN((Bitleiste)article.ETARTKLASSE1, 6))
    {
        m_Data.m_bEnableBtnNachlieferung = false;
        m_Data.m_bEnableBtnDispo = false;
        m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_BTM);
    }
    else if (AllgBitleisteN((Bitleiste)article.ETARTSCHALTER1, 4))
    {
        m_Data.m_bEnableBtnNachlieferung = false;
        m_Data.m_bEnableBtnDispo = true;
        m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_AUSLAUF);
    }
    else if (AllgBitleisteN((Bitleiste)article.ETARTSCHALTER5, 0))
    {
        m_Data.m_bEnableBtnNachlieferung = false;
        m_Data.m_bEnableBtnDispo = true;
        m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_EKS);
    }
    else if (m_Data.m_strAArt == "SV")
    {
        m_Data.m_bEnableBtnDispo = false;
    }
    else if (!m_Model.IsNachlieferung(m_Data.m_strAArt))
    {
        m_Data.m_bEnableBtnNachlieferung = false;
        m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_NO_RESTDEL);
    }
    else
    {
        m_Data.m_bEnableBtnNachlieferung = true;

        // CPR-170910
        if (m_Model.IsDE() && article.WAFOTYP[0] != '1' && !m_Data.m_bIgnoreNoWafo)
        {
            m_Data.m_bEnableBtnNachlieferung = false;
            m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_NO_RESTDEL);
        }

        m_Data.m_strAH = ""; // ???
    }

    if (m_Model.IsDE())
    {
        if (   (m_Model.GetTextFromResource(AETXT_GUEG1) == article.ABDACODE)
            || (m_Model.GetTextFromResource(AETXT_GUEG2) == article.ABDACODE) )
        {
            m_Data.m_bEnableBtnDispo = false;
            CString guegtext;
            guegtext.Format("%s %s", article.ABDACODE, m_Model.GetTextFromResource(AETXT_GUEG_NO_DISPO).GetString());
            m_Data.m_strAH = guegtext;
        }
        if (article.ARTIKELAKTIV[0] == '0' || article.ARTIKEL_GESPERRT[0] == '1')
        {
            m_Data.m_bEnableBtnNachlieferung = false;
            m_Data.m_bEnableBtnZugesagt = false;
            m_Data.m_bEnableBtnDispo = false;
            m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_ARTIKEL_GESPERRT);
        }
        if (AllgBitleisteN((Bitleiste)article.ETARTSCHALTER2, 15))
        {
            m_Data.m_bEnableBtnDispo = false; // bei geführten Artikeln in DE kein Dispo
        }
    }
    if (m_Data.m_bKndMussKopfBem)
    {
        m_Data.m_bEnableBtnNachlieferung = false;
    }
    if (article.IMPORTARTICLE == 1)   //Importartikel
    {
        if (m_Model.IsDEGetter())
        {
            if (m_Model.ReadImportArticle(article.ARTIKEL_NR))
            {
                m_Data.m_bEnableBtnDispo = true;
                m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_IMPORTARTICLE);
            }
            else
            {
                m_Data.m_bEnableBtnDispo = false;
                m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_IMPORTARTICLE_BLOCKED);
            }
        }
        else
        {
            m_Data.m_bEnableBtnDispo = false;
            m_Data.m_strAH = m_Model.GetTextFromResource(AETXT_IMPORTARTICLE);
        }
        m_Data.m_bEnableBtnNachlieferung = false;
        m_Data.m_bEnableBtnZugesagt = false;
    }
    if (!AllgBitleisteN((Bitleiste)article.ETARTSCHALTER2, 15))
    {
        char cKndNLTyp = m_Model.GetKndNLTyp();
        if ((cKndNLTyp <= '1') || (cKndNLTyp >= '7') || (article.WAFOTYP[0] <= '0'))
        {
            m_Data.m_bEnableBtnNachlieferung = false;
        }
        m_Data.m_bShowListOffBest = false;
    }
    else
    {
        CStringArray openOrders;
        m_Model.ReadOpenOrders(atol(m_Data.m_strArtNr), openOrders);
        for (int i = 0; i < openOrders.GetCount(); ++i)
        {
            m_Data.m_ListOpenOrders.Add(openOrders[i]);
        }
    }

    m_Data.m_lMengeVerbund = 0;

    if (m_Data.m_lPosState == ITEM_STAT_DISPO)
    {
        m_Data.m_uiDefID = IDC_BUTTON_DISPO;
        m_Data.m_uiFocusId = IDC_BUTTON_DISPO;
    }
    if (m_Data.m_lPosState == ITEM_STAT_NACHLIEFERN)
    {
        if (m_Data.m_bEnableBtnNachlieferung)
        {
            m_Data.m_uiDefID = IDC_BUTTON_NACH_LF;
            m_Data.m_uiFocusId = IDC_BUTTON_NACH_LF;
        }
        else
        {
            m_Data.m_uiDefID = IDC_BUTTON_DISPO;
            m_Data.m_uiFocusId = IDC_BUTTON_DISPO;
        }
    }
    if (m_Data.m_lPosState == ITEM_STAT_NORMAL)
    {
        m_Data.m_uiDefID = IDOK;
        m_Data.m_uiFocusId = IDOK;
    }
    if (m_Data.m_lPosState == ITEM_STAT_ZUGESAGT)
    {
        m_Data.m_uiDefID = IDC_BUTTON_ZUGESAGT;
        m_Data.m_uiFocusId = IDC_BUTTON_ZUGESAGT;
    }

    m_Data.m_bIsNLevelIBTCst = m_Model.IsNLevelIBTCst();

    m_Data.m_bShowNatra = (atol(m_Data.m_strBestMengeNatra) > 0) ? true : false;
}

void CDBePosBearbPresenter::InitVerbund()
{
    //Verbund moeglich

    std::vector<AUFALTLAGORT> ibtData;
    m_Model.ReadIbtPossible(atol(m_Data.m_strArtNr), m_Data.m_sVerbFiliale, ibtData);

    if (m_Data.m_bIsNLevelIBTCst)
    {
        m_Data.m_nPosVB = 0;   //default
        for (int i = 0; i < (int)ibtData.size(); ++i)
        {
            if (ibtData[i].FILIALNR == m_Data.m_sVerbFiliale)
            {
                m_Data.m_nPosVB = m_Data.m_List1.size();
                m_Data.m_lMengeVerbund = ibtData[i].BESTAND;
            }
            std::map<int, CString> item;
            CString text = m_Model.GetBranchName(ibtData[i].FILIALNR);
            item[COL_IBT_BRANCHNAME] = text;
            text.Format("%d", ibtData[i].FILIALNR);
            item[COL_IBT_FILI] = text;
            text.Format("%d", ibtData[i].BESTAND);
            item[COL_IBT_BESTAND] = text;
            text = ibtData[i].IBTTYPENAME;
            text.Trim();
            item[COL_IBT_TYPE] = text;
            text = m_Model.GetDDMMYYYYStringFromDateLong(ibtData[i].DELIVERYDATEIBT);
            item[COL_IBT_DATUM] = text;
            text.Format("%d:%02d", ibtData[i].DELIVERYTIMEIBT / 100, ibtData[i].DELIVERYTIMEIBT % 100);
            item[COL_IBT_ZEIT] = text;

            m_Data.m_List1.push_back(item);
        }
        m_Data.m_bStockTooLowAlert =
            (!m_Data.m_List1.empty() && (atol(m_Data.m_List1[m_Data.m_nPosVB][COL_IBT_BESTAND]) + atol(m_Data.m_strBestand)) < atol(m_Data.m_strBestMenge))
            ? true : false;
    }
    else
    {
        int pos = 0;

        for (int i = 0; i < (int)ibtData.size(); ++i)
        {
            if (ibtData[i].FILIALNR == m_Data.m_sVerbFiliale)
            {
                pos = m_Data.m_List1.size();
                m_Data.m_lMengeVerbund = ibtData[i].BESTAND;
            }
            std::map<int, CString> item;
            CString cstr;
            cstr.Format("%02d %ld", ibtData[i].FILIALNR, ibtData[i].BESTAND);
            item[0] = cstr;

            m_Data.m_List1.push_back(item);
        }
        if (!m_Data.m_List1.empty())
        {
            m_Data.m_nCbxVerbundPos = pos;
        }
    }

    m_Data.m_sVerbFiliale = 0;   //kein Verbund ??? TODO: Ist das richtig ???
}

void CDBePosBearbPresenter::DeaktVerbund()
{
    m_Data.m_sVerbFiliale = 0;
    m_Data.m_lVerbMenge = 0;
}

void CDBePosBearbPresenter::SetVerbund(bool bVerbund)
{
    if (m_Data.m_bIsNLevelIBTCst)
    {
        if (bVerbund)
        {
            m_Data.m_lMengeVerbund = (short)atol(m_Data.m_List1[m_Data.m_nPosVB][COL_IBT_BESTAND]);
            int liefmeng = atol(m_Data.m_strBestand) + m_Data.m_lMengeVerbund;
            if (liefmeng > m_Data.m_lBestMenge)
            {
                liefmeng = m_Data.m_lBestMenge;
            }
            m_Data.m_lBestMenge = liefmeng;
            CString cstr;
            cstr.Format("%ld", m_Data.m_lBestMenge);
            m_Data.m_strLiefMenge = cstr;
        }
        else
        {
            m_Data.m_lMengeVerbund = 0;
            m_Data.m_strLiefMenge = "";
        }
    }
    else
    {
        if (bVerbund)
        {
            m_Data.m_bEnableStcVerb1 = true;
            m_Data.m_bEnableCbxVerbFiliale = true;
            //m_Data.m_sEdtLiefMenge = ""; -> OnSelchangeComboVerbFiliale();
            //m_Data.m_MengeVerbund -> OnSelchangeComboVerbFiliale();
        }
        else
        {
            m_Data.m_bEnableStcVerb1 = false;
            m_Data.m_bEnableCbxVerbFiliale = false;
            m_Data.m_lMengeVerbund = 0;
            m_Data.m_strLiefMenge = m_Data.m_strBestand;
        }
    }
}
