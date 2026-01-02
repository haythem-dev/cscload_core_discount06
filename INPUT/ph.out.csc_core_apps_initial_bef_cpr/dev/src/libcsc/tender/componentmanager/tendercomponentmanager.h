#ifndef GUARD_LIBCSC_TENDER_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_TENDER_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include <parameter/ibranchparametergetterptr.h>
#include "tender/repository/tenderrepositoryptr.h"

class pxSession;

namespace libcsc
{
namespace tender
{

class TenderComponentManager : public persistence::ITransactionFactory, public boost::enable_shared_from_this<TenderComponentManager>
{
public:
    TenderComponentManager();
    virtual ~TenderComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectTransactionHandler(nDataBase* transHandler);
	void injectBatchParameterGetter(parameter::IBranchParameterGetterPtr);

    virtual persistence::TransactionGuard createTransaction() const;
    TenderRepositoryPtr createTenderRepository();

private:
    TenderComponentManager( const TenderComponentManager& );
    TenderComponentManager & operator=( const TenderComponentManager& );

    persistence::IAccessorPtr createAccessor();    

    persistence::ConnectionPtr				m_Connection;
    nDataBase *								m_TransactionHandler;
	parameter::IBranchParameterGetterPtr	m_BranchParameterGetter;
};

} // end namespace tender
} // end namespace libcsc

#endif //end GUARD_LIBCSC_TENDER_COMPONENT_MANAGER_H
