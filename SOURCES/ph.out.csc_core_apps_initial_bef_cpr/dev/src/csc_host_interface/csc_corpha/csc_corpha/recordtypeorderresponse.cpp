//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeOrderResponse
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <sstream>
#include <iomanip>
#include <classinfo_macros.h>

#include "recordtypeorderresponse.h"

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
	RecordTypeOrderResponse::RecordTypeOrderResponse( const basar::VarString& serializedbuffer, libcsc_utils::ICSC_LoggerPtr logger )		
		: RecordTypeBase( "", DIRECTION_RECEIVE, logger ), m_SerializedBuffer( serializedbuffer )			
	{
		METHODNAME_DEF( RecordTypeOrderResponse, RecordTypeOrderResponse );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::VarString rectype = m_SerializedBuffer.substr( 0, LENGTH_RECORDTYPE );		
		setRecordTypeName( rectype );
		m_Type = mapRecordType( rectype );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeOrderResponse::~RecordTypeOrderResponse()
	{
		METHODNAME_DEF( RecordTypeOrderResponse, ~RecordTypeOrderResponse );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//	

	//----------------------------------------------------------------------------//	
	RecordType RecordTypeOrderResponse::mapRecordType( const basar::VarString& rectype )
	{
		METHODNAME_DEF( RecordTypeOrderResponse, mapRecordType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		static const basar::VarString	TYPE_A1 = "A1";	
		static const basar::VarString	TYPE_S1 = "S1";	
		static const basar::VarString	TYPE_P1 = "P1";	

		if     ( TYPE_A1 == rectype )	return A1;
		else if( TYPE_S1 == rectype )	return S1;
		else if( TYPE_P1 == rectype )	return P1;
		else							return UNKNOWN;
	}
	//----------------------------------------------------------------------------//	

	//----------------------------------------------------------------------------//	
	const OrderResponseValues RecordTypeOrderResponse::doDeserialize() const	
	{
		METHODNAME_DEF( RecordTypeOrderResponse, doDeserialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		OrderResponseValues retval;

		size_t currentposition = 0;	

		retval.Type = m_Type;
		retval.RecType = m_SerializedBuffer.substr( currentposition, LENGTH_RECORDTYPE );
		currentposition	+= LENGTH_RECORDTYPE;
		
		switch( m_Type )
		{
			case A1:
			case S1:				
				retval.CSCOrderNo		= m_SerializedBuffer.substr( currentposition, OrderResponseFormat::LENGTH_CSCORDERNO ).stol();
										currentposition	+= OrderResponseFormat::LENGTH_CSCORDERNO;
				retval.PharmosOrderNo	= m_SerializedBuffer.substr( currentposition, OrderResponseFormat::LENGTH_PHARMOSORDERNO ).stol();
										currentposition += OrderResponseFormat::LENGTH_PHARMOSORDERNO;
				retval.Status			= m_SerializedBuffer.substr( currentposition, OrderResponseFormat::LENGTH_STATUS ).stol();
										currentposition += OrderResponseFormat::LENGTH_STATUS;								
				break;

			case P1:
				retval.CSCOrderNo		= m_SerializedBuffer.substr( currentposition, OrderLineResponseFormat::LENGTH_ORDERNO ).stol();
										currentposition	+= OrderLineResponseFormat::LENGTH_ORDERNO;
				retval.CSCOrderLineNo	= m_SerializedBuffer.substr( currentposition, OrderLineResponseFormat::LENGTH_ORDERLINENO ).stol();
										currentposition += OrderLineResponseFormat::LENGTH_ORDERLINENO;
				retval.Status			= m_SerializedBuffer.substr( currentposition, OrderLineResponseFormat::LENGTH_STATUS ).stol(); 
										currentposition += OrderLineResponseFormat::LENGTH_STATUS;
				retval.DeliveryQty		= m_SerializedBuffer.substr( currentposition, OrderLineResponseFormat::LENGTH_DELIVERYQTY ).stol();
										currentposition += OrderLineResponseFormat::LENGTH_DELIVERYQTY;
				break;

			default:
				retval.init();
		}

		return retval;
	}
	//----------------------------------------------------------------------------//	

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
