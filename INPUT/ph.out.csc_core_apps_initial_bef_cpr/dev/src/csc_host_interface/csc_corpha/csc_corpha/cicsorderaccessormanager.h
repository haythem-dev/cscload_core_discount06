//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		manager for DKOTO/DKOTE accessors
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORMANAGER_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORMANAGER_H

#include "accessorinstancerefwrapper.h"
#include <icsc_loggerptr.h>
#include <iapplconfigurationptr.h>
#include <searchyiteratorptr.h>
#include "recordtypebaseptr.h"
#include "recordtypecollectionptr.h"
#include "cicsrecord.h"
#include "cicsorderaccessorbaseptr.h"
#include "cicsorderaccessorevenptr.h"
#include "cicsorderaccessoroddptr.h"
#include "cicsorderaccessorresponseptr.h"
#include "cicsorderaccessorbase.h"
#include "cicsorderaccessoreven.h"
#include "cicsorderaccessorodd.h"
#include "cicsorderaccessorresponse.h"

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;                    
			class AccessorPropertyTableRef;
            class ConnectionRef;
        }
    }
}

namespace domMod 
{		
namespace corpha
{    
namespace processOrder
{
	class CICSOrderAccessorManager
    {
        public:
																				CICSOrderAccessorManager( const basar::db::aspect::ConnectionRef,
																					libcsc_utils::ICSC_LoggerPtr,
																					libcsc_utils::IApplConfigurationPtr ); 

		    virtual																~CICSOrderAccessorManager(); 

			CICSOrderAccessorBasePtr											getAccessor( const basar::Long64 orderno, bool DirectionSend = true );			
        
	    private:	            
																				CICSOrderAccessorManager( const CICSOrderAccessorManager& r );

		    CICSOrderAccessorManager&											operator=( const CICSOrderAccessorManager& r );			

			bool																isEven( const basar::Long64 orderno );

			CICSOrderAccessorBasePtr											getAccessorEven();

			CICSOrderAccessorBasePtr											getAccessorOdd();

			CICSOrderAccessorBasePtr											getAccessorResponse();

			libcsc_utils::ICSC_LoggerPtr										m_Logger;		

			const basar::db::aspect::ConnectionRef								m_TCAConn;

			libcsc_utils::IApplConfigurationPtr									m_ApplConfiguration;

			CICSOrderAccessorBasePtr											m_AccessorEven;

			CICSOrderAccessorBasePtr											m_AccessorOdd;	

			CICSOrderAccessorBasePtr											m_AccessorResponse;
    }; 
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORMANAGER_H
