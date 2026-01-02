/*
 * componentmanager.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_COMPONENTMANAGER_H
#define GUARD_LIBCSC_CALLBACK_COMPONENTMANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include "callback/domainmodule/icritposptr.h"
#include "callback/domainmodule/inewcallbackptr.h"
#include "callback/domainmodule/inewcallbackcritposptr.h"
#include "callback/repository/irepositoryptr.h"
#include <libbasar_definitions.h>
#include <base/irunnableptr.h>
#include <sstream>

namespace libcsc {
namespace callback {

class ComponentManager : public boost::enable_shared_from_this<ComponentManager>, public persistence::ITransactionFactory
{
public:
    ComponentManager();
    ~ComponentManager();

    void injectConnection(persistence::ConnectionPtr connection);
    void injectTransactionHandler(nDataBase* transHandler);
    repo::IRepositoryPtr getRepository(basar::VarString const& dbName);

    virtual libcsc::persistence::TransactionGuard createTransaction() const;

    libcsc::base::IRunnablePtr getWriteNewCallbackCritPosUC(basar::VarString const& dbName, domMod::INewCallbackCritPosPtr const newCallbackCritPos);

    libcsc::base::IRunnablePtr getWriteNewCallbackUC(basar::VarString const& dbName, std::ifstream* msgStream, int languageCode, 
		const basar::VarString& smtpServer, const short smtpPort, domMod::INewCallbackPtr const newCallback);

    void getGetCallbackDivisionAndReasonName(basar::VarString const& dbName,
        basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString& divisionName, basar::VarString& reasonName);

private:
    ComponentManager(ComponentManager const& );
    ComponentManager& operator=(ComponentManager const &);

    persistence::IAccessorPtr createAccessor();
    repo::IRepositoryPtr createRepository(basar::VarString const& dbName);

    persistence::ConnectionPtr m_Connection;
    nDataBase* m_TransactionHandler;
};

} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_COMPONENTMANAGER_H
