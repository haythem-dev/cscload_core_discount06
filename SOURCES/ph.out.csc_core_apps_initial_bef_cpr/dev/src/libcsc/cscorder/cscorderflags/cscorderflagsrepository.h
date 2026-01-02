#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGS_REPOSITORY_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGS_REPOSITORY_H

#include "icscorderflagsrepository.h"
#include "icscorderflagsrepositoryptr.h"
#include <persistence/itransactionfactoryptr.h>
#include <persistence/iaccessorptr.h>
#include <pxsess.hpp>
#include "cscorder/cscorderflags/icscorderflags.h"
#include "cscorder/cscorderflags/icscorderflagsptr.h"

namespace log4cplus {
class Logger;
}

// CSCArchitecture: libcsc::infrastructure::repository::cscorder

namespace libcsc {
namespace cscorder {
namespace domMod {
}

namespace repo {

class CSCOrderFlagsRepository : public ICSCOrderFlagsRepository
{
public:
    virtual ~CSCOrderFlagsRepository();
    CSCOrderFlagsRepository();

	void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
	void injectDeleteAccessor(persistence::IAccessorPtr accessor);    
    void injectInsertAccessor(persistence::IAccessorPtr accessor);    
	void injectUpdateAccessor(persistence::IAccessorPtr accessor);    
    void injectFindAccessor(persistence::IAccessorPtr accessor);                

	virtual domMod::ICSCOrderFlagsPtr findCSCOrderFlags(const basar::Int32 cscorderno);           	    
	virtual bool saveCSCOrderFlags(domMod::ICSCOrderFlagsPtr cscOrderFlags);
    virtual bool deleteCSCOrderFlags(basar::Int32 const& cscorderno);

protected:
    

private:
    persistence::ITransactionFactoryPtr m_TransactionFactory;
	persistence::IAccessorPtr m_DeleteAccessor;              
	persistence::IAccessorPtr m_InsertAccessor;              
    persistence::IAccessorPtr m_UpdateAccessor;              
	persistence::IAccessorPtr m_FindAccessor;                      

    CSCOrderFlagsRepository& operator=(const CSCOrderFlagsRepository&);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGS_REPOSITORY_H
