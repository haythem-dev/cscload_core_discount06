//----------------------------------------------------------------------------//
/*! \file	
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBDBTRANSACTIONLEVELMAPPER_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBDBTRANSACTIONLEVELMAPPER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "pxvbdbconnection_definitions.h"
#include "pvhx04_includes.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

	class PXVBDBTransactionLevelMapper 
	{	
		public:
			static ::tDBTransactLevel mapTransactionLevel2PXDBTransactLevel( const TransactionLevel ); // tDBTransactLevel defined in database.hpp    

		private:
			PXVBDBTransactionLevelMapper();
			~PXVBDBTransactionLevelMapper();

			PXVBDBTransactionLevelMapper( const PXVBDBTransactionLevelMapper& );
		    PXVBDBTransactionLevelMapper& operator= ( const PXVBDBTransactionLevelMapper& );

	};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 

