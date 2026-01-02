#ifndef GUARD_LIBCSC_CSCORDER_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_CSCORDER_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include "base/irunnableptr.h"
#include "cscorder/cscorderflags/icscorderflagsrepositoryptr.h"
#include "cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepositoryptr.h"

class pxSession;

namespace libcsc {
namespace cscorder {

class CSCOrderComponentManager : public persistence::ITransactionFactory, public boost::enable_shared_from_this<CSCOrderComponentManager>
{
public:
    CSCOrderComponentManager();
    virtual ~CSCOrderComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectTransactionHandler(nDataBase* transHandler);

    virtual persistence::TransactionGuard createTransaction() const;
    repo::ICSCOrderFlagsRepositoryPtr getCSCOrderFlagsRepository();
    repo::ICSCOrderIBTPickingdataRepositoryPtr getCSCOrderIBTPickingdataRepository();

    libcsc::base::IRunnablePtr saveCSCCallplanUC(short branchno, int customerno, int timeto);


private:
    CSCOrderComponentManager( const CSCOrderComponentManager & );
    CSCOrderComponentManager & operator=( const CSCOrderComponentManager & );

    repo::ICSCOrderFlagsRepositoryPtr createCSCOrderFlagsRepository();
    repo::ICSCOrderIBTPickingdataRepositoryPtr createCSCOrderIBTPickingdataRepository();

    persistence::IAccessorPtr createAccessor();

    persistence::ConnectionPtr  m_Connection;
    nDataBase*                  m_TransactionHandler;
};

} // end namespace cscorder
} // end namespace libcsc

#endif //end GUARD_LIBCSC_CSCORDER_COMPONENT_MANAGER_H
