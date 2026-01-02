#ifndef GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARCOMPONENTMANAGER_H
#define GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARCOMPONENTMANAGER_H

#include <workingdayscalendar/iworkingdayscalendarrepositoryptr.h>

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>

namespace libcsc {
namespace workingdayscalendar {

	class WorkingdaysCalendarComponentManager : public persistence::ITransactionFactory,
												public boost::enable_shared_from_this<WorkingdaysCalendarComponentManager>
	{
	public:
		WorkingdaysCalendarComponentManager();
		virtual ~WorkingdaysCalendarComponentManager();

		void injectConnection(persistence::ConnectionPtr connection);
		void injectTransactionHandler(nDataBase * transactionHandler);

		virtual libcsc::persistence::TransactionGuard	createTransaction() const;

		IWorkingdaysCalendarRepositoryPtr	getWorkingdaysCalendarRepository();

	private:
		WorkingdaysCalendarComponentManager(const WorkingdaysCalendarComponentManager &);
		WorkingdaysCalendarComponentManager & operator=(const WorkingdaysCalendarComponentManager &);

		persistence::IAccessorPtr					createAccessor();

		persistence::ConnectionPtr					m_Connection;
		nDataBase *									m_TransactionHandler;

		mutable IWorkingdaysCalendarRepositoryPtr	m_WorkingdaysCalendarRepository;
	};

} // end namespace workingdayscalendar
} // end namespace libcscs

#endif // !GUARD_LIBCSC_WORKINGDAYSCALENDAR_WORKINGDAYSCALENDARCOMPONENTMANAGER_H
