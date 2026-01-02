#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAREPOSITORY_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAREPOSITORY_H

#include <persistence/itransactionfactoryptr.h>
#include <persistence/iaccessorptr.h>
#include <pxsess.hpp>
#include "icscorderibtpickingdatarepository.h"

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderIBTPickingdataRepository : public ICSCOrderIBTPickingdataRepository
{
public:
    CSCOrderIBTPickingdataRepository();
    virtual ~CSCOrderIBTPickingdataRepository();

    void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
    void injectInsertAccessor(persistence::IAccessorPtr accessor);
    void injectFindAccessor(persistence::IAccessorPtr accessor);

    virtual domMod::CSCOrderIBTPickingdataCollectionPtr findPickingdata(
        const basar::Int32 cscorderno, const basar::Int32 cscorderposno);
    virtual bool savePickingdata(domMod::ICSCOrderIBTPickingdataPtr pickingdata);

private:
    persistence::ITransactionFactoryPtr m_TransactionFactory;
    persistence::IAccessorPtr m_InsertAccessor;
    persistence::IAccessorPtr m_FindAccessor;

    CSCOrderIBTPickingdataRepository& operator=(const CSCOrderIBTPickingdataRepository&);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAREPOSITORY_H
