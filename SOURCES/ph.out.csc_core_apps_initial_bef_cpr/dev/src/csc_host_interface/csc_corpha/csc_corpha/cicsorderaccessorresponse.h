//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		class for DKOTR accessor management
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORRESPONSE_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORRESPONSE_H

#include <icsc_loggerptr.h>
#include <searchyiteratorptr.h>
#include "cicsorderaccessorbase.h"
#include "recordtypebaseptr.h"
#include "recordtypecollectionptr.h"
#include "cicsrecord.h"

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
	class CICSOrderAccessorResponse : public CICSOrderAccessorBase
    {
		// ----------------- p u b l i c ------------------------------------------	//	
		public:
			virtual														~CICSOrderAccessorResponse();

																		CICSOrderAccessorResponse(const basar::db::aspect::ConnectionRef, libcsc_utils::ICSC_LoggerPtr); 

			virtual AccessorInstanceRefWrapper&							getAccessor();			

			virtual domMod::searchyiterator::SearchYIteratorPtr			getSearchYit();

			virtual void												findByPattern();			

			virtual basar::Int32										getCountByPattern();

			virtual void												prepareRetrieveCriteria( const basar::Int32 orderno );			

			virtual CICSRecord											getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator );       
		
		// ----------------- p r i v a t e ---------------------------------------- //
		private:

																		CICSOrderAccessorResponse(const CICSOrderAccessorResponse& r);

			CICSOrderAccessorResponse&									operator=(const CICSOrderAccessorResponse& r);								
	}; 				
    
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORRESPONSE_H
