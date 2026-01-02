//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  PXVBDBConnection
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBDBCONNECTION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBDBCONNECTION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
//#include <libbasarcmnutil.h>
#include "ipxvbdbconnection.h"

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

class NullPXVBDBConnection : public IPXVBDBConnection
{	
    public:		
        NullPXVBDBConnection();
        ~NullPXVBDBConnection();             			

		virtual void beginTransaction( const TransactionLevel );
        virtual void commitTransaction(  const TransactionLevel );
		virtual void rollbackTransaction();	
        virtual bool isTransactionActive();
};

} // end namespace pxVerbund
} // end namespace pharmosTransaction
} // end namespace domMod

#endif 

