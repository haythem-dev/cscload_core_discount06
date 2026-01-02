//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDiscount
 *  \author Steffen Heinlein
 *  \date   10.09.2014
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "recordtypediscount.h"
#include "recordtypeformatter.h"
#include "formattingexception.h"

#include <sstream>
#include <iomanip>

using namespace std;

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	//----------------------------------------------------------------------------//
	RecordTypeDiscount::RecordTypeDiscount( libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "PR", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF( RecordTypeDiscount, RecordTypeDiscount );		
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeDiscount::~RecordTypeDiscount()
	{
		METHODNAME_DEF( RecordTypeDiscount, ~RecordTypeDiscount );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeDiscount::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeDiscount, doSerialize );				
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, DiscountFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.BranchNo, DiscountFormat::LENGTH_BRANCHNO, ss );
			RecordTypeFormatter::serialize( m_Values.PharmosOrderNo, DiscountFormat::LENGTH_PHARMOSORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.OrderPosNo, DiscountFormat::LENGTH_ORDERPOSNO, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountMode, DiscountFormat::LENGTH_DISCOUNTMODE, ss );
			RecordTypeFormatter::serialize( m_Values.OrderNo, DiscountFormat::LENGTH_ORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.CurrentDate, DiscountFormat::LENGTH_CURRENTDATE, ss );
			RecordTypeFormatter::serialize( m_Values.Discount, DiscountFormat::LENGTH_DISCOUNT, DiscountFormat::DECPLACES_DISCOUNT, ss );
			RecordTypeFormatter::serialize( m_Values.Origin, DiscountFormat::LENGTH_ORIGIN, ss );
			RecordTypeFormatter::serialize( m_Values.InternalRebate, DiscountFormat::LENGTH_INTERNALREBATE, ss );
			RecordTypeFormatter::serialize( m_Values.RefundPercent, DiscountFormat::LENGTH_REFUNDPERCENT, DiscountFormat::DECPLACES_REFUNDPERCENT, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountBase, DiscountFormat::LENGTH_DISCOUNTBASE, ss );
			RecordTypeFormatter::serialize( m_Values.PharmacyGroup, DiscountFormat::LENGTH_PHARMACYGROUP, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountCalcFrom, DiscountFormat::LENGTH_DISCOUNTCALCFROM, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountApplyTo, DiscountFormat::LENGTH_DISCOUNTAPPLYTO, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountSortBase, DiscountFormat::LENGTH_DISCOUNTSORTBASE, ss );
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeDiscount: Formatting exception!", __FILE__, __LINE__ ) ); 			
		}

		return ss.str().c_str();			
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setBranchNo( const basar::Int16 branchno )
	{
		m_Values.BranchNo = branchno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setOrderPosNo( const basar::Long64& orderposno )
	{
		m_Values.OrderPosNo = orderposno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setDiscountMode( const basar::Int32 discountmode )
	{
		m_Values.DiscountMode = discountmode;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setOrderNo( const basar::Long64& orderno )
	{
		m_Values.OrderNo = orderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setDiscount( const basar::Decimal& discount )
	{
		m_Values.Discount = discount;
		m_Values.Discount.round(4);
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setInternalRebate(const basar::Int16 internalRebate)
	{
		m_Values.InternalRebate = internalRebate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setRefundPercent(const basar::Decimal& refundPercent)
	{
		m_Values.RefundPercent = refundPercent;
		m_Values.RefundPercent.round(2);
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setDiscountBase(const basar::Int16 discountBase)
	{
		m_Values.DiscountBase = discountBase;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setPharmacyGroup(const basar::VarString& pharmacyGroup)
	{
		m_Values.PharmacyGroup = pharmacyGroup;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setDiscountCalcFrom(const basar::Int16 discountCalcFrom)
	{
		m_Values.DiscountCalcFrom = discountCalcFrom;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setDiscountApplyTo(const basar::Int16 discountApplyTo)
	{
		m_Values.DiscountApplyTo = discountApplyTo;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeDiscount::setDiscountSortBase(const basar::Int16 discountSortBase)
	{
		m_Values.DiscountSortBase = discountSortBase;
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
