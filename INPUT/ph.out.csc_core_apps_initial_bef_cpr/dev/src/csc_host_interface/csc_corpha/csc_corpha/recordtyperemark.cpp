//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeRemark
 *  \author Steffen Heinlein
 *  \date   28.05.2014
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <sstream>
#include <iomanip>
#include "recordtyperemark.h"
#include "recordtypeformatter.h"
#include "formattingexception.h"
#include <classinfo_macros.h>

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
	RecordTypeRemark::RecordTypeRemark( libcsc_utils::ICSC_LoggerPtr logger )		
		: RecordTypeBase( "TX", DIRECTION_SEND, logger )		
	{
		METHODNAME_DEF( RecordTypeRemark, RecordTypeRemark );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeRemark::~RecordTypeRemark()
	{
		METHODNAME_DEF( RecordTypeRemark, ~RecordTypeRemark );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeRemark::setOrderNo( const basar::Long64& orderno )
	{
		m_Values.OrderNo = orderno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeRemark::setPositionNo( const basar::Long64& positionno )
	{
		m_Values.PositionNo = positionno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeRemark::setTextType( const basar::Int32& texttype )
	{
		m_Values.TextType = texttype;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeRemark::setSequentialNo( const basar::Int32& sequentialno )
	{
		m_Values.SequentialNo = sequentialno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeRemark::setText( const basar::VarString& text )
	{		
		m_Values.Text = text;		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeRemark::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeRemark::, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		
		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, RemarkFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.OrderNo, RemarkFormat::LENGTH_ORDERNO, ss );
			RecordTypeFormatter::serialize( m_Values.PositionNo, RemarkFormat::LENGTH_POSITIONNO, ss );
			RecordTypeFormatter::serialize( m_Values.TextType, RemarkFormat::LENGTH_TEXTTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.SequentialNo, RemarkFormat::LENGTH_SEQUENTIALNO, ss );
			RecordTypeFormatter::serialize( m_Values.Text, RemarkFormat::LENGTH_TEXT, ss );			
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeRemark: Formatting exception!", __FILE__, __LINE__ ) ); 			
		}

		return ss.str().c_str();			
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod
