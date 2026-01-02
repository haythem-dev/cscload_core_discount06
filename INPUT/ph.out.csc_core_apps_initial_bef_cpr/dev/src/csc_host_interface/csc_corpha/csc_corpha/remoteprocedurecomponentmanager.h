//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		15.10.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_REMOTEPROCEDURECOMPONENTMANAGER_H
#define GUARD_DOMMOD_CORPHA_REMOTEPROCEDURECOMPONENTMANAGER_H

#include <icsc_loggerptr.h>
#include <iremoteprocedurecallerptr.h>
#include <iapplconfigurationptr.h>

#include "iremoteprocedureservicelocator.h"

namespace domMod
{
namespace corpha
{    

class RemoteProcedureComponentManager : public domMod::corpha::IRemoteProcedureServiceLocator
{
	private:
        RemoteProcedureComponentManager( const RemoteProcedureComponentManager& );
		RemoteProcedureComponentManager& operator= ( const RemoteProcedureComponentManager& );        		

    public:		
		~RemoteProcedureComponentManager();		
		RemoteProcedureComponentManager( basar::db::aspect::ConnectionRef, libcsc_utils::IApplConfigurationPtr, libcsc_utils::ICSC_LoggerPtr );		

		libcsc_utils::IRemoteProcedureCallerPtr		getRemoteProcedureCaller( const basar::Long64 orderno, const basar::Long64 time );

    private:		        		
		libcsc_utils::ICSC_LoggerPtr				m_Logger;		
		basar::db::aspect::ConnectionRef			m_Connection;
		const basar::VarString						m_ApplicationName;
		libcsc_utils::IApplConfigurationPtr			m_ApplConfiguration;

		libcsc_utils::IRemoteProcedureCallerPtr		m_RPCaller;			

};

} // end namespace corpha
} // end namespace domMod

#endif // GUARD_DOMMOD_CORPHA_REMOTEPROCEDURECOMPONENTMANAGER_H

