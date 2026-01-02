#include "pxitemdiscount.hpp"
#include "pxsess.hpp"
#include "pxorder.hpp"
#include <logger/loggerpool.h>

extern bool pxGlobalNoDatabaseWrite;

int pxItemDiscount::logKdAuftragPosRab(nString& m_str)
{
	if (!Session()->isBulgaria())
	{
		return ErrorState();
	}
	if ( KdAuftragNr_ == pxOrder::PSEUDO_ORDER_NUMBER )
		return ErrorState();
	if ( pxGlobalNoDatabaseWrite == true )
		return ErrorState();

	BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), m_str() );
	std::stringstream s;
	s << "Auftrag= " << KdAuftragNr_ << ", PosNr=" << PosNr_ << ", Typ=" << DiscountType_ << ", DiscountValuePct=" << (double)DiscountValuePct_ << ", DiscountValuePctMan=" << (double)DiscountValPctMan_;
	BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), s.str() );
	return ErrorState();
}
