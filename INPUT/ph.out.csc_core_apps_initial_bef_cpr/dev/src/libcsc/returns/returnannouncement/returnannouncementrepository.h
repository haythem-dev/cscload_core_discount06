#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTREPOSITORY_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTREPOSITORY_H

#include "ireturnannouncementrepository.h"

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasar_definitions.h>

#include <returns/returnannouncement/returnannouncementptr.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementheadptr.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementposptr.h>

namespace basar {
	namespace db {
		namespace sql {
			class ResultsetRef;
		}
	}
}

namespace libcsc {
namespace returns {

	class ReturnAnnouncementRepository : public IReturnAnnouncementRepository
	{
	public:
		ReturnAnnouncementRepository();
		virtual ~ReturnAnnouncementRepository();

		virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);

		virtual void injectReturnAnnouncementAccessor(persistence::IAccessorPtr accessor);
		virtual void injectReturnAnnouncementHeadAccessor(persistence::IAccessorPtr accessor);
		virtual void injectReturnAnnouncementPosAccessor(persistence::IAccessorPtr accessor);
		virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
		virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);

		virtual ReturnAnnouncementPtr				createEmptyReturnAnnouncement() const;
		virtual ReturnAnnouncementPtr				findReturnAnnouncement(basar::Int32 returnAnnouncementId) const;
		virtual ReturnAnnouncementHeadCollectionPtr findReturnAnnouncementHeads(basar::Int32 announcementId) const;
		virtual ReturnAnnouncementPosCollectionPtr	findReturnAnnouncementPositions(basar::Int32 announcementHeadId) const;

		virtual void saveReturnAnnouncement(const ReturnAnnouncementPtr& returnAnnouncement) const;
		virtual void saveReturnAnnouncementHeads(const ReturnAnnouncementPtr& returnAnnouncement) const;
		virtual void saveReturnAnnouncementPositions(const ReturnAnnouncementHeadPtr& returnAnnouncementHead) const;

	private:
		persistence::ITransactionFactoryPtr m_TransactionFactory;
		persistence::IAccessorPtr			m_SelectReturnAnnouncementAccessor;
		persistence::IAccessorPtr			m_SelectReturnAnnouncementHeadAccessor;
		persistence::IAccessorPtr			m_SelectReturnAnnouncementPosAccessor;
		persistence::IAccessorPtr			m_InsertAccessor;
		persistence::IAccessorPtr			m_UpdateAccessor;
	};

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTREPOSITORY_H
