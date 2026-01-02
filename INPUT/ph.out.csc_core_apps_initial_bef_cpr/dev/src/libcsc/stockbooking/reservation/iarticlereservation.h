#ifndef GUARD_LIBCSC_STOCKBOOKING_I_ARTICLERESERVATION_H
#define GUARD_LIBCSC_STOCKBOOKING_I_ARTICLERESERVATION_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace stockbooking {

class IArticleReservation
{

public:
	~IArticleReservation(){}

	virtual const basar::Int16&			getBranchNo() const = 0;
	virtual const basar::VarString&		getPharmacyGroupId() const = 0;
	virtual const basar::Int32&			getArticleNo() const = 0;
	virtual const basar::Int16&			getReservType() const = 0;
	virtual const basar::Int32&			getMaxQty() const = 0;
	virtual const basar::Int32&			getReservedQty() const = 0;
	virtual const basar::Int16&			getReservePct() const = 0;

	virtual void						setBranchNo(const basar::Int16&) = 0;
	virtual void						setPharmacyGroupId(const basar::VarString&)  = 0;
	virtual void						setArticleNo(const basar::Int32&)  = 0;
	virtual void						setReservType(const basar::Int16&)  = 0;
	virtual void						setMaxQty(const basar::Int32&)  = 0;
	virtual void						setReservedQty(const basar::Int32&)  = 0;
	virtual void						setReservePct(const basar::Int16&) = 0;


	virtual bool						isInsertable() const = 0;
	virtual bool						isUpdatable() const = 0;
	virtual bool						isClean() const = 0;
	virtual bool						isDirty()const = 0;

};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_ARTICLERESERVATION_H
