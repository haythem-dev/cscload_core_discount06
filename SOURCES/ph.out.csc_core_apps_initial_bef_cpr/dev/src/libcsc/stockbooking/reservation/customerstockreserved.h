#ifndef GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_H
#define GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_H

#include <stockbooking/reservation/icustomerstockreserved.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace stockbooking {

class CustomerStockReserved : public ICustomerStockReserved
{
	friend class CustomerStockReservedMapperBase;

public:
	CustomerStockReserved();
	virtual ~CustomerStockReserved();

	 const basar::Int16&			getBranchNo() const;
	 const basar::Int32&			getCustomerNo() const;
	 const basar::Int32&			getArticleNo() const;
	 const basar::Int32&			getReservedQty() const;
	 const basar::Int32&			getDateFrom() const;
	 const basar::Int32&			getTimeFrom() const;
	 const basar::Int32&			getDateTo() const;
	 const basar::Int32&			getTimeTo() const;
	 const basar::Int32&			getKdAuftragNr() const;
	 const basar::Int16&			getReservType() const;

	 void							setBranchNo(const basar::Int16&);
	 void							setCustomerNo(const basar::Int32&);
	 void							setArticleNo(const basar::Int32&);
	 void							setReservedQty(const basar::Int32&);
	 void							setDateFrom(const basar::Int32&);
	 void							setTimeFrom(const basar::Int32&);
	 void							setDateTo(const basar::Int32&);
	 void							setTimeTo(const basar::Int32&);
	 void							setKdAuftragNr(const basar::Int32&);
	 void							setReservType(const basar::Int16&);


	bool							isInsertable() const;
	bool							isUpdatable() const;
	bool							isClean() const;
	bool							isDirty() const;


private:
	libcsc::Int16					m_BranchNo;
	libcsc::Int32					m_CustomerNo;
	libcsc::Int32					m_ArticleNo;
	libcsc::Int32					m_ReservedQty;
	libcsc::Int32					m_DateFrom;
	libcsc::Int32					m_TimeFrom;
	libcsc::Int32					m_DateTo;
	libcsc::Int32					m_TimeTo;
	libcsc::Int32					m_KdAuftragNr;
	libcsc::Int16					m_ReservType;

};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_H
