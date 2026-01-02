#ifndef GUARD_LIBCSC_CSCORDERTYPE_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_CSCORDERTYPE_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include <cscordertype/repository/icscordertyperepositoryptr.h>

class pxSession;

namespace libcsc
{
namespace cscordertype
{
class CSCOrderTypeComponentManager : public persistence::ITransactionFactory,
		public boost::enable_shared_from_this<CSCOrderTypeComponentManager>
{
public:
    CSCOrderTypeComponentManager();
    virtual ~CSCOrderTypeComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectTransactionHandler( nDataBase* transHandler );

    virtual persistence::TransactionGuard createTransaction() const;
	ICSCOrderTypeRepositoryPtr				getCSCOrderTypeRepository();

private:
    CSCOrderTypeComponentManager( const CSCOrderTypeComponentManager& );
    CSCOrderTypeComponentManager & operator=( const CSCOrderTypeComponentManager& );

	ICSCOrderTypeRepositoryPtr createCSCOrderTypeRepository();

    persistence::IAccessorPtr createAccessor() const;

    persistence::ConnectionPtr  m_Connection;
    nDataBase *                 m_TransactionHandler;
	mutable ICSCOrderTypeRepositoryPtr		m_CSCOrderTypeRepository;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif //end GUARD_LIBCSC_CSCORDERTYPE_COMPONENT_MANAGER_H
