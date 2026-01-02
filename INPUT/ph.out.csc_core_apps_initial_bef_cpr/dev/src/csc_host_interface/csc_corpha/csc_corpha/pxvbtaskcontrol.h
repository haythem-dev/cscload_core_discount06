//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       18.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBTASKCONTROL_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBTASKCONTROL_H

#include <icsc_loggerptr.h>
#include <iapplconfigurationptr.h>

#include "pvhx04_includes.h"
#include "ipxvbtaskcontrol.h"
#include "ipxvbservicelocatorptr.h"
#include "pxtaskcontrolptr.h"

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	
	class PXVBTaskControl : public domMod::corpha::pxVerbund::IPXVBTaskControl
	{	
		public:
			PXVBTaskControl( domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr, libcsc_utils::IApplConfigurationPtr, libcsc_utils::ICSC_LoggerPtr );
			~PXVBTaskControl();								

		private:
			PXVBTaskControl( const PXVBTaskControl& );
			PXVBTaskControl& operator= ( const PXVBTaskControl& );

		public:
			void												setHeartBeat();			

		private:
			pxTaskControlPtr									getPXTaskControl();
	
		private:
			libcsc_utils::IApplConfigurationPtr					m_ApplConfiguration;
			domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr	m_PXVBServiceLocator;	
			libcsc_utils::ICSC_LoggerPtr						m_Logger;
			basar::VarString									m_ApplicationName;

			pxTaskControlPtr									m_pxTaskControl;
	};

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBTASKCONTROL_H
