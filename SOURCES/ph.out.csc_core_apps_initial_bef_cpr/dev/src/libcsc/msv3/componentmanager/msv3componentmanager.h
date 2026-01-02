#ifndef GUARD_LIBCSC_MSV3_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_MSV3_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <msv3/orderresponse/orderresponserepositoryptr.h>
#include <msv3/transmissionresponse/transmissionresponserepositoryptr.h>
#include <msv3/customerdata/customerdatarepositoryptr.h>


class pxSession;

namespace libcsc {
namespace msv3 {

class MSV3ComponentManager : public persistence::ITransactionFactory,
							 public boost::enable_shared_from_this<MSV3ComponentManager>
{
public:
	MSV3ComponentManager();
	virtual ~MSV3ComponentManager();

	void injectConnection( persistence::ConnectionPtr connection );
	void injectTransactionHandler (nDataBase * transHandler);

	virtual libcsc::persistence::TransactionGuard	createTransaction() const;

	TransmissionResponseRepositoryPtr				getTransmissionResponseRepository();
	OrderResponseRepositoryPtr						getOrderResponseRepository();
	CustomerDataRepositoryPtr						getCustomerDataRepository();

private:
	MSV3ComponentManager( const MSV3ComponentManager & );
	MSV3ComponentManager & operator=( const MSV3ComponentManager & );
	persistence::IAccessorPtr createAccessor();

	persistence::ConnectionPtr		m_Connection;
	nDataBase *						m_TransactionHandler;

	mutable TransmissionResponseRepositoryPtr	m_TransmissionResponseRepository;
	mutable OrderResponseRepositoryPtr			m_OrderResponseRepository;
	mutable CustomerDataRepositoryPtr			m_CustomerDataRepository;
};

} // end namespace msv3
} // end namespace libcsc

#endif //end GUARD_LIBCSC_MSV3_COMPONENT_MANAGER_H
