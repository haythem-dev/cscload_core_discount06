//----------------------------------------------------------------------------//
/*! \file	
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBDBCONNECTION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBDBCONNECTION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "pxvbdbconnection_definitions.h"

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

class IPXVBDBConnection 
{		
    public:		
        virtual ~IPXVBDBConnection(){};

		virtual void beginTransaction( const TransactionLevel ) = 0;
		virtual void commitTransaction(  const TransactionLevel ) = 0;
		virtual void rollbackTransaction() = 0;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 

