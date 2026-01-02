//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       15.10.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <iremoteprocedurecaller.h>
#include <remoteprocedurecaller.h>
#include <iapplconfiguration.h>

#include "remoteprocedurecomponentmanager.h"
#include "pdx040remoteprocedure.h"
#include "csc_corphacmdlineoption_definitions.h"

namespace domMod
{
namespace corpha
{

	//--------------------------------------------------------------------------------------------------//
	RemoteProcedureComponentManager::RemoteProcedureComponentManager( basar::db::aspect::ConnectionRef tca, libcsc_utils::IApplConfigurationPtr applcfg, libcsc_utils::ICSC_LoggerPtr logger )
	: m_Logger( logger ), m_Connection( tca ), m_ApplicationName( applcfg->getApplicationName() ), m_ApplConfiguration( applcfg )
	{
        METHODNAME_DEF( RemoteProcedureComponentManager, RemoteProcedureComponentManager )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		

		m_RPCaller = libcsc_utils::IRemoteProcedureCallerPtr( new libcsc_utils::RemoteProcedureCaller( m_Connection, m_Logger ) );
	}
	//--------------------------------------------------------------------------------------------------//

	//--------------------------------------------------------------------------------------------------//
	RemoteProcedureComponentManager::~RemoteProcedureComponentManager()		
	{
        METHODNAME_DEF( RemoteProcedureComponentManager, ~RemoteProcedureComponentManager )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//--------------------------------------------------------------------------------------------------//

	//--------------------------------------------------------------------------------------------------//
	libcsc_utils::IRemoteProcedureCallerPtr RemoteProcedureComponentManager::getRemoteProcedureCaller( const basar::Long64 orderno, const basar::Long64 time )
	{
        METHODNAME_DEF( RemoteProcedureComponentManager, getRemoteProcedureCaller )
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		libcsc_utils::IRemoteProcedurePtr pdx040 = 
				libcsc_utils::IRemoteProcedurePtr( new domMod::corpha::PDX040RemoteProcedure( m_ApplicationName, orderno, m_ApplConfiguration->getBranchNo(), time, m_Logger ) );		
		m_RPCaller->injectRemoteProcedure( pdx040 );
		return m_RPCaller;
	}
	//--------------------------------------------------------------------------------------------------//

} // end namespace corpha
} // end namespace domMod
