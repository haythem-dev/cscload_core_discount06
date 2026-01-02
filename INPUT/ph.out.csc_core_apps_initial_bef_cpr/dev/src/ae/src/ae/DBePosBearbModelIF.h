#pragma once

#include <vector>
#include <auftrag.h>

struct ARTAESEL;

class CDBePosBearbModelIF
{
public:
    virtual void ReadArticle(long lArticleNo, ARTAESEL& article) = 0;

    virtual bool ReadImportArticle(long lArticleNo) = 0;

    virtual void ReadOpenOrders(long lArticleNo, CStringArray& openOrders) = 0;

    virtual int ReadIbtPossible(long lArticleNo, short sIbtBranchNo, std::vector<AUFALTLAGORT>& ibtData) = 0;

    virtual bool ReadDispoInfo(long lArticleNo, CString& cInfo) = 0;

    virtual bool IsNachlieferung(const CString& cAArt) = 0;

    virtual bool IsDE() = 0;

    virtual bool IsDEGetter() = 0;

    virtual char GetKndNLTyp() = 0;

    virtual bool IsNLevelIBTCst() = 0;

    virtual CString GetBranchName(short branchNo) = 0;

    virtual CString GetTextFromResource(UINT uiStringId) = 0;

    virtual CString GetDDMMYYYYStringFromDateLong(long lDate) = 0;
};
