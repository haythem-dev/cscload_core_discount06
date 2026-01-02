#ifndef GUARD_LIBCSC_RETURNS_RETURNSCOMPONENTMANAGER_H
#define GUARD_LIBCSC_RETURNS_RETURNSCOMPONENTMANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>

#include <returns/returnrulebook/ireturnrulebookrepositoryptr.h>
#include <returns/returnannouncement/ireturnannouncementrepositoryptr.h>
#include <returns/returnperiod/ireturnperiodrepositoryptr.h>
#include <returns/returnpositioncheckuc/returnpositioncheckuc.h>

class pxSession;

namespace libcsc {
namespace returns {

	class ReturnComponentManager : public persistence::ITransactionFactory,
								   public boost::enable_shared_from_this<ReturnComponentManager>
	{
	public:
		ReturnComponentManager();
		virtual ~ReturnComponentManager();

		void injectConnection(persistence::ConnectionPtr connection);
		void injectTransactionHandler(nDataBase * transactionHandler);
		void injectSession(pxSession* sess);

		virtual libcsc::persistence::TransactionGuard	createTransaction() const;

		IReturnRuleBookRepositoryPtr		getReturnRuleBookRepository();
		IReturnAnnouncementRepositoryPtr	getReturnAnnouncementRepository();
		IReturnPeriodRepositoryPtr			getReturnPeriodRepository();
		ReturnPositionCheckUCPtr			getReturnPositionCheckUC();

	private:
		ReturnComponentManager(const ReturnComponentManager &);
		ReturnComponentManager & operator=(const ReturnComponentManager &);

		persistence::IAccessorPtr					createAccessor();

		persistence::ConnectionPtr					m_Connection;
		nDataBase *									m_TransactionHandler;

		mutable IReturnRuleBookRepositoryPtr		m_ReturnRuleBookRepository;
		mutable IReturnAnnouncementRepositoryPtr	m_ReturnAnnouncementRepository;
		mutable	IReturnPeriodRepositoryPtr			m_ReturnPeriodRepository;
		mutable ReturnPositionCheckUCPtr			m_ReturnPositionCheckUC;
		mutable pxSession*							m_Session;
	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNSCOMPONENTMANAGER_H
