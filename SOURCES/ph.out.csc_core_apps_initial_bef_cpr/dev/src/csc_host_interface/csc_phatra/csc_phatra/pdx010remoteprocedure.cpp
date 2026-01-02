//--------------------------------------------------------------------------------------------------//
/*! \file		pdx010remoteprocedure.cpp
*   \brief		definition for PDX010 remote procedure
*   \author		Steffen Heinlein
*   \date		20.06.2012
*/
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

#include "pdx010remoteprocedure.h"
#include "pdx010remoteprocedure_definitions.h"
#include <remoteprocedureresult.h>

#include <sstream>
#include <iomanip>

using namespace std;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
namespace pharmosTransaction
{
namespace preparation
{

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX010RemoteProcedure::getResultMessage( const basar::Int32 returncode ) const
	{
		basar::VarString retval("");

		switch( returncode )
		{
			case 101:	retval = PDX010MESSAGE101;	break;
			case 102:	retval = PDX010MESSAGE102;	break;
			case 103:	retval = PDX010MESSAGE103;	break;
			case 105:	retval = PDX010MESSAGE105;	break;
			case 190:	retval = PDX010MESSAGE190;	break;
			case 201:	retval = PDX010MESSAGE201;	break;
			case 202:	retval = PDX010MESSAGE202;	break;
			case 203:	retval = PDX010MESSAGE203;	break;
			case 204:	retval = PDX010MESSAGE204;	break;
			case 205:	retval = PDX010MESSAGE205;	break;
			case 290:	retval = PDX010MESSAGE290;	break;
			case 301:	retval = PDX010MESSAGE301;	break;
			case 302:	retval = PDX010MESSAGE302;	break;
			case 303:	retval = PDX010MESSAGE303;	break;
			case 304:	retval = PDX010MESSAGE304;	break;
			case 305:	retval = PDX010MESSAGE305;	break;
			case 390:	retval = PDX010MESSAGE390;	break;		
			default:	retval = "";				break;
		}

		return retval;
	}

	//--------------------------------------------------------------------------------------------------//
	const libcsc_utils::RemoteProcedureResult PDX010RemoteProcedure::checkResult() const
	{		
		if( 0 != m_CDX010CommArea.ReturnCode )
		{
			return libcsc_utils::RemoteProcedureResult( false, 0 ,getResultMessage( m_CDX010CommArea.ReturnCode ) );		
		}
        return libcsc_utils::RemoteProcedureResult( true, m_CDX010CommArea.DatasetsProcessed );	
	}

	//--------------------------------------------------------------------------------------------------//
	PDX010RemoteProcedure::PDX010RemoteProcedure( const basar::Int16 branchno, const basar::VarString &applicationname )
	{	
		m_CDX010CommArea.CommAreaLength = CDX010::CDX010CommArea::LENGTH_TOTAL;
		m_CDX010CommArea.BranchNo = branchno;
		m_CDX010CommArea.CallID = applicationname;
		
		m_CDX010CommArea.ReturnCode = 0;
		m_CDX010CommArea.DatasetsProcessed = 0;
		m_CDX010CommArea.OffsetStart = 0;
		m_CDX010CommArea.OffsetEnd = 0;
		m_CDX010CommArea.ClearBeforeTransfer = "J";
		m_CDX010CommArea.Filler = " ";
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX010RemoteProcedure::getProcedureName() const
	{
		return PROCEDURENAME;
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX010RemoteProcedure::serializeQuery() const
	{
		stringstream ss;

		ss	<< setw( CDX010::CDX010CommArea::LENGTH_COMMAREA )				<< setfill('0') << right << m_CDX010CommArea.CommAreaLength
			<< setw( CDX010::CDX010CommArea::LENGTH_CALLID )				<< setfill(' ') << left  << m_CDX010CommArea.CallID
			<< setw( CDX010::CDX010CommArea::LENGTH_RETURNCODE )			<< setfill('0') << right << m_CDX010CommArea.ReturnCode
			<< setw( CDX010::CDX010CommArea::LENGTH_DATASETSPROCESSED )		<< setfill('0') << right << m_CDX010CommArea.DatasetsProcessed
			<< setw( CDX010::CDX010CommArea::LENGTH_BRANCHNO )				<< setfill('0') << right << m_CDX010CommArea.BranchNo
			<< setw( CDX010::CDX010CommArea::LENGTH_OFFSETSTART )			<< setfill('0') << right << m_CDX010CommArea.OffsetStart
			<< setw( CDX010::CDX010CommArea::LENGTH_OFFSETEND )				<< setfill('0') << right << m_CDX010CommArea.OffsetEnd
			<< setw( CDX010::CDX010CommArea::LENGHT_CLEARBEFORETRANSFER )   << setfill(' ') << left  << m_CDX010CommArea.ClearBeforeTransfer
			<< setw( CDX010::CDX010CommArea::LENGTH_FILLER)					<< setfill(' ') << left	 << m_CDX010CommArea.Filler;

		if( ss.str().length() > (CDX010::CDX010CommArea::LENGTH_TOTAL + CDX010::CDX010CommArea::LENGTH_COMMAREA) )
		{
			ss.str() = ss.str().substr(0, CDX010::CDX010CommArea::LENGTH_TOTAL);
		}

		return ss.str().c_str();
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX010RemoteProcedure::serializeForLogging() const
	{
		stringstream ss;

		ss	<< " CommAreaLength: "
			<< setw( CDX010::CDX010CommArea::LENGTH_COMMAREA )				<< setfill('0') << right << m_CDX010CommArea.CommAreaLength
			<< " | CallID: "
			<< setw( CDX010::CDX010CommArea::LENGTH_CALLID )				<< setfill(' ') << left  << m_CDX010CommArea.CallID
			<< " | ReturnCode: "
			<< setw( CDX010::CDX010CommArea::LENGTH_RETURNCODE )			<< setfill('0') << right << m_CDX010CommArea.ReturnCode
			<< " | DatasetsProcessed: "
			<< setw( CDX010::CDX010CommArea::LENGTH_DATASETSPROCESSED )		<< setfill('0') << right << m_CDX010CommArea.DatasetsProcessed
			<< " | BranchNo: "
			<< setw( CDX010::CDX010CommArea::LENGTH_BRANCHNO )				<< setfill('0') << right << m_CDX010CommArea.BranchNo
			<< " | OffsetStart: "
			<< setw( CDX010::CDX010CommArea::LENGTH_OFFSETSTART )			<< setfill('0') << right << m_CDX010CommArea.OffsetStart
			<< " | OffsetEnd: "
			<< setw( CDX010::CDX010CommArea::LENGTH_OFFSETEND )				<< setfill('0') << right << m_CDX010CommArea.OffsetEnd
			<< " | ClearBeforeTransfer: "
			<< setw( CDX010::CDX010CommArea::LENGHT_CLEARBEFORETRANSFER)	<< setfill(' ') << left	 << m_CDX010CommArea.ClearBeforeTransfer
			<< " | Filler: "
			<< setw( CDX010::CDX010CommArea::LENGTH_FILLER)					<< setfill(' ') << left	 << m_CDX010CommArea.Filler;

		if( ss.str().length() > (CDX010::CDX010CommArea::LENGTH_TOTAL + CDX010::CDX010CommArea::LENGTH_COMMAREA) )
		{
			ss.str() = ss.str().substr(0, CDX010::CDX010CommArea::LENGTH_TOTAL);
		}

		return ss.str().c_str();
	}

	//--------------------------------------------------------------------------------------------------//
	void PDX010RemoteProcedure::deserializeResult( const basar::VarString &result )
	{
		basar::Int16 currentposition = 0;	
		
		m_CDX010CommArea.CommAreaLength = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_COMMAREA ).stoi();
		currentposition += CDX010::CDX010CommArea::LENGTH_COMMAREA;

		m_CDX010CommArea.CallID = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_CALLID);
		currentposition += CDX010::CDX010CommArea::LENGTH_CALLID;

		m_CDX010CommArea.ReturnCode = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_RETURNCODE).stoi();
		currentposition += CDX010::CDX010CommArea::LENGTH_RETURNCODE;

		m_CDX010CommArea.DatasetsProcessed = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_DATASETSPROCESSED).stoi();
		currentposition += CDX010::CDX010CommArea::LENGTH_DATASETSPROCESSED;

		m_CDX010CommArea.BranchNo = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_BRANCHNO).stoi();
		currentposition += CDX010::CDX010CommArea::LENGTH_BRANCHNO;

		m_CDX010CommArea.OffsetStart = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_OFFSETSTART).stoi();
		currentposition += CDX010::CDX010CommArea::LENGTH_OFFSETSTART;

		m_CDX010CommArea.OffsetEnd = result.substr(currentposition, CDX010::CDX010CommArea::LENGTH_OFFSETEND).stoi();
		currentposition += CDX010::CDX010CommArea::LENGTH_OFFSETEND;				
	}

}
}
}