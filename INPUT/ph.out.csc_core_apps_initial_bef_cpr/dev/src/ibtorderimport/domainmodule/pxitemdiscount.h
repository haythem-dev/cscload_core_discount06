#ifndef GUARD_IBTORDERIMPORT_DOMMOD_PXITEMDISCOUNT_H
#define GUARD_IBTORDERIMPORT_DOMMOD_PXITEMDISCOUNT_H

//-----------------------------------------------------------------------------------------

#include "ipxitemdiscount.h"

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

class PxItemDiscount : public IPxItemDiscount
{
public:
	PxItemDiscount(const log4cplus::Logger& logger, ::pxItemDiscount* );
	virtual ~PxItemDiscount();

	virtual void			setDiscountValuePct(basar::Decimal );
	virtual void			setDiscountValuePctMan(basar::Decimal);
	virtual void			setPaymentTargetNo(basar::Int16);
	virtual void			setFixedPrice(basar::Decimal);
	virtual ::pxItemDiscount*	getPxVbItemDiscount();

private:
	PxItemDiscount( const PxItemDiscount& );
	PxItemDiscount& operator=( const PxItemDiscount& );

	const log4cplus::Logger&		getLogger();

	const log4cplus::Logger&		m_Logger;
	::pxItemDiscount*				m_pxItemDiscount;
};

//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------

#endif // GUARD_IBTORDERIMPORT_DOMMOD_PXITEMDISCOUNT_H

//-----------------------------------------------------------------------------------------
