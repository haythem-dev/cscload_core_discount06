//--------------------------------------------------------------------------------------------------//
/*! \file		pdx040remoteprocedure.cpp
*   \brief		definition for PDX040 remote procedure
*   \author		Steffen Heinlein
*   \date		22.08.2012
*/
//--------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <sstream>
#include <iomanip>
#include "pdx040remoteprocedure.h"
#include "pdx040remoteprocedure_definitions.h"
#include "remoteprocedureresult.h"

using namespace std;

namespace domMod
{
namespace corpha
{

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX040RemoteProcedure::getResultMessage( const basar::Int32 returncode ) const
	{
		METHODNAME_DEF( PDX040RemoteProcedure, getResultMessage )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::VarString retval("");		
		switch( returncode )
		{
			case 1001: retval = PDX040MESSAGE1001; break;
			case 1002: retval = PDX040MESSAGE1002; break;
			case 1000: retval = PDX040MESSAGE1000; break;
			case 2000: retval = PDX040MESSAGE2000; break;			
			case 3100: retval = PDX040MESSAGE3100; break;
			case 3200: retval = PDX040MESSAGE3200; break;
			case 4100: retval = PDX040MESSAGE4100; break;		
			case 4200: retval = PDX040MESSAGE4200; break;
			case 5000: retval = PDX040MESSAGE5000; break;
			case 5100: retval = PDX040MESSAGE5100; break;
			case 9000: retval = PDX040MESSAGE9000; break;
			case 9100: retval = PDX040MESSAGE9100; break;
			case 9200: retval = PDX040MESSAGE9200; break;
			case 9300: retval = PDX040MESSAGE9300; break;
			case 9400: retval = PDX040MESSAGE9400; break;
			case 9500: retval = PDX040MESSAGE9500; break;
			case 9600: retval = PDX040MESSAGE9600; break;
			case 9800: retval = PDX040MESSAGE9800; break;																						
			case 0:		retval = "";				break;
			default:	retval.format( "%d Unspecified Error.", returncode ); break;
		}		

		return retval;
	}

	//--------------------------------------------------------------------------------------------------//
	const ::libcsc_utils::RemoteProcedureResult PDX040RemoteProcedure::checkResult() const
	{		
		METHODNAME_DEF( PDX040RemoteProcedure, checkResult )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		
		if( 0 != m_CDX040CommArea.ReturnCode )
		{
			basar::VarString logmessage("");
			logmessage.format( "Time %d Branch %d OrderNo %d => PDX040 RC not 0: %d Message: %s", m_CDX040CommArea.Time, m_CDX040CommArea.ProcedureBranchNo, m_CDX040CommArea.CustomerOrderNo, m_CDX040CommArea.ReturnCode, getResultMessage( m_CDX040CommArea.ReturnCode ).c_str()  );
			m_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmessage );								
			// !!! no return! continue to avoid loop !!!
			//return ::libcsc_utils::RemoteProcedureResult( false, 0, getResultMessage( m_CDX040CommArea.ReturnCode ) );
		}
		
		return ::libcsc_utils::RemoteProcedureResult( true, 0 );	
	}

	//--------------------------------------------------------------------------------------------------//
	PDX040RemoteProcedure::PDX040RemoteProcedure( const basar::VarString &applicationname, const basar::Long64 cscorderno, const basar::Int16 branchno, const basar::Long64 time, libcsc_utils::ICSC_LoggerPtr logger )
		: m_BranchNo( branchno ), m_Logger( logger )
	{				
		METHODNAME_DEF( PDX040RemoteProcedure, PDX040RemoteProcedure )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_CDX040CommArea.CommAreaLength = CDX040::CDX040CommArea::LENGTH_TOTAL;		
		m_CDX040CommArea.CallID = applicationname;
		m_CDX040CommArea.ReturnCode = 0;
		m_CDX040CommArea.CustomerOrderNo = cscorderno;
		m_CDX040CommArea.PharmosOrderNo = 0;		
		m_CDX040CommArea.ProcedureBranchNo = branchno;
		m_CDX040CommArea.Time = time;
		m_CDX040CommArea.VersionID = 1;
		m_CDX040CommArea.Filler = " ";				
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX040RemoteProcedure::getProcedureName() const
	{
		METHODNAME_DEF( PDX040RemoteProcedure, getProcedureName )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		return PROCEDURENAME;
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX040RemoteProcedure::serializeQuery() const
	{
		METHODNAME_DEF( PDX040RemoteProcedure, serializeQuery )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		stringstream ss;
		ss	<< setw( CDX040::CDX040CommArea::LENGTH_COMMAREA )				<< setfill('0') << right << m_CDX040CommArea.CommAreaLength
			<< setw( CDX040::CDX040CommArea::LENGTH_CALLID )				<< setfill(' ') << left  << m_CDX040CommArea.CallID			
			<< setw( CDX040::CDX040CommArea::LENGTH_RETURNCODE )			<< setfill('0') << right << m_CDX040CommArea.ReturnCode
			<< setw( CDX040::CDX040CommArea::LENGTH_CUSTOMERORDERNO )		<< setfill('0') << right << m_CDX040CommArea.CustomerOrderNo
			<< setw( CDX040::CDX040CommArea::LENGTH_PHARMOSORDERNO )		<< setfill('0') << right << m_CDX040CommArea.PharmosOrderNo
			<< setw( CDX040::CDX040CommArea::LENGTH_PROCFIL )				<< setfill('0') << right << m_CDX040CommArea.ProcedureBranchNo
			<< setw( CDX040::CDX040CommArea::LENGTH_TIME )					<< setfill('0') << right << m_CDX040CommArea.Time
			<< setw( CDX040::CDX040CommArea::LENGTH_VERSIONID )				<< setfill('0') << right << m_CDX040CommArea.VersionID
			<< setw( CDX040::CDX040CommArea::LENGTH_FILLER )				<< setfill(' ') << left	 << m_CDX040CommArea.Filler;
		if( ss.str().length() > (CDX040::CDX040CommArea::LENGTH_TOTAL + CDX040::CDX040CommArea::LENGTH_COMMAREA) )
		{
			ss.str() = ss.str().substr(0, CDX040::CDX040CommArea::LENGTH_TOTAL);
		}
		return ss.str().c_str();
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX040RemoteProcedure::serializeForLogging() const
	{
		METHODNAME_DEF( PDX040RemoteProcedure, serializeForLogging )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		stringstream ss;
		ss	<< " CommAreaLength: "
			<< setw( CDX040::CDX040CommArea::LENGTH_COMMAREA )				<< setfill('0') << right << m_CDX040CommArea.CommAreaLength
			<< " | CallID: "
			<< setw( CDX040::CDX040CommArea::LENGTH_CALLID )				<< setfill(' ') << left  << m_CDX040CommArea.CallID
			<< " | ReturnCode: "
			<< setw( CDX040::CDX040CommArea::LENGTH_RETURNCODE )			<< setfill('0') << right << m_CDX040CommArea.ReturnCode
			<< " | CustomerOrderNo: "
			<< setw( CDX040::CDX040CommArea::LENGTH_CUSTOMERORDERNO )       << setfill('0') << right << m_CDX040CommArea.CustomerOrderNo
			<< " | PharmosOrderNo: "
			<< setw( CDX040::CDX040CommArea::LENGTH_PHARMOSORDERNO )       	<< setfill('0') << right << m_CDX040CommArea.PharmosOrderNo	
			<< " | ProcFil: "
			<< setw( CDX040::CDX040CommArea::LENGTH_PROCFIL )			   	<< setfill('0') << right << m_CDX040CommArea.ProcedureBranchNo
			<< " | Time: "
			<< setw( CDX040::CDX040CommArea::LENGTH_TIME )					<< setfill('0') << right << m_CDX040CommArea.Time
			<< " | Version: "
			<< setw( CDX040::CDX040CommArea::LENGTH_VERSIONID )				<< setfill('0') << right << m_CDX040CommArea.VersionID
			<< " | Filler: "
			<< setw( CDX040::CDX040CommArea::LENGTH_FILLER)					<< setfill(' ') << left	 << m_CDX040CommArea.Filler;
		if( ss.str().length() > (CDX040::CDX040CommArea::LENGTH_TOTAL + CDX040::CDX040CommArea::LENGTH_COMMAREA) )
		{
			ss.str() = ss.str().substr(0, CDX040::CDX040CommArea::LENGTH_TOTAL);
		}
		return ss.str().c_str();
	}

	//--------------------------------------------------------------------------------------------------//
	void PDX040RemoteProcedure::deserializeResult( const basar::VarString &result )
	{
		METHODNAME_DEF( PDX040RemoteProcedure, deserializeResult )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		size_t currentposition = 0;	
		
		m_CDX040CommArea.CommAreaLength = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_COMMAREA ).stol();
		currentposition += CDX040::CDX040CommArea::LENGTH_COMMAREA;

		m_CDX040CommArea.CallID = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_CALLID);
		currentposition += CDX040::CDX040CommArea::LENGTH_CALLID;

		m_CDX040CommArea.ReturnCode = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_RETURNCODE).stol();
		currentposition += CDX040::CDX040CommArea::LENGTH_RETURNCODE;

		m_CDX040CommArea.CustomerOrderNo = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_CUSTOMERORDERNO).stol();
		currentposition += CDX040::CDX040CommArea::LENGTH_CUSTOMERORDERNO;
		
		m_CDX040CommArea.PharmosOrderNo = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_PHARMOSORDERNO).stol();
		currentposition += CDX040::CDX040CommArea::LENGTH_PHARMOSORDERNO;				

		m_CDX040CommArea.ProcedureBranchNo = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_PROCFIL).stol();
		currentposition += CDX040::CDX040CommArea::LENGTH_PROCFIL;				

		m_CDX040CommArea.Time = result.substr(currentposition, CDX040::CDX040CommArea::LENGTH_TIME).stol();
		currentposition += CDX040::CDX040CommArea::LENGTH_TIME;
	}

}
}
