#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESMAPPERBASE_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESMAPPERBASE_H

#include "blockedarticlesptr.h"
#include <libbasar_definitions.h>

namespace libcsc {
namespace blockedarticles {

	class BlockedArticlesMapperBase
	{
	public:
		BlockedArticlesMapperBase(BlockedArticlesPtr blockedArticles);

		void map();


	protected:
		virtual ~BlockedArticlesMapperBase();

		virtual void doMap() = 0;

		void setBranchNo(const basar::Int16 branchNo);
		void setArticleNo(const basar::Int32 articleNo);
		void setBlockedID(const basar::Int32 blockedID);
		void setStorageLocation(const basar::VarString& storageLocation);
		void setQuantity(const basar::Int32 quantity);
		void setBookingType(const basar::Int16 bookingType);
		void setCreationTime(const basar::Int32 creationTime);
		void setCreationDate(const basar::Int32 creationDate);
		void setProcessedDate(const basar::Int32 processedDate);
		void setProcessedTime(const basar::Int32 processedTime);

	private:
		BlockedArticlesPtr m_BlockedArticles;
	};

} // namespace blockedarticles
} // namespace libcsc

#endif // !GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESMAPPERBASE_H
