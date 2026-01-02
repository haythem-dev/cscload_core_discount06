//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeOrderHeader
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "recordtypeorderheader.h"
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
	RecordTypeOrderHeader::RecordTypeOrderHeader( libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "A1", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF( RecordTypeOrderHeader, RecordTypeOrderHeader );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeOrderHeader::~RecordTypeOrderHeader()
	{
		METHODNAME_DEF( RecordTypeOrderHeader, ~RecordTypeOrderHeader );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeOrderHeader::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeOrderHeader, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, OrderHeaderFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.Mandant, OrderHeaderFormat::LENGTH_MANDANT, ss );
			RecordTypeFormatter::serialize( m_Values.OrderNo, OrderHeaderFormat::LENGTH_ORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.CustomerNo, OrderHeaderFormat::LENGTH_CUSTOMERNO, ss );
			RecordTypeFormatter::serialize( m_Values.TerminalId, OrderHeaderFormat::LENGTH_TERMINALID, ss );
			RecordTypeFormatter::serialize( m_Values.TourId, OrderHeaderFormat::LENGTH_TOURID, ss );
			RecordTypeFormatter::serialize( m_Values.TourIdOld, OrderHeaderFormat::LENGTH_TOURIDOLD, ss );
			RecordTypeFormatter::serialize( m_Values.UserId, OrderHeaderFormat::LENGTH_USERID, ss );
			RecordTypeFormatter::serialize( m_Values.BranchNo, OrderHeaderFormat::LENGTH_BRANCHNO, ss );
			RecordTypeFormatter::serialize( m_Values.ET1Flags, OrderHeaderFormat::LENGTH_ET1FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET2Flags, OrderHeaderFormat::LENGTH_ET2FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET3Flags, OrderHeaderFormat::LENGTH_ET3FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET4Flags, OrderHeaderFormat::LENGTH_ET4FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.OrderType, OrderHeaderFormat::LENGTH_ORDERTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.PickingType, OrderHeaderFormat::LENGTH_PICKINGTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.BookingType, OrderHeaderFormat::LENGTH_BOOKINGTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.ValidationDate, OrderHeaderFormat::LENGTH_VALIDATIONDATE, ss );
			RecordTypeFormatter::serialize( m_Values.OrderValue, OrderHeaderFormat::LENGTH_ORDERVALUE, OrderHeaderFormat::DECPLACES_ORDERVALUE, ss );
			RecordTypeFormatter::serialize( m_Values.DeliveryValue, OrderHeaderFormat::LENGTH_DELIVERYVALUE, OrderHeaderFormat::DECPLACES_DELIVERYVALUE, ss );
			RecordTypeFormatter::serialize( m_Values.AvgLineValue, OrderHeaderFormat::LENGTH_AVGLINEVALUE, OrderHeaderFormat::DECPLACES_AVGLINEVALUE, ss );
			RecordTypeFormatter::serialize( m_Values.Lines, OrderHeaderFormat::LENGTH_LINES, ss );
			RecordTypeFormatter::serialize( m_Values.LinesNoCalc, OrderHeaderFormat::LENGTH_LINESNOCALC, ss );
			RecordTypeFormatter::serialize( m_Values.LinesDialUp, OrderHeaderFormat::LENGTH_LINESDIALUP, ss );
			RecordTypeFormatter::serialize( m_Values.LinesDialUpErrors, OrderHeaderFormat::LENGTH_LINESDIALUPERRORS, ss );
			RecordTypeFormatter::serialize( m_Values.LinesAlphaTxt, OrderHeaderFormat::LENGTH_LINESALPHATXT, ss );
			RecordTypeFormatter::serialize( m_Values.LinesNarcotics, OrderHeaderFormat::LENGTH_LINESNARCOTICS, ss );
			RecordTypeFormatter::serialize( m_Values.CashDiscountPercentage, OrderHeaderFormat::LENGTH_CASHDISCOUNTPERCENTAGE, OrderHeaderFormat::DECPLACES_CASHDISCOUNTPERCENTAGE, ss );
			RecordTypeFormatter::serialize( m_Values.Origin, OrderHeaderFormat::LENGTH_ORIGIN, ss );
			RecordTypeFormatter::serialize( m_Values.OriginBranchNo, OrderHeaderFormat::LENGTH_ORIGINBRANCHNO, ss );
			RecordTypeFormatter::serialize( m_Values.NextTourId, OrderHeaderFormat::LENGTH_NEXTTOURID, ss );
			RecordTypeFormatter::serialize( m_Values.LastTourId, OrderHeaderFormat::LENGTH_LASTTOURID, ss );
			RecordTypeFormatter::serialize( m_Values.DialUpOrderNo, OrderHeaderFormat::LENGTH_DIALUPORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.DialUpDeviceType, OrderHeaderFormat::LENGTH_DIALUPDEVICETYPE, ss );
			RecordTypeFormatter::serialize( m_Values.Hint, OrderHeaderFormat::LENGTH_HINT, ss );
			RecordTypeFormatter::serialize( m_Values.ParentBranchFlag, OrderHeaderFormat::LENGTH_PARENTBRANCHFLAG, ss );
			RecordTypeFormatter::serialize( m_Values.BatchOrderNo, OrderHeaderFormat::LENGTH_BATCHORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.SubOrderType, OrderHeaderFormat::LENGTH_SUBORDERTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentTerm, OrderHeaderFormat::LENGTH_PAYMENTTERM, ss );
			RecordTypeFormatter::serialize( m_Values.ValueMonthManual, OrderHeaderFormat::LENGTH_VALUEMONTHMANUAL, ss );
			RecordTypeFormatter::serialize( m_Values.ValueMonthAuto, OrderHeaderFormat::LENGTH_VALUEMONTHAUTO, ss );
			RecordTypeFormatter::serialize( m_Values.PartialOrder, OrderHeaderFormat::LENGTH_PARTIALORDER, ss );
			RecordTypeFormatter::serialize( m_Values.TenderNo, OrderHeaderFormat::LENGTH_TENDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.ContractNo, OrderHeaderFormat::LENGTH_CONTRACTNO, ss );
			RecordTypeFormatter::serialize( m_Values.ShipmentDate, OrderHeaderFormat::LENGTH_SHIPMENTDATE, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountAccFromDate, OrderHeaderFormat::LENGTH_DISCOUNTACCFROMDATE, ss );
			RecordTypeFormatter::serialize( m_Values.DiscountAccToDate, OrderHeaderFormat::LENGTH_DISCOUNTACCTODATE, ss );
			RecordTypeFormatter::serialize( m_Values.ChainMember, OrderHeaderFormat::LENGTH_CHAINMEMBER, ss );
			RecordTypeFormatter::serialize( m_Values.NarcoticsFormNo, OrderHeaderFormat::LENGTH_NARCOTICSFORMNO, ss );
			RecordTypeFormatter::serialize( m_Values.ValueDateDays, OrderHeaderFormat::LENGTH_VALUEDATEDAYS, ss );
			RecordTypeFormatter::serialize( m_Values.PrintPriceProposal, OrderHeaderFormat::LENGTH_PRINTPRICEPROPOSAL, ss );
			RecordTypeFormatter::serialize( m_Values.DeductionPharmacyPurchasePrice, OrderHeaderFormat::LENGTH_DEDUCTIONPHARMACYPURCHASEPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.DeductionPharmacySellPrice, OrderHeaderFormat::LENGTH_DEDUCTIONPHARMACYSELLPRICE, ss );
			RecordTypeFormatter::serialize( m_Values.DeductionColumnNo, OrderHeaderFormat::LENGTH_DEDUCTIONCOLUMNNO, ss );
			RecordTypeFormatter::serialize( m_Values.EmailInvoice, OrderHeaderFormat::LENGTH_EMAILINVOICE, ss );
			RecordTypeFormatter::serialize( m_Values.ET5Flags, OrderHeaderFormat::LENGTH_ET5FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.ET6Flags, OrderHeaderFormat::LENGTH_ET6FLAGS, ss );
			RecordTypeFormatter::serialize( m_Values.XMLReference, OrderHeaderFormat::LENGTH_XMLREFERENCE, ss );
			RecordTypeFormatter::serialize( m_Values.PseudoInvoiceNo, OrderHeaderFormat::LENGTH_PSEUDOINVOICENO, ss );
			RecordTypeFormatter::serialize( m_Values.MSV3Order, OrderHeaderFormat::LENGTH_MSV3ORDER, ss );
			RecordTypeFormatter::serialize( m_Values.TenderType, OrderHeaderFormat::LENGTH_TENDERTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.NumberOfDiscountRecords, OrderHeaderFormat::LENGTH_NUMBEROFDISCOUNTRECORDS, ss );
			RecordTypeFormatter::serialize( m_Values.PaymentType, OrderHeaderFormat::LENGTH_PAYMENTTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.PurchaseOrderNo, OrderHeaderFormat::LENGTH_PURCHASEORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.ExpressDeliveryCharge, OrderHeaderFormat::LENGTH_EXPRESSDELIVERYCHARGE, ss );
            RecordTypeFormatter::serialize( m_Values.ProformaOrderDate, OrderHeaderFormat::LENGTH_PROFORMAORDERDATE, ss );
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeOrderHeader: Formatting exception!", __FILE__, __LINE__ ) );
		}

		return ss.str().c_str();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPurchaseOrderNo( const basar::Int32 value )
	{
		m_Values.PurchaseOrderNo = value;
	}
	//----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeOrderHeader::setProformaOrderDate(const basar::Long64& value)
    {
        m_Values.ProformaOrderDate = value;
    }
    //----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setExpressDeliveryCharge( const basar::VarString& value )
	{
		m_Values.ExpressDeliveryCharge = value;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPaymentType( const basar::VarString& value )
	{
		m_Values.PaymentType = value;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setMandant( const basar::Int32 mandant )
	{
		m_Values.Mandant = mandant;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setOrderNo( const basar::Long64& orderno )
	{
		m_Values.OrderNo = orderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setCustomerNo( const basar::Long64& customerno )
	{
		m_Values.CustomerNo = customerno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setTerminalId( const basar::VarString& terminalid )
	{
		m_Values.TerminalId = terminalid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setTourId( const basar::VarString& tourid )
	{
		m_Values.TourId = tourid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setTourIdOld( const basar::VarString& touridold )
	{
		m_Values.TourIdOld = touridold;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setUserId( const basar::Long64& userid )
	{
		m_Values.UserId = userid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setBranchNo( const basar::Int32 branchno )
	{
		m_Values.BranchNo = branchno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setET1Flags( const basar::Long64& et1flags )
	{
		m_Values.ET1Flags = et1flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setET2Flags( const basar::Long64& et2flags )
	{
		m_Values.ET2Flags = et2flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setET3Flags( const basar::Long64& et3flags )
	{
		m_Values.ET3Flags = et3flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setET4Flags( const basar::Long64& et4flags )
	{
		m_Values.ET4Flags = et4flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setOrderType( const basar::VarString& ordertype )
	{
		m_Values.OrderType = ordertype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPickingType( const basar::VarString& pickingtype )
	{
		m_Values.PickingType = pickingtype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setBookingType( const basar::VarString& bookingtype )
	{
		m_Values.BookingType = bookingtype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setValidationDate( const basar::Long64& validationdate )
	{
		m_Values.ValidationDate = validationdate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setOrderValue( basar::Decimal& ordervalue )
	{
		ordervalue.round(2);
		m_Values.OrderValue = ordervalue;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDeliveryValue( basar::Decimal& deliveryvalue )
	{
		deliveryvalue.round(2);
		m_Values.DeliveryValue = deliveryvalue;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setAvgLineValue( basar::Decimal& avglinevalue )
	{
		avglinevalue.round(2);
		m_Values.AvgLineValue = avglinevalue;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLines( const basar::Long64& lines )
	{
		m_Values.Lines = lines;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLinesNoCalc( const basar::Long64& linesnocalc )
	{
		m_Values.LinesNoCalc = linesnocalc;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLinesDialUp( const basar::Long64& linesdialup )
	{
		m_Values.LinesDialUp = linesdialup;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLinesDialUpErrors( const basar::Long64& linesdialuperrors )
	{
		m_Values.LinesDialUpErrors = linesdialuperrors;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLinesAlphaTxt( const basar::Long64& linesalphatxt )
	{
		m_Values.LinesAlphaTxt = linesalphatxt;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLinesNarcotics( const basar::Long64& linesnarcotics )
	{
		m_Values.LinesNarcotics = linesnarcotics;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setCashDiscountPercentage( basar::Decimal& cashdiscountpercentage )
	{
		cashdiscountpercentage.round(2);
		m_Values.CashDiscountPercentage = cashdiscountpercentage;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setOrigin( const basar::VarString& origin )
	{
		m_Values.Origin = origin;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setOriginBranchNo( const basar::Int32 originbranchno )
	{
		m_Values.OriginBranchNo = originbranchno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setNextTourId( const basar::VarString& nexttourid )
	{
		m_Values.NextTourId = nexttourid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setLastTourId( const basar::VarString& lasttourid )
	{
		m_Values.LastTourId = lasttourid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDialUpOrderNo( const basar::Long64& dialuporderno )
	{
		m_Values.DialUpOrderNo = dialuporderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDialUpDeviceType( const basar::VarString& dialupdevicetype )
	{
		m_Values.DialUpDeviceType = dialupdevicetype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setHint( const basar::VarString& hint )
	{
		m_Values.Hint = hint;
		//m_Values.Hint.cleanchar(); // I18nString
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setParentBranchFlag( const basar::VarString& parentbranchflag )
	{
		m_Values.ParentBranchFlag = parentbranchflag;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setBatchOrderNo( const basar::Long64& batchorderno )
	{
		m_Values.BatchOrderNo = batchorderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setSubOrderType( const basar::VarString& subordertype )
	{
		m_Values.SubOrderType = subordertype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPaymentTerm( const basar::VarString& paymentterm )
	{
		m_Values.PaymentTerm = paymentterm;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setValueMonthManual( const basar::Int32 valuemonthmanual )
	{
		m_Values.ValueMonthManual = valuemonthmanual;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setValueMonthAuto( const basar::Int32 valuemonthauto )
	{
		m_Values.ValueMonthAuto = valuemonthauto;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPartialOrder( const basar::Int32 partialorder )
	{
		m_Values.PartialOrder = partialorder;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setTenderNo( const basar::Long64& tenderno )
	{
		m_Values.TenderNo = tenderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setContractNo( const basar::VarString& contractno )
	{
		m_Values.ContractNo = contractno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setShipmentDate( const basar::Long64& shipmentdate )
	{
		m_Values.ShipmentDate = shipmentdate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDiscountAccFromDate( const basar::Long64& discountaccfromdate )
	{
		m_Values.DiscountAccFromDate = discountaccfromdate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDiscountAccToDate( const basar::Long64& discountacctodate )
	{
		m_Values.DiscountAccToDate = discountacctodate;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setChainMember( const basar::VarString& chainmember )
	{
		m_Values.ChainMember = chainmember;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setNarcoticsFormNo( const basar::VarString& narcoticsformno )
	{
		m_Values.NarcoticsFormNo = narcoticsformno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setValueDateDays( const basar::Long64& valuedatedays )
	{
		m_Values.ValueDateDays = valuedatedays;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPrintPriceProposal( const basar::VarString& printpriceproposal )
	{
		m_Values.PrintPriceProposal = printpriceproposal;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDeductionPharmacyPurchasePrice( const basar::VarString& deductionpharmacypurchaseprice )
	{
		m_Values.DeductionPharmacyPurchasePrice = deductionpharmacypurchaseprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDeductionPharmacySellPrice( const basar::VarString& deductionpharmacysellprice )
	{
		m_Values.DeductionPharmacySellPrice = deductionpharmacysellprice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setDeductionColumnNo( const basar::VarString& deductioncolumnno )
	{
		m_Values.DeductionColumnNo = deductioncolumnno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setEmailInvoice( const basar::VarString& emailinvoice )
	{
		m_Values.EmailInvoice = emailinvoice;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setET5Flags( const basar::Long64& et5flags )
	{
		m_Values.ET5Flags = et5flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setET6Flags( const basar::Long64& et6flags )
	{
		m_Values.ET6Flags = et6flags;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setXMLReference( const basar::VarString& xmlreference )
	{
		m_Values.XMLReference = xmlreference;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setPseudoInvoiceNo( const basar::Int32 pseudoinvoiceno )
	{
		m_Values.PseudoInvoiceNo = pseudoinvoiceno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setMSV3Order( const basar::VarString& msv3order )
	{
		m_Values.MSV3Order = msv3order;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setTenderType( const basar::Int32 tendertype )
	{
		m_Values.TenderType = tendertype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderHeader::setNumberOfDiscountRecords( const basar::Int16 recs )
	{
		m_Values.NumberOfDiscountRecords = recs;
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
