#ifndef GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOREPOSITORY_H
#define GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOREPOSITORY_H

#include <persistence/itransactionfactoryptr.h>
#include <persistence/iaccessorptr.h>
#include <pxsess.hpp>
#include "icscorderpossplittinforepository.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

class CSCOrderposSplittinfoRepository : public ICSCOrderposSplittinfoRepository
{
public:
    CSCOrderposSplittinfoRepository();
    virtual ~CSCOrderposSplittinfoRepository();

    void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
    void injectInsertAccessor(persistence::IAccessorPtr accessor);
    void injectFindAccessor(persistence::IAccessorPtr accessor);

    virtual domMod::ICSCOrderposSplittinfoPtr findSplittinfo(const basar::Int32 cscorderno,
        const basar::Int32 cscorderposno, const SplittTypeEnum splitttype, const basar::Int32 date = 0);
    virtual bool saveSplittinfo(domMod::ICSCOrderposSplittinfoPtr splittinfo);

private:
    persistence::ITransactionFactoryPtr m_TransactionFactory;
    persistence::IAccessorPtr m_InsertAccessor;
    persistence::IAccessorPtr m_FindAccessor;

    CSCOrderposSplittinfoRepository& operator=(const CSCOrderposSplittinfoRepository&);
};

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOREPOSITORY_H
