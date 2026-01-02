//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  PXVBDBConnection
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBDBCONNECTION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBDBCONNECTION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include "ipxvbdbconnection.h"
#include "pxordertransmitptr.h"
#include "pvhx01_includes.h"
#include <icsc_loggerptr.h>
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

class PXVBDBConnection : public IPXVBDBConnection
{	
    public:		
        PXVBDBConnection( pxOrderTransmitPtr, libcsc_utils::ICSC_LoggerPtr m_CSC_Logger );
        ~PXVBDBConnection();             			

		virtual void								beginTransaction( const TransactionLevel );
        virtual void								commitTransaction(  const TransactionLevel );
		virtual void								rollbackTransaction();	

        virtual bool                                isTransactionActive();

    private:                		
		::pxOrderTransmitPtr						m_pxOrderTransmit;
		libcsc_utils::ICSC_LoggerPtr				m_CSC_Logger;
};

} // end namespace pxVerbund
} // end namespace pharmosTransaction
} // end namespace domMod

#endif 

