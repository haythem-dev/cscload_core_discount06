#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSMAPPERBASE_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSMAPPERBASE_H

#include <libbasar_definitions.h>
#include "returnannouncementposptr.h"

namespace libcsc {
namespace returns {

	class ReturnAnnouncementPosMapperBase
	{
	public:
		ReturnAnnouncementPosMapperBase(ReturnAnnouncementPosPtr returnannouncementPos);

		void map();

	protected:
		virtual ~ReturnAnnouncementPosMapperBase();

		virtual void doMap() = 0;

		void setAnnouncementHeadId(const basar::Int32 announcementHeadId);
		void setPosNo(const basar::Int32 posNo);
		void setAnnouncementPosRefId(const basar::Int32 announcementPosRefId);
		void setDeliveryAdviceNo(const basar::VarString& deliveryAdviceNo);
		void setDeliveryAdviceDate(const basar::Date& deliveryAdviceDate);
		void setDeliveryAdvicePosNo(const basar::Int32 deliveryAdvicePosNo);
		void setReturnReasonCode(const basar::VarString& returnReasonCode);
		void setReturnQty(const basar::Int32 returnQty);
		void setArticleNo(const basar::Int32 articleNo);
		void setArticleCode(const basar::VarString& articleCode);
		void setCodetype(const basar::Int16 codeType);
		void setBatch(const basar::VarString& batch);
		void setExpiryDate(const basar::Int32 expiryDate);


	private:
		ReturnAnnouncementPosPtr m_returnAnnouncementPos;

	};

} // returns
} // libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOSMAPPERBASE_H
