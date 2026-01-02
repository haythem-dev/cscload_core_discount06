#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOS_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOS_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <returns/returnrulebook/returnacceptancecheckenum.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementPos
	{
		friend class ReturnAnnouncementPosMapperBase;

	public:
		ReturnAnnouncementPos();
		virtual ~ReturnAnnouncementPos();

		virtual       basar::Int32		getAnnouncementHeadId() const;
		virtual       basar::Int32		getPosNo() const;
		virtual       basar::Int32		getAnnouncementPosRefId() const;
		virtual const basar::VarString&	getDeliveryAdviceNo() const;
		virtual const basar::Date&		getDeliveryAdviceDate() const;
		virtual       basar::Int32		getDeliveryAdvicePosNo() const;
		virtual const basar::VarString&	getReturnReasonCode() const;
		virtual       basar::Int32		getReturnQty() const;
		virtual       basar::Int32		getArticleNo() const;
		virtual const basar::VarString&	getArticleCode() const;
		virtual       basar::Int16		getCodeType() const;
		virtual const basar::VarString&	getBatch() const;
		virtual       basar::Int32		getExpiryDate() const;
		virtual	      ReturnAcceptanceCheckEnum	getFailedCheckId() const;
		virtual	const basar::VarString&	getFailedCheckString() const;

		virtual void					setAnnouncementHeadId(const basar::Int32);
		virtual void					setPosNo(const basar::Int32);
		virtual void					setAnnouncementPosRefId(const basar::Int32);
		virtual void					setDeliveryAdviceNo(const basar::VarString&);
		virtual void					setDeliveryAdviceDate(const basar::Date&);
		virtual void					setDeliveryAdvicePosNo(const basar::Int32);
		virtual void					setReturnReasonCode(const basar::VarString&);
		virtual void					setReturnQty(const basar::Int32);
		virtual void					setArticleNo(const basar::Int32);
		virtual void					setArticleCode(const basar::VarString&);
		virtual void					setCodeType(const basar::Int16);
		virtual void					setBatch(const basar::VarString&);
		virtual void					setExpiryDate(const basar::Int32);
		virtual void					setFailedCheckId(const ReturnAcceptanceCheckEnum);
		virtual void					setFailedCheckString(const basar::VarString&);

		bool isInsertable() const;

	private:
		libcsc::Int32		m_AnnouncementHeadId;
		libcsc::Int32		m_PosNo;
		libcsc::Int32		m_AnnouncementPosRefId;
		libcsc::VarString	m_DeliveryAdviceNo;
		libcsc::Date		m_DeliveryAdviceDate;
		libcsc::Int32		m_DeliveryAdvicePosNo;
		libcsc::VarString	m_ReturnReasonCode;
		libcsc::Int32		m_ReturnQty;
		libcsc::Int32		m_ArticleNo;
		libcsc::VarString	m_ArticleCode;
		libcsc::Int16		m_CodeType;
		libcsc::VarString	m_Batch;
		libcsc::Int32		m_ExpiryDate;
		ReturnAcceptanceCheckEnum	m_FailedCheckId;
		basar::VarString	m_FailedCheckString;
	};

} // returns
} // libcsc

#endif // !GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTPOS_H
