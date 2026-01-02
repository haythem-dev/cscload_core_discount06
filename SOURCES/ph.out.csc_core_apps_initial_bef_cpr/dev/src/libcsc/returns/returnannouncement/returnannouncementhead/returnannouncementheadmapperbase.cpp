#include "returnannouncementheadmapperbase.h"
#include "returnannouncementhead.h"

namespace libcsc {
namespace returns {

	ReturnAnnouncementHeadMapperBase::ReturnAnnouncementHeadMapperBase(ReturnAnnouncementHeadPtr returnAnnouncementHead)
		: m_returnAnnouncementHead(returnAnnouncementHead)
	{

	}

	ReturnAnnouncementHeadMapperBase::~ReturnAnnouncementHeadMapperBase()
	{

	}

	void ReturnAnnouncementHeadMapperBase::map()
	{
		doMap();
	}

	void ReturnAnnouncementHeadMapperBase::mapSerial(const basar::Int32 id)
	{
		doMapSerial(id);
	}

	void ReturnAnnouncementHeadMapperBase::setAnnouncementHeadId(const basar::Int32 announcementHeadId)
	{
		m_returnAnnouncementHead->m_AnnouncementHeadId = announcementHeadId;
		m_returnAnnouncementHead->m_AnnouncementHeadId.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setAnnouncementId(const basar::Int32 announcementId)
	{
		m_returnAnnouncementHead->m_AnnouncementId = announcementId;
		m_returnAnnouncementHead->m_AnnouncementId.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setAccCheckResultCode(const basar::VarString accCheckResultCode)
	{
		m_returnAnnouncementHead->m_AccCheckResultCode = accCheckResultCode;
		m_returnAnnouncementHead->m_AccCheckResultCode.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setWholesalerReferenceId(const basar::VarString& wholesalerReferenceId)
	{
		m_returnAnnouncementHead->m_WholesalerReferenceId = wholesalerReferenceId;
		m_returnAnnouncementHead->m_WholesalerReferenceId.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setDocumentId(const basar::VarString& documentId)
	{
		m_returnAnnouncementHead->m_DocumentId = documentId;
		m_returnAnnouncementHead->m_DocumentId.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setTourId(const basar::VarString& tourId)
	{
		m_returnAnnouncementHead->m_TourId = tourId;
		m_returnAnnouncementHead->m_TourId.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setTourDepartureDate(const basar::Int32 tourDepartureDate)
	{
		m_returnAnnouncementHead->m_TourDepartureDate = tourDepartureDate;
		m_returnAnnouncementHead->m_TourDepartureDate.setClean();
	}

	void ReturnAnnouncementHeadMapperBase::setTransferStatus(const basar::Int16 transferStatus)
	{
		m_returnAnnouncementHead->m_TransferStatus = transferStatus;
		m_returnAnnouncementHead->m_TransferStatus.setClean();
	}

} //returns
} //libcsc
