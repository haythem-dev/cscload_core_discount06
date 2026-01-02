//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		11.10.2012
 */
//----------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_ICICSORDERDM_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_ICICSORDERDM_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecollectionptr.h"
#include "cicsrecord.h"

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

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//

namespace domMod 
{		
namespace corpha
{    
namespace processOrder
{

class ICICSOrderDM
{			
    public:		
        virtual ~ICICSOrderDM(){};

		virtual void init( const basar::Long64 ) = 0;
		virtual void send( recordtypes::RecordTypeCollectionPtr ) = 0;
		virtual void retrieve() = 0;
		virtual void shutdown() = 0;
		virtual basar::db::aspect::AccessorPropertyTableRef getPropTab() = 0;						
		virtual basar::db::aspect::AccessorPropertyTableRef getResponsePropTab() = 0;						
		virtual CICSRecord getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
};

}
}
}

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_ICICSORDERDM_H
