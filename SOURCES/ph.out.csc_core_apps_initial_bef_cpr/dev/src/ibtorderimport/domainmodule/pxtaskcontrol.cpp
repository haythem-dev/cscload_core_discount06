//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "pxtaskcontrol.h"

#include <libutil/util.h>
#include <persistence/transactionguard.h>
#include <persistence/itransactionfactory.h>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace ibtorderimport {
namespace domMod {

	//----------------------------------------------------------------------------//
	PxTaskControl::PxTaskControl( const log4cplus::Logger& logger )		
		: m_Logger( logger )
	{
	}

	//----------------------------------------------------------------------------//
	PxTaskControl::~PxTaskControl()
	{
	}

	//----------------------------------------------------------------------------//
	void	PxTaskControl::injectPxVbPxTaskControl(pxVbPxTaskControlPtr tc)
	{
		METHODNAME_DEF( MainUC, injectUnbookedIbtRequestRepo )
		BLOG_TRACE_METHOD( getLogger(), fun );

		m_pxVbPxTaskControl = tc;
	}

	//----------------------------------------------------------------------------//
	const log4cplus::Logger&	PxTaskControl::getLogger()
	{
		return m_Logger;
	}

	//----------------------------------------------------------------------------//
	void PxTaskControl::injectTransactionFactory(libcsc::persistence::ITransactionFactoryPtr transactionFactory)
	{
		METHODNAME_DEF( PxTaskControl, injectTransactionFactory )
		BLOG_TRACE_METHOD( getLogger(), fun );

		m_TransactionFactory = transactionFactory;
	}

	//----------------------------------------------------------------------------//
	pxVbPxTaskControlPtr	PxTaskControl::getPxVbPxTaskControl()
	{
		CHECK_INSTANCE_EXCEPTION( m_pxVbPxTaskControl.get() );

		return m_pxVbPxTaskControl;
	}
	
	//----------------------------------------------------------------------------//
	void PxTaskControl::setHeartBeat()
	{
		METHODNAME_DEF( PxTaskControl, setHeartBeat );
		BLOG_TRACE_METHOD( getLogger(), fun );

		try
		{
			libcsc::persistence::TransactionGuard guard = getTransactionFactory()->createTransaction();
			guard.begin();

			nTime now;
			getPxVbPxTaskControl()->TaskControl( now );

			if( !getPxVbPxTaskControl()->IsGoodState() )
			{								
				BLOG_WARN(getLogger(), "-> setHeartBeat failed: TaskControl is not in good state" );							
				guard.rollback();
			}
			else
			{
				guard.commit();
				BLOG_DEBUG( getLogger(), "-> heart beat was set successfully." );
			}			
		}
		catch( ... )
		{				
			BLOG_ERROR( getLogger(), "-> setHeartBeat unexpected exception" );	
			throw;
		}

	}

	//----------------------------------------------------------------------------//
	libcsc::persistence::ITransactionFactoryPtr		PxTaskControl::getTransactionFactory()
	{
		CHECK_INSTANCE_EXCEPTION( m_TransactionFactory.get() );
		return m_TransactionFactory;
	}
	
} // namespace domMod
} // namespace ibtorderimport
