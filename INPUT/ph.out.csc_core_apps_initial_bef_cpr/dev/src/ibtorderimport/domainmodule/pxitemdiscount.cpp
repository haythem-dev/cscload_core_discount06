#include "pxitemdiscount.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <misc/metaclassmacro_definitions.h> // libutil
#include <misc/log_macro_definitions.h>      // libutil
#include "pxvb_includes.h"

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

PxItemDiscount::PxItemDiscount(const log4cplus::Logger& logger, ::pxItemDiscount* itemDisc) :
	m_Logger(logger), m_pxItemDiscount(itemDisc)
{
}

//-----------------------------------------------------------------------------------------

PxItemDiscount::~PxItemDiscount()
{
}

//-----------------------------------------------------------------------------------------

const log4cplus::Logger& PxItemDiscount::getLogger()
{
	return m_Logger;
}

//-----------------------------------------------------------------------------------------

void PxItemDiscount::setDiscountValuePct(basar::Decimal pct)
{
	m_pxItemDiscount->SetDiscountValuePct(pct.toFloat64());
}

//-----------------------------------------------------------------------------------------

void PxItemDiscount::setDiscountValuePctMan(basar::Decimal pct)
{
	m_pxItemDiscount->SetDiscountValPctMan(pct.toFloat64());
}

//-----------------------------------------------------------------------------------------

void PxItemDiscount::setPaymentTargetNo(basar::Int16 no)
{
	m_pxItemDiscount->SetPaymentTargetNo(no);
}

//-----------------------------------------------------------------------------------------

void PxItemDiscount::setFixedPrice(basar::Decimal pr)
{
	m_pxItemDiscount->SetFixedPrice( pr.toFloat64());
}

//-----------------------------------------------------------------------------------------

::pxItemDiscount* PxItemDiscount::getPxVbItemDiscount()
{
	return m_pxItemDiscount;
}

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------
