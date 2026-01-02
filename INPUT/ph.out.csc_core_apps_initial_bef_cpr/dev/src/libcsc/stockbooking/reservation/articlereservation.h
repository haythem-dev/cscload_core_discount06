#ifndef GUARD_LIBCSC_STOCKBOOKING_ARTICLERESERVATION_H
#define GUARD_LIBCSC_STOCKBOOKING_ARTICLERESERVATION_H

#include <stockbooking/reservation/iarticlereservation.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace stockbooking {

class ArticleReservation : public IArticleReservation
{
	friend class ArticleReservationMapperBase;

public:
	ArticleReservation();
	virtual ~ArticleReservation();

	 const basar::Int16&			getBranchNo() const;
	 const basar::VarString&		getPharmacyGroupId() const;
	 const basar::Int32&			getArticleNo() const;
	 const basar::Int16&			getReservType() const;
	 const basar::Int32&			getMaxQty() const;
	 const basar::Int32&			getReservedQty() const;
	 const basar::Int16&			getReservePct() const;

	 void							setBranchNo(const basar::Int16&);
	 void							setPharmacyGroupId(const basar::VarString&);
	 void							setArticleNo(const basar::Int32&);
	 void							setReservType(const basar::Int16&);
	 void							setMaxQty(const basar::Int32&);
	 void							setReservedQty(const basar::Int32&);
	 void							setReservePct(const basar::Int16&);

	bool							isInsertable() const;
	bool							isUpdatable() const;
	bool							isClean() const;
	bool							isDirty() const;


private:
	libcsc::Int16					m_BranchNo;
	libcsc::VarString				m_PharmacyGroupId;
	libcsc::Int32					m_ArticleNo;
	libcsc::Int16					m_ReservType;
	libcsc::Int32					m_MaxQty;
	libcsc::Int32					m_ReservedQty;
	libcsc::Int16					m_ReservePct;
};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ARTICLERESERVATION_H
