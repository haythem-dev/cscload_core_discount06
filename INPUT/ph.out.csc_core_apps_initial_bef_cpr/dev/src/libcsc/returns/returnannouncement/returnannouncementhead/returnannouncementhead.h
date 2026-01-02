#ifndef GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEAD_H
#define GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEAD_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

#include <returns/returnannouncement/returnannouncementpos/returnannouncementposptr.h>

namespace libcsc {
namespace returns {

	class ReturnAnnouncementHead
	{
		friend class ReturnAnnouncementHeadMapperBase;
		friend class ReturnAnnouncementRepository;

	public:
		ReturnAnnouncementHead();
		virtual ~ReturnAnnouncementHead();

		virtual       basar::Int32		getAnnouncementHeadId() const;
		virtual       basar::Int32		getAnnouncementId() const;
		virtual const basar::VarString&	getAccCheckResultCode() const;
		virtual const basar::VarString&	getWholesalerReferenceId() const;
		virtual const basar::VarString&	getDocumentId() const;
		virtual const basar::VarString&	getTourId() const;
		virtual       basar::Int32		getTourDepartureDate() const;
		virtual       basar::Int32		getTourDepartureTime() const;
		virtual       basar::Int32		getTourArrivalDate() const;
		virtual       basar::Int32		getTourArrivalTime() const;
		virtual       basar::Int16		getTransferStatus() const;

		virtual void					setAnnouncementHeadId(const basar::Int32);
		virtual void					setAnnouncementId(const basar::Int32);
		virtual void					setAccCheckResultCode(const basar::VarString&);
		virtual void					setWholesalerReferenceId(const basar::VarString&);
		virtual void					setDocumentId(const basar::VarString&);
		virtual void					setTourId(const basar::VarString&);
		virtual void					setTourDepartureDate(const basar::Int32);
		virtual void					setTourDepartureTime(const basar::Int32);
		virtual void					setTourArrivalDate(const basar::Int32);
		virtual void					setTourArrivalTime(const basar::Int32);
		virtual void					setTransferStatus(const basar::Int16);

		virtual const ReturnAnnouncementPosCollectionPtr getPositions() const;
		virtual void					addPosition(ReturnAnnouncementPosPtr pos);

		bool isInsertable() const;

	private:
		libcsc::Int32		m_AnnouncementHeadId;
		libcsc::Int32		m_AnnouncementId;
		libcsc::VarString	m_AccCheckResultCode;
		libcsc::VarString	m_WholesalerReferenceId;
		libcsc::VarString	m_DocumentId;
		libcsc::VarString	m_TourId;
		libcsc::Int32		m_TourDepartureDate;
		libcsc::Int32		m_TourDepartureTime;	// not in DB!!!
		libcsc::Int32		m_TourArrivalDate;		// not in DB!!!
		libcsc::Int32		m_TourArrivalTime;		// not in DB!!!
		libcsc::Int16		m_TransferStatus;

		ReturnAnnouncementPosCollectionPtr m_Positions;
	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNANNOUNCEMENTHEAD_H
