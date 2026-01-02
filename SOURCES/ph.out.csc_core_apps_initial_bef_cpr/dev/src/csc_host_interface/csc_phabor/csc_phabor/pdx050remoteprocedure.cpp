//--------------------------------------------------------------------------------------------------//
/*! \file		pdx050remoteprocedure.cpp
*   \brief		definition for PDX050 remote procedure
*   \author		Steffen Heinlein
*   \date		11.07.2012
*/
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

#include "pdx050remoteprocedure.h"
#include "pdx050remoteprocedure_definitions.h"
#include <remoteprocedureresult.h>

#include <sstream>
#include <iomanip>

using namespace std;

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
namespace batchOrder
{
namespace preparation
{

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX050RemoteProcedure::getResultMessage( const basar::Int32 returncode ) const
	{
		basar::VarString retval("");

		switch( returncode )
		{
			case 101:	retval = PDX050MESSAGE101;	break;
			case 102:	retval = PDX050MESSAGE102;	break;
			case 103:	retval = PDX050MESSAGE103;	break;
			case 105:	retval = PDX050MESSAGE105;	break;
			case 190:	retval = PDX050MESSAGE190;	break;
			case 201:	retval = PDX050MESSAGE201;	break;
			case 202:	retval = PDX050MESSAGE202;	break;
			case 203:	retval = PDX050MESSAGE203;	break;
			case 204:	retval = PDX050MESSAGE204;	break;
			case 205:	retval = PDX050MESSAGE205;	break;
			case 290:	retval = PDX050MESSAGE290;	break;
			case 301:	retval = PDX050MESSAGE301;	break;
			case 302:	retval = PDX050MESSAGE302;	break;
			case 303:	retval = PDX050MESSAGE303;	break;
			case 304:	retval = PDX050MESSAGE304;	break;
			case 305:	retval = PDX050MESSAGE305;	break;
			case 390:	retval = PDX050MESSAGE390;	break;		
			default:	retval = "";				break;
		}

		return retval;
	}

	//--------------------------------------------------------------------------------------------------//
	const libcsc_utils::RemoteProcedureResult PDX050RemoteProcedure::checkResult() const
	{		
		if( 0 != m_CDX050CommArea.ReturnCode )
		{
			return libcsc_utils::RemoteProcedureResult( false, 0, getResultMessage( m_CDX050CommArea.ReturnCode ) );		
		}
		return libcsc_utils::RemoteProcedureResult( true, m_CDX050CommArea.DatasetsProcessed );	
	}

	//--------------------------------------------------------------------------------------------------//
	PDX050RemoteProcedure::PDX050RemoteProcedure( const basar::Int16 branchno, const basar::VarString &applicationname,
												  const basar::VarString updateStatus, const basar::Date updateDate, 
												  const basar::Int32 updateOffset )
	{	
		m_CDX050CommArea.CommAreaLength = CDX050::CDX050CommArea::LENGTH_TOTAL;
		m_CDX050CommArea.BranchNo = branchno;
		m_CDX050CommArea.CallID = applicationname;
		
		m_CDX050CommArea.ReturnCode = 0;
		m_CDX050CommArea.DatasetsProcessed = 0;
		m_CDX050CommArea.OffsetStart = 0;
		m_CDX050CommArea.OffsetEnd = 0;
		m_CDX050CommArea.UpdateStatus = updateStatus;

		if ( updateDate.isValid() ){
			m_CDX050CommArea.UpdateDate = updateDate.toString("yyyymmdd").stoi();
		} else {
			m_CDX050CommArea.UpdateDate = 0;
		}
		
		m_CDX050CommArea.UpdateOffset = updateOffset;
		m_CDX050CommArea.Filler = " ";
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX050RemoteProcedure::getProcedureName() const
	{
		return PROCEDURENAMEPDX050;
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX050RemoteProcedure::serializeQuery() const
	{
		stringstream ss;

		ss	<< setw( CDX050::CDX050CommArea::LENGTH_COMMAREA )			<< setfill('0') << right << m_CDX050CommArea.CommAreaLength
			<< setw( CDX050::CDX050CommArea::LENGTH_CALLID )			<< setfill(' ') << left  << m_CDX050CommArea.CallID
			<< setw( CDX050::CDX050CommArea::LENGTH_RETURNCODE )		<< setfill('0') << right << m_CDX050CommArea.ReturnCode
			<< setw( CDX050::CDX050CommArea::LENGTH_BRANCHNO )			<< setfill('0') << right << m_CDX050CommArea.BranchNo
			<< setw( CDX050::CDX050CommArea::LENGTH_OFFSETSTART )		<< setfill('0') << right << m_CDX050CommArea.OffsetStart
			<< setw( CDX050::CDX050CommArea::LENGTH_OFFSETEND )			<< setfill('0') << right << m_CDX050CommArea.OffsetEnd
			<< setw( CDX050::CDX050CommArea::LENGTH_DATASETSPROCESSED )	<< setfill('0') << right << m_CDX050CommArea.DatasetsProcessed						
			<< setw( CDX050::CDX050CommArea::LENGTH_UPDSTATUS )			<< setfill('0') << right << m_CDX050CommArea.UpdateStatus	
			<< setw( CDX050::CDX050CommArea::LENGTH_UPDSTATUSDATE )		<< setfill('0') << right << m_CDX050CommArea.UpdateDate	
			<< setw( CDX050::CDX050CommArea::LENGTH_UPDSTATUSOFFSET )	<< setfill('0') << right << m_CDX050CommArea.UpdateOffset	
			<< setw( CDX050::CDX050CommArea::LENGTH_FILLER)				<< setfill(' ') << left	 << m_CDX050CommArea.Filler;

		if( ss.str().length() > (CDX050::CDX050CommArea::LENGTH_TOTAL + CDX050::CDX050CommArea::LENGTH_COMMAREA) )
		{
			ss.str() = ss.str().substr(0, CDX050::CDX050CommArea::LENGTH_TOTAL);
		}

		return ss.str().c_str();
	}

	//--------------------------------------------------------------------------------------------------//
	const basar::VarString PDX050RemoteProcedure::serializeForLogging() const
	{
		stringstream ss;

		ss	<< " CommAreaLength: "
			<< setw( CDX050::CDX050CommArea::LENGTH_COMMAREA )				<< setfill('0') << right << m_CDX050CommArea.CommAreaLength
			<< " | CallID: "
			<< setw( CDX050::CDX050CommArea::LENGTH_CALLID )				<< setfill(' ') << left  << m_CDX050CommArea.CallID
			<< " | ReturnCode: "
			<< setw( CDX050::CDX050CommArea::LENGTH_RETURNCODE )			<< setfill('0') << right << m_CDX050CommArea.ReturnCode
			<< " | DatasetsProcessed: "
			<< setw( CDX050::CDX050CommArea::LENGTH_DATASETSPROCESSED )		<< setfill('0') << right << m_CDX050CommArea.DatasetsProcessed
			<< " | BranchNo: "
			<< setw( CDX050::CDX050CommArea::LENGTH_BRANCHNO )				<< setfill('0') << right << m_CDX050CommArea.BranchNo
			<< " | OffsetStart: "
			<< setw( CDX050::CDX050CommArea::LENGTH_OFFSETSTART )			<< setfill('0') << right << m_CDX050CommArea.OffsetStart
			<< " | OffsetEnd: "
			<< setw( CDX050::CDX050CommArea::LENGTH_OFFSETEND )				<< setfill('0') << right << m_CDX050CommArea.OffsetEnd
			<< " | UpdateStatus: "
			<< setw( CDX050::CDX050CommArea::LENGTH_UPDSTATUS )				<< setfill('0') << right << m_CDX050CommArea.OffsetEnd
			<< " | UpdateDate: "
			<< setw( CDX050::CDX050CommArea::LENGTH_UPDSTATUSDATE )			<< setfill('0') << right << m_CDX050CommArea.OffsetEnd
			<< " | UpdateOffset: "
			<< setw( CDX050::CDX050CommArea::LENGTH_UPDSTATUSOFFSET )		<< setfill('0') << right << m_CDX050CommArea.OffsetEnd
			<< " | Filler: "
			<< setw( CDX050::CDX050CommArea::LENGTH_FILLER)					<< setfill(' ') << left	 << m_CDX050CommArea.Filler;

		if( ss.str().length() > (CDX050::CDX050CommArea::LENGTH_TOTAL + CDX050::CDX050CommArea::LENGTH_COMMAREA) )
		{
			ss.str() = ss.str().substr(0, CDX050::CDX050CommArea::LENGTH_TOTAL);
		}

		return ss.str().c_str();
	}

	//--------------------------------------------------------------------------------------------------//
	void PDX050RemoteProcedure::deserializeResult( const basar::VarString &result )
	{
		basar::Int16 currentposition = 0;	
		
		m_CDX050CommArea.CommAreaLength = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_COMMAREA ).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_COMMAREA;

		m_CDX050CommArea.CallID = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_CALLID);
		currentposition += CDX050::CDX050CommArea::LENGTH_CALLID;

		m_CDX050CommArea.ReturnCode = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_RETURNCODE).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_RETURNCODE;

		m_CDX050CommArea.BranchNo = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_BRANCHNO).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_BRANCHNO;

		m_CDX050CommArea.OffsetStart = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_OFFSETSTART).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_OFFSETSTART;

		m_CDX050CommArea.OffsetEnd = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_OFFSETEND).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_OFFSETEND;	

		m_CDX050CommArea.DatasetsProcessed = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_DATASETSPROCESSED).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_DATASETSPROCESSED;

		m_CDX050CommArea.UpdateStatus = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_UPDSTATUS);
		currentposition += CDX050::CDX050CommArea::LENGTH_UPDSTATUS;

		m_CDX050CommArea.UpdateDate = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_UPDSTATUSDATE).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_UPDSTATUSDATE;

		m_CDX050CommArea.UpdateOffset = result.substr(currentposition, CDX050::CDX050CommArea::LENGTH_UPDSTATUSOFFSET).stoi();
		currentposition += CDX050::CDX050CommArea::LENGTH_UPDSTATUSOFFSET;
	}

}
}
}
