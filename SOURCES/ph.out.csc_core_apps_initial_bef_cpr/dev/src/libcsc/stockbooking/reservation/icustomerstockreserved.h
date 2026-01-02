#ifndef GUARD_LIBCSC_STOCKBOOKING_I_CUSTOMERSTOCKRESERVED_H
#define GUARD_LIBCSC_STOCKBOOKING_I_CUSTOMERSTOCKRESERVED_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace stockbooking {

class ICustomerStockReserved
{

public:
	~ICustomerStockReserved(){}

	virtual const basar::Int16&			getBranchNo() const = 0;
	virtual const basar::Int32&			getCustomerNo() const = 0;
	virtual const basar::Int32&			getArticleNo() const = 0;
	virtual const basar::Int32&			getReservedQty() const = 0;
	virtual const basar::Int32&			getDateFrom() const = 0;
	virtual const basar::Int32&			getTimeFrom() const = 0;
	virtual const basar::Int32&			getDateTo() const = 0;
	virtual const basar::Int32&			getTimeTo() const = 0;
	virtual const basar::Int32&			getKdAuftragNr() const = 0;
	virtual const basar::Int16&			getReservType() const = 0;

	virtual void						setBranchNo(const basar::Int16&) = 0;
	virtual void						setCustomerNo(const basar::Int32&) = 0;
	virtual void						setArticleNo(const basar::Int32&) = 0;
	virtual void						setReservedQty(const basar::Int32&) = 0;
	virtual void						setDateFrom(const basar::Int32&) = 0;
	virtual void						setTimeFrom(const basar::Int32&) = 0;
	virtual void						setDateTo(const basar::Int32&) = 0;
	virtual void						setTimeTo(const basar::Int32&) = 0;
	virtual void						setKdAuftragNr(const basar::Int32&) = 0;
	virtual void						setReservType(const basar::Int16&)  = 0;

	virtual bool						isInsertable() const = 0;
	virtual bool						isUpdatable() const = 0;
	virtual bool						isClean() const = 0;
	virtual bool						isDirty() const = 0;

};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_H
