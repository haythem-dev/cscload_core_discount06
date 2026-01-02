#ifndef GUARD_LIBCSC_CSCORDERPOS_CSCORDERPOSCOMPONENTMANAGER_H
#define GUARD_LIBCSC_CSCORDERPOS_CSCORDERPOSCOMPONENTMANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include "cscorderpos/cscorderpossplittinfo/icscorderpossplittinforepositoryptr.h"

class pxSession;

namespace libcsc {
namespace cscorderpos {

class CSCOrderposComponentManager
    : public persistence::ITransactionFactory, public boost::enable_shared_from_this<CSCOrderposComponentManager>
{
public:
    CSCOrderposComponentManager();
    virtual ~CSCOrderposComponentManager();

    void injectConnection(persistence::ConnectionPtr connection);
    void injectTransactionHandler(nDataBase* transHandler);

    virtual persistence::TransactionGuard createTransaction() const;
    repo::ICSCOrderposSplittinfoRepositoryPtr getCSCOrderposSplittinfoRepository();

private:
    CSCOrderposComponentManager(const CSCOrderposComponentManager &);
    CSCOrderposComponentManager& operator=(const CSCOrderposComponentManager&);

    repo::ICSCOrderposSplittinfoRepositoryPtr createCSCOrderposSplittinfoRepository();

    persistence::IAccessorPtr createAccessor();

    persistence::ConnectionPtr m_Connection;
    nDataBase* m_TransactionHandler;
};

} // end namespace cscorderpos
} // end namespace libcsc

#endif //end GUARD_LIBCSC_CSCORDERPOS_CSCORDERPOSCOMPONENTMANAGER_H
