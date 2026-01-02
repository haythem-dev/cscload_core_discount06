#include "returnannouncementhead.h"
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace returns {

	ReturnAnnouncementHead::ReturnAnnouncementHead()
	{
		m_Positions = boost::make_shared<ReturnAnnouncementPosCollection>();
	}

	ReturnAnnouncementHead::~ReturnAnnouncementHead()
	{
	}

	basar::Int32 ReturnAnnouncementHead::getAnnouncementHeadId() const
	{
		return m_AnnouncementHeadId;
	}

	basar::Int32 ReturnAnnouncementHead::getAnnouncementId() const
	{
		return m_AnnouncementId;
	}

	const basar::VarString& ReturnAnnouncementHead::getAccCheckResultCode() const
	{
		return m_AccCheckResultCode;
	}

	const basar::VarString& ReturnAnnouncementHead::getWholesalerReferenceId() const
	{
		return m_WholesalerReferenceId;
	}

	const basar::VarString& ReturnAnnouncementHead::getDocumentId() const
	{
		return m_DocumentId;
	}

	const basar::VarString& ReturnAnnouncementHead::getTourId() const
	{
		return m_TourId;
	}

	basar::Int32 ReturnAnnouncementHead::getTourDepartureDate() const
	{
		return m_TourDepartureDate;
	}

	basar::Int32 ReturnAnnouncementHead::getTourDepartureTime() const
	{
		return m_TourDepartureTime;
	}

	basar::Int32 ReturnAnnouncementHead::getTourArrivalDate() const
	{
		return m_TourArrivalDate;
	}

	basar::Int32 ReturnAnnouncementHead::getTourArrivalTime() const
	{
		return m_TourArrivalTime;
	}

	basar::Int16 ReturnAnnouncementHead::getTransferStatus() const
	{
		return m_TransferStatus;
	}

	const ReturnAnnouncementPosCollectionPtr ReturnAnnouncementHead::getPositions() const
	{
		return m_Positions;
	}

	void ReturnAnnouncementHead::addPosition(ReturnAnnouncementPosPtr pos)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncement::addPosition()");

		m_Positions->push_back(pos);
	}

	void ReturnAnnouncementHead::setAnnouncementHeadId(const basar::Int32 id)
	{
		m_AnnouncementHeadId = id;
	}

	void ReturnAnnouncementHead::setAnnouncementId(const basar::Int32 id)
	{
		m_AnnouncementId = id;
	}

	void ReturnAnnouncementHead::setAccCheckResultCode(const basar::VarString& resultCode)
	{
		m_AccCheckResultCode = resultCode;
	}

	void ReturnAnnouncementHead::setWholesalerReferenceId(const basar::VarString& id)
	{
		m_WholesalerReferenceId = id;
	}

	void ReturnAnnouncementHead::setDocumentId(const basar::VarString& id)
	{
		m_DocumentId = id;
	}

	void ReturnAnnouncementHead::setTourId(const basar::VarString& id)
	{
		m_TourId = id;
	}

	void ReturnAnnouncementHead::setTourDepartureDate(const basar::Int32 date)
	{
		m_TourDepartureDate = date;
	}

	void ReturnAnnouncementHead::setTourDepartureTime(const basar::Int32 time)
	{
		m_TourDepartureTime = time;
	}

	void ReturnAnnouncementHead::setTourArrivalDate(const basar::Int32 date)
	{
		m_TourArrivalDate = date;
	}

	void ReturnAnnouncementHead::setTourArrivalTime(const basar::Int32 time)
	{
		m_TourArrivalTime = time;
	}

	void ReturnAnnouncementHead::setTransferStatus(const basar::Int16 status)
	{
		m_TransferStatus = status;
	}

	bool ReturnAnnouncementHead::isInsertable() const
	{
		return m_AccCheckResultCode.isDirty() &&
			   m_AnnouncementId.isDirty() &&
			   m_DocumentId.isDirty() &&
			   m_TourDepartureDate.isDirty() &&
			   m_TourId.isDirty() &&
			   m_TransferStatus.isDirty() &&
			   m_WholesalerReferenceId.isDirty();
	}

} //returns
} //libcsc
