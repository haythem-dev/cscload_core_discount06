//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeFormatter
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include "recordtypeformatter.h"
#include <iostream>
#include "formattingexception.h"
#include <classinfo_macros.h>
#include <libbasarcmnutil_decimal.h>

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
	RecordTypeFormatter::RecordTypeFormatter( libcsc_utils::ICSC_LoggerPtr logger )		
		: m_Logger( logger )
	{
		METHODNAME_DEF( RecordTypeFormatter, RecordTypeFormatter );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeFormatter::~RecordTypeFormatter()
	{
		METHODNAME_DEF( RecordTypeFormatter, ~RecordTypeFormatter );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeFormatter::serialize( const basar::Decimal& value, const size_t& length, const size_t& decimalplaces, std::stringstream& out ) 
	{
		int lengthbefore = out.str().length();				

		basar::Decimal val = value;
		if( basar::Decimal(0.0) > val )	val = val * (-1);

		basar::VarString formattedvalue = val.toNonLocString(decimalplaces); // 0.5 => 0.5000
		basar::VarString decSep = "."; 
		formattedvalue.remove(decSep); // 0.5000 => 05000				

		out << std::setw(length) << std::setfill('0') << std::right << formattedvalue.c_str(); // ...000005000												

		if( (out.str().length() - lengthbefore) != length )
		{
			int lengthafter = out.str().length();
			basar::VarString message;
			message.format( "Formatting exception: LengthBefore %d; LengthAfter %d; Length %d; Value: [%s]", lengthbefore, lengthafter, length, formattedvalue.c_str() ); 
			throw FormattingException( basar::ExceptInfo( "serialize Decimal", message.c_str() ) ); 			
		}		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeFormatter::serialize( const basar::VarString& value, const size_t& length, std::stringstream& out )
	{
		int lengthbefore = out.str().length();				

		out << std::setw( static_cast<std::streamsize>(length) ) << std::setfill( ' ' ) << std::left << modifyLength( value, length ).c_str();		

		if( (out.str().length() - lengthbefore) != length )
		{
			int lengthafter = out.str().length();
			basar::VarString message;
			message.format( "Formatting exception: LengthBefore %d; LengthAfter %d; Length %d; Value: [%s]", lengthbefore, lengthafter, length, value.c_str() ); 
			throw FormattingException( basar::ExceptInfo( "serialize VarString", message.c_str() ) ); 			
		}		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeFormatter::serialize( const basar::Long64& value, const size_t& length, std::stringstream& out )
	{
		int lengthbefore = out.str().length();	

		std::stringstream tmp;
		tmp << std::setw( static_cast<std::streamsize>(length) ) << std::setfill( '0' ) <<  std::right << modifyLength(value, length);		
		out << tmp.str().c_str();		

		if( (out.str().length() - lengthbefore) != length )
		{
			int lengthafter = out.str().length();
			basar::VarString message;
			message.format( "Formatting exception: LengthBefore %d; LengthAfter %d; Length %d; Value: [%d]", lengthbefore, lengthafter, length, value ); 
			throw FormattingException( basar::ExceptInfo( "serialize Long64", message.c_str() ) ); 			
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeFormatter::serializeLeft( const basar::Long64& value, const size_t& length, std::stringstream& out )	
	{
		int lengthbefore = out.str().length();		

		std::stringstream tmp;
		tmp << std::setw( static_cast<std::streamsize>(length) ) << std::setfill( '0' )	<< std::left << modifyLength(value, length);
		out << tmp.str().c_str();		

		if( (out.str().length() - lengthbefore) != length )
		{
			int lengthafter = out.str().length();
			basar::VarString message;
			message.format( "Formatting exception: LengthBefore %d; LengthAfter %d; Length %d; Value: [%d]", lengthbefore, lengthafter, length, value ); 
			throw FormattingException( basar::ExceptInfo( "serializeLeft Long64", message.c_str() ) ); 			
		}		
	}
	//----------------------------------------------------------------------------//
	

	//----------------------------------------------------------------------------//
	basar::VarString RecordTypeFormatter::modifyLength( const basar::VarString& value, const size_t& length )
	{	
		if( value.length() > length )
		{
			return value.substr( 0, length );
		}
		else
		{
			return value;
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	basar::Long64 RecordTypeFormatter::modifyLength( const basar::Long64& value, const size_t& length )
	{		
		std::stringstream tmp;
		tmp << value;		
		if( tmp.str().length() > length )
		{
			basar::VarString txt( (tmp.str().substr( tmp.str().length() - length, length )) );
			return txt.stol();
		}
		else
		{
			return value;
		}
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
