#pragma once

#include <auftrag.h>
#include <artsel.h>
#include <DBePosBearbModelIF.h>

class CDBePosBearbModelMock : public CDBePosBearbModelIF
{
public:
    CDBePosBearbModelMock()
    {
        m_bImportArticle = false;
        m_bIbtPossible = false;
        m_bDispoInfo = false;
        m_bNachlieferung = true;
        m_bDE = false;
        m_bDEGetter = false;
        m_cKndNLTyp = 0;
        m_bNLevelIBTCst = false;

        m_Article.ETARTSCHALTER5 = 0x0001;
        m_Article.ARTIKELAKTIV[0] = '1';
        m_Article.ARTIKEL_GESPERRT[0] = '0';
    }

    virtual void ReadArticle(long lArticleNo, ARTAESEL& article);
    virtual bool ReadImportArticle(long lArticleNo);
    virtual void ReadOpenOrders(long lArticleNo, CStringArray& openOrders);
    virtual int ReadIbtPossible(long lArticleNo, short sIbtBranchNo, std::vector<AUFALTLAGORT>& ibtData);
    virtual bool ReadDispoInfo(long lArticleNo, CString& cInfo);
    virtual bool IsNachlieferung(const CString& cAArt);
    virtual bool IsDE();
    virtual bool IsDEGetter();
    virtual char GetKndNLTyp();
    virtual bool IsNLevelIBTCst();
    virtual CString GetBranchName(short branchNo);
    virtual CString GetTextFromResource(UINT uiStringId);
    virtual CString GetDDMMYYYYStringFromDateLong(long lDate);

    ARTAESEL m_Article;
    bool m_bImportArticle;
    CStringArray m_astrOpenOrders;
    std::vector<AUFALTLAGORT> m_IbtData;
    bool m_bIbtPossible;
    CString m_strDispoInfo;
    bool m_bDispoInfo;
    bool m_bNachlieferung;
    bool m_bDE;
    bool m_bDEGetter;
    char m_cKndNLTyp;
    bool m_bNLevelIBTCst;
    CString m_strBranchName;
};

