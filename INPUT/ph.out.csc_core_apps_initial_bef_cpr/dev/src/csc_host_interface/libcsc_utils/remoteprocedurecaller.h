//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		manages stored procedure calls via tcaccess
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_REMOTEPROCEDURECALLER_H
#define GUARD_LIBCSC_UTILS_REMOTEPROCEDURECALLER_H


#include "iremoteprocedurecaller.h"
#include "iremoteprocedureptr.h"
#include "icsc_loggerptr.h"
#include <accessorinstancerefwrapper.h>
#include "remoteprocedureacc_definitions.h"


namespace basar
{
	namespace db
	{
		namespace aspect
		{
			class AccessorInstanceRef;
			class AccessorPropertyTableRef;
			class AccessorPropertyTable_YIterator;		
		}
	}
}

namespace libcsc_utils
{	
	struct RemoteProcedureResult;


	class RemoteProcedureCaller : public IRemoteProcedureCaller
	{		
		public:			

			RemoteProcedureCaller(	const basar::db::aspect::ConnectionRef tcaconn, ICSC_LoggerPtr csc_logger, const basar::VarString& stp = lit::acc_remoteprocedure::DEFAULT_STORED_PROCEDURE );		
			virtual	~RemoteProcedureCaller();
						
			RemoteProcedureResult								call();

			void												injectRemoteProcedure( IRemoteProcedurePtr remoteprocedure );			

			basar::db::aspect::AccessorPropertyTableRef			getRemoteProcedureACCPropTab();			
								
		private:

			RemoteProcedureCaller(const RemoteProcedureCaller& r);
			RemoteProcedureCaller& operator=(const RemoteProcedureCaller& r);		

			void												init();					

			void												shutdown();

			void												checkInjections() const;

			basar::db::aspect::AccessorInstanceRef				getRemoteProcedureACC();			

			basar::db::aspect::AccessorPropertyTable_YIterator	addEmptyRemoteProcedureYit();			

			basar::db::aspect::ConnectionRef					m_TCAConnection; //!< tcaccess connection

			ICSC_LoggerPtr										m_CSC_Logger;	//!< logger 

			IRemoteProcedurePtr									m_RemoteProcedure; //!< remote procedure to be called

			const basar::VarString								m_StoredProcedure; //!< name of the stored procedure 
			
			domMod::AccessorInstanceRefWrapper                  m_Accessor;

	}; // end of class RemoteProcedureCaller

}

#endif  // GUARD_LIBCSC_UTILS_REMOTEPROCEDURECALLER_H
