//-------------------------------------------------------------------------------------------//
/*! \file		pdx040remoteprocedure.h
*   \brief		definition for PDX040 remote procedure
*   \author		Steffen Heinlein
*   \date		22.08.2012
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PDX040REMOTEPROCEDURE_H
#define GUARD_DOMMOD_CORPHA_PDX040REMOTEPROCEDURE_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include <icsc_loggerptr.h>

#include "iremoteprocedure.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
	namespace corpha
	{		
		namespace CDX040
		{
			//-------------------------------------------------------------------------------------------------//
			// struct declaration
			//-------------------------------------------------------------------------------------------------//
			struct CDX040CommArea
			{	
				static const size_t LENGTH_TOTAL = 100;

				static const size_t LENGTH_COMMAREA = 4;
				static const size_t LENGTH_CALLID = 10;
				static const size_t LENGTH_RETURNCODE = 4;
				static const size_t LENGTH_CUSTOMERORDERNO = 8;
				static const size_t LENGTH_PHARMOSORDERNO = 8;
				static const size_t LENGTH_PROCFIL = 2;
				static const size_t LENGTH_TIME = 9;
				static const size_t LENGTH_VERSIONID = 5;
				static const size_t LENGTH_FILLER = 53;

				basar::Long64 CommAreaLength;
				basar::VarString CallID;
				basar::Int32 ReturnCode;
				basar::Long64 CustomerOrderNo;
				basar::Int32 PharmosOrderNo;		
				basar::Int16 ProcedureBranchNo;
				basar::Long64 Time;
				basar::Int32 VersionID;
				basar::VarString Filler;
			};
		}
			
		class PDX040RemoteProcedure : public ::libcsc_utils::IRemoteProcedure
		{
			public:		
				PDX040RemoteProcedure( const basar::VarString &applicationname, const basar::Long64 cscorderno, const basar::Int16 branchno, const basar::Long64 time, libcsc_utils::ICSC_LoggerPtr );
				~PDX040RemoteProcedure(){};   

				virtual const basar::VarString							getProcedureName() const;

				virtual const basar::VarString							serializeQuery() const;

				virtual const basar::VarString							serializeForLogging() const;

				virtual void											deserializeResult( const basar::VarString &result );

				virtual const ::libcsc_utils::RemoteProcedureResult		checkResult() const;		

			private:
					
				const basar::VarString									getResultMessage( const basar::Int32 returncode ) const;

				CDX040::CDX040CommArea									m_CDX040CommArea;

				const basar::Int16										m_BranchNo;

				libcsc_utils::ICSC_LoggerPtr							m_Logger;		

				PDX040RemoteProcedure(const PDX040RemoteProcedure&);
				PDX040RemoteProcedure& operator=(const PDX040RemoteProcedure&);	
		};

	}//end corpha
} // end domMod

#endif // GUARD_DOMMOD_CORPHA_PDX040REMOTEPROCEDURE_H
