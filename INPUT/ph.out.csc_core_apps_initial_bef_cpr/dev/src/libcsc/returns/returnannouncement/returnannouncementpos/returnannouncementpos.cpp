#include "returnannouncementpos.h"


namespace libcsc {
namespace returns {

	ReturnAnnouncementPos::ReturnAnnouncementPos() :
		m_FailedCheckId(CHECK_UNKNOWN),
		m_FailedCheckString()
	{
	}

	ReturnAnnouncementPos::~ReturnAnnouncementPos()
	{
	}

	basar::Int32 ReturnAnnouncementPos::getAnnouncementHeadId() const
	{
		return m_AnnouncementHeadId;
	}

	basar::Int32 ReturnAnnouncementPos::getPosNo() const
	{
		return m_PosNo;
	}

	basar::Int32 ReturnAnnouncementPos::getAnnouncementPosRefId() const
	{
		return m_AnnouncementPosRefId;
	}

	const basar::VarString&	ReturnAnnouncementPos::getDeliveryAdviceNo() const
	{
		return m_DeliveryAdviceNo;
	}

	const basar::Date& ReturnAnnouncementPos::getDeliveryAdviceDate() const
	{
		return m_DeliveryAdviceDate;
	}

	basar::Int32 ReturnAnnouncementPos::getDeliveryAdvicePosNo() const
	{
		return m_DeliveryAdvicePosNo;
	}

	const basar::VarString&	ReturnAnnouncementPos::getReturnReasonCode() const
	{
		return m_ReturnReasonCode;
	}

	basar::Int32 ReturnAnnouncementPos::getReturnQty() const
	{
		return m_ReturnQty;
	}

	basar::Int32 ReturnAnnouncementPos::getArticleNo() const
	{
		return m_ArticleNo;
	}

	const basar::VarString&	ReturnAnnouncementPos::getArticleCode() const
	{
		return m_ArticleCode;
	}

	basar::Int16 ReturnAnnouncementPos::getCodeType() const
	{
		return m_CodeType;
	}

	const basar::VarString&	ReturnAnnouncementPos::getBatch() const
	{
		return m_Batch;
	}

	basar::Int32 ReturnAnnouncementPos::getExpiryDate() const
	{
		return m_ExpiryDate;
	}

	ReturnAcceptanceCheckEnum ReturnAnnouncementPos::getFailedCheckId() const
	{
		return m_FailedCheckId;
	}

	const basar::VarString& ReturnAnnouncementPos::getFailedCheckString() const
	{
		return m_FailedCheckString;
	}


	void ReturnAnnouncementPos::setAnnouncementHeadId(const basar::Int32 id)
	{
		m_AnnouncementHeadId = id;
	}
	
	void ReturnAnnouncementPos::setPosNo(const basar::Int32 posNo)
	{
		m_PosNo = posNo;
	}

	void ReturnAnnouncementPos::setAnnouncementPosRefId(const basar::Int32 id)
	{
		m_AnnouncementPosRefId = id;
	}

	void ReturnAnnouncementPos::setDeliveryAdviceNo(const basar::VarString& no)
	{
		m_DeliveryAdviceNo = no;
	}

	void ReturnAnnouncementPos::setDeliveryAdviceDate(const basar::Date& date)
	{
		m_DeliveryAdviceDate = date;
	}

	void ReturnAnnouncementPos::setDeliveryAdvicePosNo(const basar::Int32 posNo)
	{
		m_DeliveryAdvicePosNo = posNo;
	}

	void ReturnAnnouncementPos::setReturnReasonCode(const basar::VarString& code)
	{
		m_ReturnReasonCode = code;
	}

	void ReturnAnnouncementPos::setReturnQty(const basar::Int32 qty)
	{
		m_ReturnQty = qty;
	}

	void ReturnAnnouncementPos::setArticleNo(const basar::Int32 articleNo)
	{
		m_ArticleNo = articleNo;
	}

	void ReturnAnnouncementPos::setArticleCode(const basar::VarString& code)
	{
		m_ArticleCode = code;
	}

	void ReturnAnnouncementPos::setCodeType(const basar::Int16 type)
	{
		m_CodeType = type;
	}

	void ReturnAnnouncementPos::setBatch(const basar::VarString& batch)
	{
		m_Batch = batch;
	}

	void ReturnAnnouncementPos::setExpiryDate(const basar::Int32 date)
	{
		m_ExpiryDate = date;
	}

	void ReturnAnnouncementPos::setFailedCheckId(const ReturnAcceptanceCheckEnum id)
	{
		m_FailedCheckId = id;
	}

	void ReturnAnnouncementPos::setFailedCheckString(const basar::VarString& str)
	{
		m_FailedCheckString = str;
	}


	bool ReturnAnnouncementPos::isInsertable() const
	{
		return m_AnnouncementHeadId.isDirty() &&
			   m_AnnouncementPosRefId.isDirty() &&
			   m_ArticleCode.isDirty() &&
			   m_ArticleNo.isDirty() &&
			   m_Batch.isDirty() &&
			   m_CodeType.isDirty() &&
			   m_DeliveryAdviceDate.isDirty() &&
			   m_DeliveryAdviceNo.isDirty() &&
			   m_DeliveryAdvicePosNo.isDirty() &&
			   m_ExpiryDate.isDirty() &&
			   m_PosNo.isDirty() &&
			   m_ReturnQty.isDirty() &&
			   m_ReturnReasonCode.isDirty();
	}

} // returns
} // libcsc
