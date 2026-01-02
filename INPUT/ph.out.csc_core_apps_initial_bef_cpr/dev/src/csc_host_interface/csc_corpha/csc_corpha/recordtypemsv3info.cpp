//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeMSV3Info
 *  \author Steffen Heinlein
 *  \date   08.08.2013
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <sstream>
#include <iomanip>
#include <classinfo_macros.h>

#include "recordtypemsv3info.h"
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
	RecordTypeMSV3Info::RecordTypeMSV3Info( const MSV3InfoTextType& texttype, libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "M3", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF( RecordTypeMSV3Info, RecordTypeMSV3Info );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
		setTextType(texttype);
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeMSV3Info::~RecordTypeMSV3Info()
	{
		METHODNAME_DEF( RecordTypeMSV3Info, ~RecordTypeMSV3Info );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//
				
	//----------------------------------------------------------------------------//
	void RecordTypeMSV3Info::setKSCOrderNo( const basar::Long64& kscorderno )
	{
		METHODNAME_DEF( RecordTypeMSV3Info, setKSCOrderNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		m_Values.KSCOrderNo = kscorderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeMSV3Info::setTextType( const MSV3InfoTextType& texttype )		
	{
		METHODNAME_DEF( RecordTypeMSV3Info, setTextType );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		static const basar::VarString TEXTTYPE_ORDERLABEL( "A" );
		static const basar::VarString TEXTTYPE_PACKAGELABEL( "G" );

		if( ORDERLABEL == texttype )
		{
			m_Values.TextType = TEXTTYPE_ORDERLABEL;
		}
		else if( PACKAGELABEL == texttype )
		{
			m_Values.TextType = TEXTTYPE_PACKAGELABEL;
		}		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeMSV3Info::setSeqNo( const basar::Long64& seqno )
	{
		METHODNAME_DEF( RecordTypeMSV3Info, setSeqNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		m_Values.SeqNo = seqno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeMSV3Info::setText( const basar::VarString& text )
	{
		METHODNAME_DEF( RecordTypeMSV3Info, setText );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		m_Values.Text = text;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeMSV3Info::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeMSV3Info, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		stringstream ss;

		try
		{			
			RecordTypeFormatter::serialize( m_Values.RecordType, MSV3InfoFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.KSCOrderNo, MSV3InfoFormat::LENGTH_KSCODERNO, ss );
			RecordTypeFormatter::serialize( m_Values.TextType, MSV3InfoFormat::LENGTH_TEXTTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.SeqNo, MSV3InfoFormat::LENGTH_SEQNO, ss );
			RecordTypeFormatter::serialize( m_Values.Text, MSV3InfoFormat::LENGTH_TEXT, ss );
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeMSV3Info: Formatting exception!", __FILE__, __LINE__ ) ); 			
		}

		return ss.str().c_str();			
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
