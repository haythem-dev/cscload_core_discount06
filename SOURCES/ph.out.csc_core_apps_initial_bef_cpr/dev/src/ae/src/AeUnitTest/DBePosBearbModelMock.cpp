#include "stdafx.h"
#include "DBePosBearbModelMock.h"
#include <algorithm>
#include <resource.h>

void CDBePosBearbModelMock::ReadArticle(long lArticleNo, ARTAESEL& article)
{
    memcpy_s(&article, sizeof(ARTAESEL), &m_Article, sizeof(ARTAESEL));
}

bool CDBePosBearbModelMock::ReadImportArticle(long lArticleNo)
{
    return m_bImportArticle;
}

void CDBePosBearbModelMock::ReadOpenOrders(long lArticleNo, CStringArray& openOrders)
{
    openOrders.Copy(m_astrOpenOrders);
}

int CDBePosBearbModelMock::ReadIbtPossible(long lArticleNo, short sIbtBranchNo, std::vector<AUFALTLAGORT>& ibtData)
{
    std::copy(m_IbtData.begin(), m_IbtData.end(), ibtData.begin());
    return m_bIbtPossible;
}

bool CDBePosBearbModelMock::ReadDispoInfo(long lArticleNo, CString& cInfo)
{
    cInfo = m_strDispoInfo;
    return m_bDispoInfo;
}

bool CDBePosBearbModelMock::IsNachlieferung(const CString& cAArt)
{
    return m_bNachlieferung;
}

bool CDBePosBearbModelMock::IsDE()
{
    return m_bDE;
}

bool CDBePosBearbModelMock::IsDEGetter()
{
    return m_bDEGetter;
}

char CDBePosBearbModelMock::GetKndNLTyp()
{
    return m_cKndNLTyp;
}

bool CDBePosBearbModelMock::IsNLevelIBTCst()
{
    return m_bNLevelIBTCst;
}

CString CDBePosBearbModelMock::GetBranchName(short branchNo)
{
    return m_strBranchName;
}

CString CDBePosBearbModelMock::GetTextFromResource(UINT uiStringId)
{
    switch (uiStringId)
    {
    case AETXT_GUEG1:
        return "GUEG1";
    case AETXT_GUEG2:
        return "GUEG2";
    default:
        return "";
    }
}

CString CDBePosBearbModelMock::GetDDMMYYYYStringFromDateLong(long lDate)
{
    return "";
}