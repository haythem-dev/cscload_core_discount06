//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       18.09.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "pxvbdbtransactionlevelmapper.h"
#include <notimplementedexception.h>
//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	
	
	::tDBTransactLevel PXVBDBTransactionLevelMapper::mapTransactionLevel2PXDBTransactLevel( const TransactionLevel tlevel ) // tDBTransactLevel defined in database.hpp
	{        
		if( SINGLE_RECORD == tlevel )
		{			
			return cDBTransRecord;
		}
		else if ( MULTI_RECORD == tlevel )
		{
			return cDBTransSet;
		}
		else
		{
			basar::VarString msg = "";
			msg.format("Unknown TransactionLevel %d", tlevel);
			throw new libcsc_utils::NotImplementedException( basar::ExceptInfo( msg, "mapTransactionLevel2PXDBTransactLevel", __FILE__, __LINE__ ) );
		}					
		return cDBTransRecord;
	}

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod
