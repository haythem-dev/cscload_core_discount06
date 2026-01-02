#include "returnannouncementposmapperbase.h"
#include "returnannouncementpos.h"

namespace libcsc {
namespace returns {

	ReturnAnnouncementPosMapperBase::ReturnAnnouncementPosMapperBase(ReturnAnnouncementPosPtr returnannouncementPos)
		: m_returnAnnouncementPos(returnannouncementPos)
	{

	}

	ReturnAnnouncementPosMapperBase::~ReturnAnnouncementPosMapperBase()
	{

	}

	void ReturnAnnouncementPosMapperBase::map()
	{
		doMap();
	}

	void ReturnAnnouncementPosMapperBase::setAnnouncementHeadId(const basar::Int32 announcementHeadId)
	{
		m_returnAnnouncementPos->m_AnnouncementHeadId = announcementHeadId;
		m_returnAnnouncementPos->m_AnnouncementHeadId.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setPosNo(const basar::Int32 posNo)
	{
		m_returnAnnouncementPos->m_PosNo = posNo;
		m_returnAnnouncementPos->m_PosNo.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setAnnouncementPosRefId(const basar::Int32 announcementPosRefId)
	{
		m_returnAnnouncementPos->m_AnnouncementPosRefId = announcementPosRefId;
		m_returnAnnouncementPos->m_AnnouncementPosRefId.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setDeliveryAdviceNo(const basar::VarString& deliveryAdviceNo)
	{
		m_returnAnnouncementPos->m_DeliveryAdviceNo = deliveryAdviceNo;
		m_returnAnnouncementPos->m_DeliveryAdviceNo.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setDeliveryAdviceDate(const basar::Date& deliveryAdviceDate)
	{
		m_returnAnnouncementPos->m_DeliveryAdviceDate = deliveryAdviceDate;
		m_returnAnnouncementPos->m_DeliveryAdviceDate.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setDeliveryAdvicePosNo(const basar::Int32 deliveryAdvicePosNo)
	{
		m_returnAnnouncementPos->m_DeliveryAdvicePosNo = deliveryAdvicePosNo;
		m_returnAnnouncementPos->m_DeliveryAdvicePosNo.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setReturnReasonCode(const basar::VarString& returnReasonCode)
	{
		m_returnAnnouncementPos->m_ReturnReasonCode = returnReasonCode;
		m_returnAnnouncementPos->m_ReturnReasonCode.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setReturnQty(const basar::Int32 returnQty)
	{
		m_returnAnnouncementPos->m_ReturnQty = returnQty;
		m_returnAnnouncementPos->m_ReturnQty.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setArticleNo(const basar::Int32 articleNo)
	{
		m_returnAnnouncementPos->m_ArticleNo = articleNo;
		m_returnAnnouncementPos->m_ArticleNo.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setArticleCode(const basar::VarString& articleCode)
	{
		m_returnAnnouncementPos->m_ArticleCode = articleCode;
		m_returnAnnouncementPos->m_ArticleCode.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setCodetype(const basar::Int16 codeType)
	{
		m_returnAnnouncementPos->m_CodeType = codeType;
		m_returnAnnouncementPos->m_CodeType.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setBatch(const basar::VarString& batch)
	{
		m_returnAnnouncementPos->m_Batch = batch;
		m_returnAnnouncementPos->m_Batch.setClean();
	}

	void ReturnAnnouncementPosMapperBase::setExpiryDate(const basar::Int32 expiryDate)
	{
		m_returnAnnouncementPos->m_ExpiryDate = expiryDate;
		m_returnAnnouncementPos->m_ExpiryDate.setClean();
	}

} //libcsc
} //returns
