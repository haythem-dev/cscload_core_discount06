//-------------------------------------------------------------------------------------------//
/*! \file		pdx050remoteprocedure.h
*   \brief		definition for PDX050 remote procedure
*   \author		Steffen Heinlein
*   \date		11.07.2012
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX050REMOTEPROCEDURE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX050REMOTEPROCEDURE_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include <iremoteprocedure.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
	namespace batchOrder
	{
		namespace preparation
		{
			namespace CDX050
			{
				//-------------------------------------------------------------------------------------------------//
				// struct declaration
				//-------------------------------------------------------------------------------------------------//
				struct CDX050CommArea
				{	
					static const int LENGTH_TOTAL = 100;

					/*static const int LENGTH_COMMAREA = 4;
					static const int LENGTH_CALLID = 10;
					static const int LENGTH_RETURNCODE = 4;
					static const int LENGTH_BRANCHNO = 2;
					static const int LENGTH_OFFSETSTART = 8;
					static const int LENGTH_OFFSETEND = 8;	
					static const int LENGTH_DATASETSPROCESSED = 8;						
					static const int LENGTH_FILLER = 56;*/

					static const int LENGTH_COMMAREA = 4;
					static const int LENGTH_CALLID = 10;
					static const int LENGTH_RETURNCODE = 4;
					static const int LENGTH_BRANCHNO = 2;
					static const int LENGTH_OFFSETSTART = 8;
					static const int LENGTH_OFFSETEND = 8;	
					static const int LENGTH_DATASETSPROCESSED = 8;						
					static const int LENGTH_UPDSTATUS = 1;
					static const int LENGTH_UPDSTATUSDATE = 8;
					static const int LENGTH_UPDSTATUSOFFSET = 8;
					static const int LENGTH_FILLER = 43;

					basar::Int32 CommAreaLength;
					basar::VarString CallID;
					basar::Int32 ReturnCode;
					basar::Int32 BranchNo;
					basar::Int32 OffsetStart;
					basar::Int32 OffsetEnd;		
					basar::Int32 DatasetsProcessed;						
					basar::VarString UpdateStatus;	
					basar::Int32 UpdateDate;	
					basar::Int32 UpdateOffset;	
					basar::VarString Filler;
				};
			}

			//-------------------------------------------------------------------------------------------------//
			// class declaration
			//-------------------------------------------------------------------------------------------------//
			class PDX050RemoteProcedure : public libcsc_utils::IRemoteProcedure
			{
				public:		
					PDX050RemoteProcedure(	const basar::Int16 branchno, const basar::VarString &applicationname, 
											const basar::VarString updateStatus, const basar::Date updateDate, 
											const basar::Int32 updateOffset );

					~PDX050RemoteProcedure(){};   

					virtual const basar::VarString						getProcedureName() const;

					virtual const basar::VarString						serializeQuery() const;

					virtual const basar::VarString						serializeForLogging() const;

					virtual void										deserializeResult( const basar::VarString &result );

					virtual const libcsc_utils::RemoteProcedureResult	checkResult() const;		

				private:
					
					const basar::VarString								getResultMessage( const basar::Int32 returncode ) const;

					CDX050::CDX050CommArea								m_CDX050CommArea;		

					PDX050RemoteProcedure(const PDX050RemoteProcedure&);
					PDX050RemoteProcedure& operator=(const PDX050RemoteProcedure&);	
			};

		}//end preparation
	}//end batchOrder
} // end domMod

#endif // GUARD_UTIL_CDX010_PDX050REMOTEPROCEDURE_H


