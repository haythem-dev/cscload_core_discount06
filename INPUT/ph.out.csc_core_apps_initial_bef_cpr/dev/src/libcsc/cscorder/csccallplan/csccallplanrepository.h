#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLAN_REPOSITORY_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLAN_REPOSITORY_H

#include "icsccallplanrepository.h"
#include "cscorder/csccallplan/icsccallplanptr.h"
#include <libbasar_definitions.h>
#include <persistence/itransactionfactoryptr.h>
#include <persistence/iaccessorptr.h>

namespace libcsc {
namespace cscorder {
namespace domMod {
    class ICSCCallplan;
}
namespace repo {

class CSCCallplanRepository : public ICSCCallplanRepository
{
public:
    virtual ~CSCCallplanRepository();
    CSCCallplanRepository();

    void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
    void injectInsertAccessor(persistence::IAccessorPtr accessor);
    void injectUpdateAccessor(persistence::IAccessorPtr accessor);
    void injectFindAccessor(persistence::IAccessorPtr accessor);

    virtual bool saveCSCCallplan(domMod::ICSCCallplanPtr cscCallplan);

protected:


private:
    persistence::ITransactionFactoryPtr m_TransactionFactory;
    persistence::IAccessorPtr m_InsertAccessor;
    persistence::IAccessorPtr m_UpdateAccessor;
    persistence::IAccessorPtr m_FindAccessor;

    bool findCSCCallplan(domMod::ICSCCallplanPtr cscCallplan, basar::VarString& query, std::stringstream& log);

    CSCCallplanRepository& operator=(const CSCCallplanRepository&);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLAN_REPOSITORY_H
