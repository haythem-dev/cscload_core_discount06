//-------------------------------------------------------------------------------------------//
/*! \file		pdx010remoteprocedure.h
*   \brief		definition for PDX010 remote procedure
*   \author		Steffen Heinlein
*   \date		20.06.2012
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX010REMOTEPROCEDURE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX010REMOTEPROCEDURE_H

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
	namespace pharmosTransaction
	{
		namespace preparation
		{
			namespace CDX010
			{
				//-------------------------------------------------------------------------------------------------//
				// struct declaration
				//-------------------------------------------------------------------------------------------------//
				struct CDX010CommArea
				{	
					static const int LENGTH_TOTAL = 100;

					static const int LENGTH_COMMAREA = 4;
					static const int LENGTH_CALLID = 10;
					static const int LENGTH_RETURNCODE = 4;
					static const int LENGTH_DATASETSPROCESSED = 8;
					static const int LENGTH_BRANCHNO = 2;
					static const int LENGTH_OFFSETSTART = 8;
					static const int LENGTH_OFFSETEND = 8;	
					static const int LENGHT_CLEARBEFORETRANSFER = 1;
					static const int LENGTH_FILLER = 55;

					basar::Int32 CommAreaLength;
					basar::VarString CallID;
					basar::Int32 ReturnCode;
					basar::Int32 DatasetsProcessed;
					basar::Int32 BranchNo;
					basar::Int32 OffsetStart;
					basar::Int32 OffsetEnd;		
					basar::VarString ClearBeforeTransfer;
					basar::VarString Filler;
				};
			}

			//-------------------------------------------------------------------------------------------------//
			// class declaration
			//-------------------------------------------------------------------------------------------------//
			class PDX010RemoteProcedure : public libcsc_utils::IRemoteProcedure
			{
				public:		
					PDX010RemoteProcedure( const basar::Int16 branchno, const basar::VarString &applicationname );
					~PDX010RemoteProcedure(){};   

					virtual const basar::VarString							getProcedureName() const;

					virtual const basar::VarString							serializeQuery() const;

					virtual const basar::VarString							serializeForLogging() const;

					virtual void											deserializeResult( const basar::VarString &result );

					virtual const libcsc_utils::RemoteProcedureResult				checkResult() const;		

				private:
					
					const basar::VarString							getResultMessage( const basar::Int32 returncode ) const;

					CDX010::CDX010CommArea							m_CDX010CommArea;		

					PDX010RemoteProcedure(const PDX010RemoteProcedure&);
					PDX010RemoteProcedure& operator=(const PDX010RemoteProcedure&);	
			};

		}//end preparation
	}//end pharmosTransaction
} // end domMod

#endif


