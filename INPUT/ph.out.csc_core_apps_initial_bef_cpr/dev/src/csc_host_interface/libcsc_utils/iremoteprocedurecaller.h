//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		interface for RemoteProcedureCaller
 *  \author		
 *  \date		
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_IREMOTEPROCEDURECALLER_H
#define GUARD_LIBCSC_UTILS_IREMOTEPROCEDURECALLER_H

#include "iremoteprocedureptr.h"

namespace basar
{
	namespace db
	{
		namespace aspect
		{
			//class AccessorInstanceRef;
			class AccessorPropertyTableRef;
			//class AccessorPropertyTable_YIterator;		
		}
	}
}

namespace libcsc_utils
{	
	struct RemoteProcedureResult;


	class IRemoteProcedureCaller
	{		
		public:			
				
			virtual ~IRemoteProcedureCaller(){};	

			virtual RemoteProcedureResult								call() = 0;

			virtual void												injectRemoteProcedure( IRemoteProcedurePtr remoteprocedure ) = 0;			

			virtual basar::db::aspect::AccessorPropertyTableRef			getRemoteProcedureACCPropTab() = 0;			
								
	}; // end of Interface IRemoteProcedureCaller

}

#endif  // GUARD_LIBCSC_UTILS_IREMOTEPROCEDURECALLER_H
