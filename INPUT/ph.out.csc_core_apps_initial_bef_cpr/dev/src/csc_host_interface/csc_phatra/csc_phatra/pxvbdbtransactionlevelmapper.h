//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  IPXVBDBConnection
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBDBTRANSACTIONLEVELMAPPER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBDBTRANSACTIONLEVELMAPPER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "pxvbdbconnection_definitions.h"
#include "pvhx01_includes.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
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
} // end namespace pharmosTransaction
} // end namespace domMod

#endif 

