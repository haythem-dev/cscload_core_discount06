//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeOrderText
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
#include "recordtypeordertext.h"
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
	RecordTypeOrderText::RecordTypeOrderText( const TextType type, libcsc_utils::ICSC_LoggerPtr logger )		
		: RecordTypeBase( "T0", DIRECTION_SEND, logger )		
	{
		METHODNAME_DEF( RecordTypeOrderText, RecordTypeOrderText );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		switch( type )
		{
			case HEADTEXT:
				setRecordTypeName( "T1" );
				break;
			case TAILTEXT:
				setRecordTypeName( "T6" );
				break;
			default:
				throw basar::InvalidParameterException( basar::ExceptInfo( fun, "Wrong TextType specified", __FILE__, __LINE__ ) );				
				break;
		}		

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeOrderText::~RecordTypeOrderText()
	{
		METHODNAME_DEF( RecordTypeOrderText, ~RecordTypeOrderText );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeOrderText::setText( const basar::VarString& text )
	{
		METHODNAME_DEF( RecordTypeOrderText, setText );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Text = text;		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeOrderText::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeOrderText, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, OrderTextFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.Text, OrderTextFormat::LENGTH_TEXT, ss );			
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeOrderText: Formatting exception!", __FILE__, __LINE__ ) ); 			
		}

		return ss.str().c_str();			
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
