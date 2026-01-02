//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

#include "pxvbdbconnection.h"
#include "pvhx01_includes.h"
#include "pxvbdbtransactionlevelmapper.h"
#include <icsc_logger.h>
#include <notimplementedexception.h>
#include <classinfo_macros.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace pxVerbund
{	
	PXVBDBConnection::PXVBDBConnection( pxOrderTransmitPtr xmit, libcsc_utils::ICSC_LoggerPtr	csc_logger )
		: m_pxOrderTransmit( xmit ), m_CSC_Logger( csc_logger )
	{
        METHODNAME_DEF( PXVBDBConnection, PXVBDBConnection )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	}

//--------------------------------------------------------------------------------------------------//
	PXVBDBConnection::~PXVBDBConnection()
	{
        METHODNAME_DEF( PXVBDBConnection, ~PXVBDBConnection )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	}
//--------------------------------------------------------------------------------------------------//
	void PXVBDBConnection::beginTransaction( const TransactionLevel tlevel )
	{
        METHODNAME_DEF( PXVBDBConnection, beginTransaction )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
		
		try
		{
			m_pxOrderTransmit->nDBBeginTransaction( PXVBDBTransactionLevelMapper::mapTransactionLevel2PXDBTransactLevel( tlevel ) );									
		}
		catch(libcsc_utils::NotImplementedException& ex)
		{
			m_CSC_Logger->logBasarException("text caught NotImplExecp", ex);
		}
	}

//--------------------------------------------------------------------------------------------------//
	void PXVBDBConnection::commitTransaction( const TransactionLevel tlevel )
	{
        METHODNAME_DEF( PXVBDBConnection, commitTransaction )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
		
		try
		{
			m_pxOrderTransmit->nDBCommit( PXVBDBTransactionLevelMapper::mapTransactionLevel2PXDBTransactLevel( tlevel ) );
		}
		catch(libcsc_utils::NotImplementedException& ex)
		{
			m_CSC_Logger->logBasarException("text caught NotImplExecp", ex);
		}
	}

//--------------------------------------------------------------------------------------------------//
    bool PXVBDBConnection::isTransactionActive()
    {
        METHODNAME_DEF( PXVBDBConnection, isTransactionActive )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

        return m_pxOrderTransmit->nDBTransactLevel() > 0;

    }
//--------------------------------------------------------------------------------------------------//
	void PXVBDBConnection::rollbackTransaction()
	{
        METHODNAME_DEF( PXVBDBConnection, rollbackTransaction )
        BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

		m_pxOrderTransmit->nDBRollBack();
	}

} // end namespace pxVerbund
} // end namespace pharmosTransaction
} // end namespace domMod
