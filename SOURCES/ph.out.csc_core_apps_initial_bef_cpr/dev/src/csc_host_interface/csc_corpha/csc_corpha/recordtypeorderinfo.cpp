//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeOrderInfo
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

#include "recordtypeorderinfo.h"
#include "recordtypeformatter.h"
#include "formattingexception.h"

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
	RecordTypeOrderInfo::RecordTypeOrderInfo( libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "AI", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, RecordTypeOrderInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeOrderInfo::~RecordTypeOrderInfo()
	{
		METHODNAME_DEF( RecordTypeOrderInfo, ~RecordTypeOrderInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setCustomerOrderNo( const basar::Long64& customerorderno )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setCustomerOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.CustomerOrderNo = customerorderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setPharmacyOrderNo( const basar::VarString& pharmacyorderno )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setPharmacyOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PharmacyOrderNo = pharmacyorderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setInternalCustomerNo( const basar::Long64& internalcustomerno )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setInternalCustomerNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.InternalCustomerNo = internalcustomerno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setPharmacyTour( const basar::VarString& pharmacytour )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setPharmacyTour );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PharmacyTour = pharmacytour;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setShipmentType( const basar::VarString& shipmenttype )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setShipmentType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ShipmentType = shipmenttype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setProcessNo( const basar::Long64& processno )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setProcessNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.ProcessNo = processno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setEDIDeliveryNote( const basar::VarString& edideliverynote )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setEDIDeliveryNote );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.EDIDeliveryNote = edideliverynote;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderInfo::setBatchOrderNo( const basar::Long64& batchorderno )
	{
		METHODNAME_DEF( RecordTypeOrderInfo, setBatchOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.BatchOrderNo = batchorderno;
	}
	//----------------------------------------------------------------------------//	

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeOrderInfo::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeOrderInfo, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, OrderInfoFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.CustomerOrderNo, OrderInfoFormat::LENGTH_CUSTOMERORDERNO, ss );		
			RecordTypeFormatter::serialize( m_Values.PharmacyOrderNo, OrderInfoFormat::LENGTH_PHARMACYORDERNO_LEGACY, ss ); 		
			RecordTypeFormatter::serialize( m_Values.InternalCustomerNo, OrderInfoFormat::LENGTH_INTERNALCUSTOMERNO, ss );		
			RecordTypeFormatter::serialize( m_Values.PharmacyTour, OrderInfoFormat::LENGTH_PHARMACYTOUR, ss );			
			RecordTypeFormatter::serialize( m_Values.ShipmentType, OrderInfoFormat::LENGTH_SHIPMENTTYPE, ss );			
			RecordTypeFormatter::serialize( m_Values.ProcessNo, OrderInfoFormat::LENGTH_PROCESSNO, ss );				
			RecordTypeFormatter::serialize( m_Values.EDIDeliveryNote, OrderInfoFormat::LENGTH_EDIDELIVERYNOTE, ss );		
			RecordTypeFormatter::serialize( m_Values.BatchOrderNo, OrderInfoFormat::LENGTH_BATCHORDERNO, ss );			
			RecordTypeFormatter::serialize( m_Values.PharmacyOrderNo, OrderInfoFormat::LENGTH_PHARMACYORDERNO, ss );
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeOrderInfo: Formatting exception!", __FILE__, __LINE__ ) ); 			
		}

		return ss.str().c_str();			
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
