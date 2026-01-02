#pragma once

#include "DBePosBearbModelIF.h"

class CDBePosBearbModel : public CDBePosBearbModelIF
{
public:
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
};
