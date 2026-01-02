//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeOrderLine
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <sstream>
#include <iomanip>
#include "formattingexception.h"

#include "recordtypeorderline.h"
#include "recordtypeformatter.h"

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
	RecordTypeOrderLine::RecordTypeOrderLine( libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "P1", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF( RecordTypeOrderLine, RecordTypeOrderLine );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeOrderLine::~RecordTypeOrderLine()
	{
		METHODNAME_DEF( RecordTypeOrderLine, ~RecordTypeOrderLine );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeOrderLine::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeOrderLine, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, OrderLineFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.LineNo, OrderLineFormat::LENGTH_LINENO, ss );
			RecordTypeFormatter::serialize( m_Values.ArticleNo, OrderLineFormat::LENGTH_ARTICLENO, ss );
			RecordTypeFormatter::serialize( m_Values.LineType, OrderLineFormat::LENGTH_LINETYPE, ss );
			RecordTypeFormatter::serialize( m_Values.DeviceType, OrderLineFormat::LENGTH_DEVICETYPE, ss );
			RecordTypeFormatter::serialize( m_Values.QState, OrderLineFormat::LENGTH_QSTATE, ss );
			RecordTypeFormatter::serialize( m_Values.ArticleState, OrderLineFormat::LENGTH_ARTICLESTATE, ss );
			RecordTypeFormatter::serialize( m_Values.ET1Flags, OrderLineFormat::LENGTH_ET1FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET2Flags, OrderLineFormat::LENGTH_ET2FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET3Flags, OrderLineFormat::LENGTH_ET3FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET4Flags, OrderLineFormat::LENGTH_ET4FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET5Flags, OrderLineFormat::LENGTH_ET5FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET6Flags, OrderLineFormat::LENGTH_ET6FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.OrderQty, OrderLineFormat::LENGTH_ORDERQTY, ss );
			RecordTypeFormatter::serialize( m_Values.DispensingForm, OrderLineFormat::LENGTH_DISPENSINGFORM, ss );
			RecordTypeFormatter::serialize( m_Values.Unit, OrderLineFormat::LENGTH_UNIT, ss );
			RecordTypeFormatter::serialize( m_Values.ArticleName, OrderLineFormat::LENGTH_ARTICLENAME, ss );
			RecordTypeFormatter::serialize( m_Values.Discountable, OrderLineFormat::LENGTH_DISCOUNTABLE, ss );
			RecordTypeFormatter::serialize( m_Values.CommodityGroup, OrderLineFormat::LENGTH_COMMODITYGROUP, ss );
			RecordTypeFormatter::serialize( m_Values.FILLER_01, OrderLineFormat::LENGTH_FILLER_01, ss );
			RecordTypeFormatter::serialize( m_Values.ConfirmedQty, OrderLineFormat::LENGTH_CONFIRMEDQTY, ss );
			RecordTypeFormatter::serialize( m_Values.DeliveryQty, OrderLineFormat::LENGTH_DELIVERYQTY, ss );
			RecordTypeFormatter::serialize( m_Values.BookedQty, OrderLineFormat::LENGTH_BOOKEDQTY, ss );
			RecordTypeFormatter::serialize( m_Values.QtyRebateInKind, OrderLineFormat::LENGTH_QTYREBATEINKIND, ss );
			RecordTypeFormatter::serialize( m_Values.FILLER_02, OrderLineFormat::LENGTH_FILLER_02, ss );
			RecordTypeFormatter::serialize( m_Values.QtyRebateInKindWholesale, OrderLineFormat::LENGTH_QTYREBATEINKINDWHOLESALE, ss );
			RecordTypeFormatter::serialize( m_Values.QtyRebateInKindManufacturer, OrderLineFormat::LENGTH_QTYREBATEINKINDMANUFACTURER, ss );
			RecordTypeFormatter::serialize( m_Values.PharmacyPurchasePrice, OrderLineFormat::LENGTH_PHARMACYPURCHASEPRICE, OrderLineFormat::DECPLACES_PHARMACYPURCHASEPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.PharmacySellPrice, OrderLineFormat::LENGTH_PHARMACYSELLPRICE, OrderLineFormat::DECPLACES_PHARMACYSELLPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.NetPrice, OrderLineFormat::LENGTH_NETPRICE, OrderLineFormat::DECPLACES_NETPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.CostPrice, OrderLineFormat::LENGTH_COSTPRICE, OrderLineFormat::DECPLACES_COSTPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.NetCostPrice, OrderLineFormat::LENGTH_NETCOSTPRICE, OrderLineFormat::DECPLACES_NETCOSTPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountValueSign, OrderLineFormat::LENGTH_DISCOUNTVALUESIGN, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountValue, OrderLineFormat::LENGTH_DISCOUNTVALUE, OrderLineFormat::DECPLACES_DISCOUNTVALUE, ss );
			RecordTypeFormatter::serialize( m_Values.FILLER_03, OrderLineFormat::LENGTH_FILLER_03, ss );
			RecordTypeFormatter::serialize( m_Values.FixedDiscount, OrderLineFormat::LENGTH_FIXEDDISCOUNT, OrderLineFormat::DECPLACES_FIXEDDISCOUNT, ss );
			RecordTypeFormatter::serialize( m_Values.FILLER_04, OrderLineFormat::LENGTH_FILLER_04, ss );
			RecordTypeFormatter::serialize( m_Values.Hints, OrderLineFormat::LENGTH_HINTS, ss );
			RecordTypeFormatter::serialize( m_Values.IBTQty, OrderLineFormat::LENGTH_IBTQTY, ss );
			RecordTypeFormatter::serialize( m_Values.IBTBranchNo, OrderLineFormat::LENGTH_IBTBRANCHNO, ss );
			RecordTypeFormatter::serialize( m_Values.IBTBranchNo2, OrderLineFormat::LENGTH_IBTBRANCHNO2, ss );
			RecordTypeFormatter::serialize( m_Values.IBTOriginCustomerNo, OrderLineFormat::LENGTH_IBTORIGINCUSTOMERNO, ss );
			RecordTypeFormatter::serialize( m_Values.IBTOriginOrderNo, OrderLineFormat::LENGTH_IBTORIGINORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.IBTOriginLineNo, OrderLineFormat::LENGTH_IBTORIGINLINENO, ss );
			RecordTypeFormatter::serialize( m_Values.FILLER_05, OrderLineFormat::LENGTH_FILLER_05, ss );
			RecordTypeFormatter::serialize( m_Values.ArtET2, OrderLineFormat::LENGTH_ARTET2, ss );
			RecordTypeFormatter::serialize( m_Values.PreDeliveryQty, OrderLineFormat::LENGTH_PREDELIVERYQTY, ss );
			RecordTypeFormatter::serialize( m_Values.ChangeDiscount, OrderLineFormat::LENGTH_CHANGEDISCOUNT, OrderLineFormat::DECPLACES_CHANGEDISCOUNT, ss );
			RecordTypeFormatter::serialize( m_Values.BonusAbility, OrderLineFormat::LENGTH_BONUSABILITY, OrderLineFormat::DECPLACES_BONUSABILITY, ss );
			RecordTypeFormatter::serialize( m_Values.ChangeDiscountType, OrderLineFormat::LENGTH_CHANGEDISCOUNTTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.XMLReference, OrderLineFormat::LENGTH_XMLREFERENCE, ss );
			RecordTypeFormatter::serialize( m_Values.CodeBlocage, OrderLineFormat::LENGTH_CODEBLOCAGE, ss );
			RecordTypeFormatter::serialize( m_Values.TaxLevel, OrderLineFormat::LENGTH_TAXLEVEL, ss );
			RecordTypeFormatter::serialize( m_Values.InvoicedPurchaseGroup, OrderLineFormat::LENGTH_INVOICEDPURCHASEGROUP, ss );
			RecordTypeFormatter::serialize( m_Values.OriginalIBTQty, OrderLineFormat::LENGTH_ORIGINALIBTQTY, ss );
			RecordTypeFormatter::serialize( m_Values.PriceType, OrderLineFormat::LENGTH_PRICETYPE, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTargetDiscPercentage1, OrderLineFormat::LENGTH_PAYMENTTARGETDISCPERCENTAGE1, OrderLineFormat::DECPLACES_PAYMENTTARGETDISCPERCENTAGE1, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTargetDiscPercentage2, OrderLineFormat::LENGTH_PAYMENTTARGETDISCPERCENTAGE2, OrderLineFormat::DECPLACES_PAYMENTTARGETDISCPERCENTAGE2, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTargetDiscPercentage3, OrderLineFormat::LENGTH_PAYMENTTARGETDISCPERCENTAGE3, OrderLineFormat::DECPLACES_PAYMENTTARGETDISCPERCENTAGE3, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTargetDiscPercentage4, OrderLineFormat::LENGTH_PAYMENTTARGETDISCPERCENTAGE4, OrderLineFormat::DECPLACES_PAYMENTTARGETDISCPERCENTAGE4, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTargetDiscPercentage5, OrderLineFormat::LENGTH_PAYMENTTARGETDISCPERCENTAGE5, OrderLineFormat::DECPLACES_PAYMENTTARGETDISCPERCENTAGE5, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTargetDiscPercentage6, OrderLineFormat::LENGTH_PAYMENTTARGETDISCPERCENTAGE6, OrderLineFormat::DECPLACES_PAYMENTTARGETDISCPERCENTAGE6, ss );
			RecordTypeFormatter::serialize( m_Values.InvoicePrice, OrderLineFormat::LENGTH_INVOICEPRICE, OrderLineFormat::DECPLACES_INVOICEPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.MaxPaymentTarget, OrderLineFormat::LENGTH_MAXPAYMENTTARGET, ss );
			RecordTypeFormatter::serialize( m_Values.ContLevel, OrderLineFormat::LENGTH_CONTLEVEL, ss );
			RecordTypeFormatter::serialize( m_Values.MaxPharmacySellPrice, OrderLineFormat::LENGTH_MAXPHARMACYSELLPRICE, OrderLineFormat::DECPLACES_MAXPHARMACYSELLPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.SkontoAbility, OrderLineFormat::LENGTH_SKONTOABILITY, OrderLineFormat::DECPLACES_SKONTOABILITY, ss );
			RecordTypeFormatter::serialize( m_Values.DesiredBatch, OrderLineFormat::LENGTH_DESIREDBATCH, ss );
			RecordTypeFormatter::serialize( m_Values.AmedisPriceDifference, OrderLineFormat::LENGTH_AMEDISPRICEDIFFERENCE, OrderLineFormat::DECPLACES_AMEDISPRICEDIFFERENCE, ss );
			RecordTypeFormatter::serialize( m_Values.CalcPharmacySellPrice, OrderLineFormat::LENGTH_CALCPHARMACYSELLPRICE, OrderLineFormat::DECPLACES_CALCPHARMACYSELLPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.ArticleCode, OrderLineFormat::LENGTH_ARTICLECODE, ss );
			RecordTypeFormatter::serialize( m_Values.CodeType, OrderLineFormat::LENGTH_CODETYPE, ss );
			RecordTypeFormatter::serialize( m_Values.ServiceNo, OrderLineFormat::LENGTH_SERVICENO, ss );
			RecordTypeFormatter::serialize( m_Values.ET7Flags, OrderLineFormat::LENGTH_ET7FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.MarginCluster,	OrderLineFormat::LENGTH_MARGINCLUSTER, OrderLineFormat::DECPLACES_MARGINCLUSTER, ss );
			RecordTypeFormatter::serialize( m_Values.BusinessType, OrderLineFormat::LENGTH_BUSINESSTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.TourIdIbt, OrderLineFormat::LENGTH_TOURIDIBT, ss );
			RecordTypeFormatter::serialize( m_Values.SubDeviceType, OrderLineFormat::LENGTH_SUBDEVICETYPE, ss );
			RecordTypeFormatter::serialize( m_Values.IBTWeekday, OrderLineFormat::LENGTH_IBTWEEKDAY, ss );
			RecordTypeFormatter::serialize( m_Values.NumberOfDiscountRecords, OrderLineFormat::LENGTH_NUMBEROFDISCOUNTRECORDS, ss );
			RecordTypeFormatter::serialize( m_Values.PurchaseRelevantQuantity, OrderLineFormat::LENGTH_PURCHASERELEVANTQUANTITY, ss );
			RecordTypeFormatter::serialize( m_Values.OriginalOrderedQuantity, OrderLineFormat::LENGTH_ORIGINALORDEREDQUANTITY, ss );
			RecordTypeFormatter::serialize( m_Values.IBTDeliveryDate, OrderLineFormat::LENGTH_IBTDELIVERYDATE, ss );
            RecordTypeFormatter::serialize( m_Values.FixBatch, OrderLineFormat::LENGTH_FIXBATCH, ss );
			RecordTypeFormatter::serialize( m_Values.IBTOriginFMDCustomer, OrderLineFormat::LENGTH_IBTORIGINFMDCUSTOMER, ss );
			RecordTypeFormatter::serialize( m_Values.PromotionNo, OrderLineFormat::LENGTH_PROMOTIONNO, ss );
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeOrderLine: Formatting exception!", __FILE__, __LINE__ ) );
		}

		return ss.str().c_str();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setLineNo( const basar::Long64& lineno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setLineNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.LineNo = lineno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setArticleNo( const basar::Long64& articleno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setArticleNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ArticleNo = articleno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setLineType( const basar::Int32 linetype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setLineType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.LineType = linetype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setDeviceType( const basar::Int32 devicetype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setDeviceType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DeviceType = devicetype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setQState( const basar::Int32 qstate )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setQState );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.QState = qstate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setArticleState( const basar::Int32 articlestate )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setArticleState );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ArticleState = articlestate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET1Flags( const basar::Long64& et1flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET1Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET1Flags = et1flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET2Flags( const basar::Long64& et2flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET2Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET2Flags = et2flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET3Flags( const basar::Long64& et3flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET3Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET3Flags = et3flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET4Flags( const basar::Long64& et4flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET4Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET4Flags = et4flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET5Flags( const basar::Long64& et5flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET5Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET5Flags = et5flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET6Flags( const basar::Long64& et6flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET6Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET6Flags = et6flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setOrderQty( const basar::Long64& orderqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setOrderQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.OrderQty = orderqty;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setDispensingForm( const basar::VarString& dispensingform )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setDispensingForm );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DispensingForm = dispensingform;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setUnit( const basar::VarString& unit )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setUnit );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Unit = unit;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setArticleName( const basar::VarString& articlename )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setArticleName );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ArticleName = articlename;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setDiscountable( const basar::Int32 discountable )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setDiscountable );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Discountable = discountable;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setCommodityGroup( const basar::VarString& commoditygroup )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setCommodityGroup );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.CommodityGroup = commoditygroup;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setConfirmedQty( const basar::Long64& confirmedqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setConfirmedQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ConfirmedQty = confirmedqty;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setDeliveryQty( const basar::Long64& deliveryqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setDeliveryQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DeliveryQty = deliveryqty;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setBookedQty( const basar::Long64& bookedqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setBookedQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.BookedQty = bookedqty;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setQtyRebateInKind( const basar::Long64& qtyrebateinkind )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setQtyRebateInKind );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.QtyRebateInKind = qtyrebateinkind;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setQtyRebateInKindWholesale( const basar::Long64& qtyrebateinkindwholesale )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setQtyRebateInKindWholesale );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.QtyRebateInKindWholesale = qtyrebateinkindwholesale;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setQtyRebateInKindManufacturer( const basar::Long64& qtyrebateinkindmanufacturer )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setQtyRebateInKindManufacturer );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.QtyRebateInKindManufacturer = qtyrebateinkindmanufacturer;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPharmacyPurchasePrice( basar::Decimal& pharmacypurchaseprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPharmacyPurchasePrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		pharmacypurchaseprice.round(2);
		m_Values.PharmacyPurchasePrice = pharmacypurchaseprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPharmacySellPrice( basar::Decimal& pharmacysellprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPharmacySellPrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		pharmacysellprice.round(2);
		m_Values.PharmacySellPrice = pharmacysellprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setNetPrice( basar::Decimal& netprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setNetPrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		netprice.round(2);
		m_Values.NetPrice = netprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setCostPrice( basar::Decimal& costprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setCostPrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		costprice.round(2);
		m_Values.CostPrice = costprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setNetCostPrice( basar::Decimal& netcostprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setNetCostPrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		netcostprice.round(2);
		m_Values.NetCostPrice = netcostprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setDiscountValue( basar::Decimal& discountvalue )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setDiscountValue );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		discountvalue.round(2);
		m_Values.DiscountValue = discountvalue;
		if( 0 > m_Values.DiscountValue.toFloat64() )
		{
			m_Values.DiscountValueSign = "-";
		}
		else
		{
			m_Values.DiscountValueSign = "+";
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setFixedDiscount( basar::Decimal& fixeddiscount )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setFixedDiscount );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		fixeddiscount.round(2);
		m_Values.FixedDiscount = fixeddiscount;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setHints( const basar::VarString& hints )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setHints );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Hints = hints;
		//m_Values.Hints.cleanchar(); //-> I18nString
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTQty( const basar::Long64& ibtqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTQty = ibtqty;
	}
	//----------------------------------------------------------------------------//

    basar::Int32 RecordTypeOrderLine::getIBTBranchNo()
    {
        return m_Values.IBTBranchNo;
    }

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTBranchNo( const basar::Int32 ibtbranchno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTBranchNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTBranchNo = ibtbranchno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTBranchNo2( const basar::Int32 ibtbranchno2 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTBranchNo2 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTBranchNo2 = ibtbranchno2;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTOriginCustomerNo( const basar::Long64& ibtorigincustomerno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTOriginCustomerNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTOriginCustomerNo = ibtorigincustomerno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTOriginOrderNo( const basar::Long64& ibtoriginorderno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTOriginOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTOriginOrderNo = ibtoriginorderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTOriginLineNo( const basar::Long64& ibtoriginlineno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTOriginLineNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTOriginLineNo = ibtoriginlineno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setArtET2( const basar::Long64& artet2 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setArtET2 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ArtET2 = artet2;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPreDeliveryQty( const basar::Long64& predeliveryqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPreDeliveryQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PreDeliveryQty = predeliveryqty;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setChangeDiscount( basar::Decimal& changediscount )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setChangeDiscount );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		changediscount.round(2);
		m_Values.ChangeDiscount = changediscount;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setBonusAbility( basar::Decimal& bonusability )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setBonusAbility );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		bonusability.round(2);
		m_Values.BonusAbility = bonusability;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setChangeDiscountType( const basar::VarString& changediscounttype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setChangeDiscountType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ChangeDiscountType = changediscounttype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setXMLReference( const basar::VarString& xmlreference )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setXMLReference );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.XMLReference = xmlreference;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setCodeBlocage( const basar::VarString& codeblocage )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setCodeBlocage );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.CodeBlocage = codeblocage;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setTaxLevel( const basar::VarString& taxlevel )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setTaxLevel );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.TaxLevel = taxlevel;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setInvoicedPurchaseGroup( const basar::VarString& invoicedpurchasegroup )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setInvoicedPurchaseGroup );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.InvoicedPurchaseGroup = invoicedpurchasegroup;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setOriginalIBTQty( const basar::Long64& originalibtqty )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setOriginalIBTQty );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.OriginalIBTQty = originalibtqty;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPriceType( const basar::Int32 pricetype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPriceType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PriceType = pricetype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPaymentTargetDiscPercentage1( basar::Decimal& paymenttargetdiscpercentage1 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPaymentTargetDiscPercentage1 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		paymenttargetdiscpercentage1.round(2);
		m_Values.PaymentTargetDiscPercentage1 = paymenttargetdiscpercentage1;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPaymentTargetDiscPercentage2( basar::Decimal& paymenttargetdiscpercentage2 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPaymentTargetDiscPercentage2 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		paymenttargetdiscpercentage2.round(2);
		m_Values.PaymentTargetDiscPercentage2 = paymenttargetdiscpercentage2;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPaymentTargetDiscPercentage3( basar::Decimal& paymenttargetdiscpercentage3 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPaymentTargetDiscPercentage3 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		paymenttargetdiscpercentage3.round(2);
		m_Values.PaymentTargetDiscPercentage3 = paymenttargetdiscpercentage3;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPaymentTargetDiscPercentage4( basar::Decimal& paymenttargetdiscpercentage4 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPaymentTargetDiscPercentage4 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		paymenttargetdiscpercentage4.round(2);
		m_Values.PaymentTargetDiscPercentage4 = paymenttargetdiscpercentage4;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPaymentTargetDiscPercentage5( basar::Decimal& paymenttargetdiscpercentage5 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPaymentTargetDiscPercentage5 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		paymenttargetdiscpercentage5.round(2);
		m_Values.PaymentTargetDiscPercentage5 = paymenttargetdiscpercentage5;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPaymentTargetDiscPercentage6( basar::Decimal& paymenttargetdiscpercentage6 )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setPaymentTargetDiscPercentage6 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		paymenttargetdiscpercentage6.round(2);
		m_Values.PaymentTargetDiscPercentage6 = paymenttargetdiscpercentage6;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setInvoicePrice( basar::Decimal& invoiceprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setInvoicePrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		invoiceprice.round(2);
		m_Values.InvoicePrice = invoiceprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setMaxPaymentTarget( const basar::Int32 maxpaymenttarget )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setMaxPaymentTarget );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.MaxPaymentTarget = maxpaymenttarget;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setContLevel( const basar::VarString& contlevel )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setContLevel );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ContLevel = contlevel;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setMaxPharmacySellPrice( basar::Decimal& maxpharmacysellprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setMaxPharmacySellPrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		maxpharmacysellprice.round(2);
		m_Values.MaxPharmacySellPrice = maxpharmacysellprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setSkontoAbility( basar::Decimal& skontoability )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setSkontoAbility );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		skontoability.round(2);
		m_Values.SkontoAbility = skontoability;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setDesiredBatch( const basar::VarString& desiredbatch )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setDesiredBatch );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DesiredBatch = desiredbatch;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setAmedisPriceDifference( basar::Decimal& amedispricedifference )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setAmedisPriceDifference );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		amedispricedifference.round(2);
		m_Values.AmedisPriceDifference = amedispricedifference;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setCalcPharmacySellPrice( basar::Decimal& calcpharmacysellprice )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setCalcPharmacySellPrice );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		calcpharmacysellprice.round(2);
		m_Values.CalcPharmacySellPrice = calcpharmacysellprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setArticleCode( const basar::VarString& articlecode )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setArticleCode );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ArticleCode = articlecode;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setCodeType( const basar::Int32 codetype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setCodeType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.CodeType = codetype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setServiceNo( const basar::Int32 serviceno )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setServiceNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ServiceNo = serviceno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setET7Flags( const basar::Long64& et7flags )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setET7Flags );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ET7Flags = et7flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setMarginCluster( basar::Decimal& margincluster )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setMarginCluster );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		margincluster.round(2);
		m_Values.MarginCluster = margincluster;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setBusinessType( const basar::Int16 businesstype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setBusinessType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.BusinessType = businesstype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setTourIdIbt( const basar::VarString& touridibt )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setTourIdIbt );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.TourIdIbt = touridibt;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setSubDeviceType( const basar::Int16 subdevicetype )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setSubDeviceType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.SubDeviceType = subdevicetype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTWeekday( const basar::Int16 ibtweekday )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setIBTWeekday );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.IBTWeekday = ibtweekday;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setNumberOfDiscountRecords( const basar::Int16 recs )
	{
		METHODNAME_DEF( RecordTypeOrderLine, setNumberOfDiscountRecords );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.NumberOfDiscountRecords = recs;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPurchaseRelevantQuantity( const basar::Long64& value )
	{
		m_Values.PurchaseRelevantQuantity = value;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setOriginalOrderedQuantity( const basar::Long64& value )
	{
		m_Values.OriginalOrderedQuantity = value;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setIBTDeliveryDate( const basar::Long64& value )
	{
		m_Values.IBTDeliveryDate = value;
	}
	//----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeOrderLine::setFixBatch( const bool value )
    {
        if (value)
        {
            m_Values.FixBatch = "J";
        }
        else
        {
            m_Values.FixBatch = "N";
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeOrderLine::setIBTOriginFMDCustomer(const bool value)
    {
        if (value)
        {
            m_Values.IBTOriginFMDCustomer = "1";
        }
        else
        {
            m_Values.IBTOriginFMDCustomer = "0";
        }
    }
    //----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderLine::setPromotionNo(const basar::Int32 promotionno)
	{
		METHODNAME_DEF(RecordTypeOrderLine, setPromotionNo);
		BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

		m_Values.PromotionNo = promotionno;
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
