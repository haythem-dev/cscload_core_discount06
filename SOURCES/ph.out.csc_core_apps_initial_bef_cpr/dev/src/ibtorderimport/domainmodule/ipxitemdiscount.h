#ifndef GUARD_IBTORDERIMPORT_DOMMOD_IPXITEMDISCOUNT_H
#define GUARD_IBTORDERIMPORT_DOMMOD_IPXITEMDISCOUNT_H

#include <libbasar_definitions.h>
#include <pxitemdiscount.hpp>

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace domMod {


//-------------------------------------------------------------------------------------------------//

class IPxItemDiscount
{
public:
	virtual ~IPxItemDiscount() {};

	virtual void			setDiscountValuePct(basar::Decimal) = 0;
	virtual void			setDiscountValuePctMan(basar::Decimal) = 0;
	virtual void			setPaymentTargetNo(basar::Int16) = 0;
	virtual void			setFixedPrice(basar::Decimal) = 0;
	virtual ::pxItemDiscount*	getPxVbItemDiscount() = 0;
};

//-------------------------------------------------------------------------------------------------//

} // namespace domMod
} // namespace ibtorderimport

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERITEM_H

//-------------------------------------------------------------------------------------------------//
