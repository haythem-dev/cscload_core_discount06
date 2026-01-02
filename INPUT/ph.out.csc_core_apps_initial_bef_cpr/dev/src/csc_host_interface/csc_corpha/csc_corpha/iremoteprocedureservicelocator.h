//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		15.10.2012
 */
//----------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_IREMOTEPROCEDURESERVICELOCATOR_H
#define GUARD_DOMMOD_CORPHA_IREMOTEPROCEDURESERVICELOCATOR_H

#include <iremoteprocedurecallerptr.h>

namespace domMod
{
namespace corpha
{

class IRemoteProcedureServiceLocator
{			
    public:		
        virtual ~IRemoteProcedureServiceLocator(){};				
		virtual libcsc_utils::IRemoteProcedureCallerPtr		getRemoteProcedureCaller( const basar::Long64, const basar::Long64 ) = 0;
};


}
}

#endif // GUARD_DOMMOD_CORPHA_IREMOTEPROCEDURESERVICELOCATOR_H
