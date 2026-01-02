//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		class for DKOTE accessor management
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSOREVEN_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSOREVEN_H

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
	class CICSOrderAccessorEven : public CICSOrderAccessorBase
    {
		// ----------------- p u b l i c ------------------------------------------	//	
		public:
			virtual														~CICSOrderAccessorEven();

																		CICSOrderAccessorEven(const basar::db::aspect::ConnectionRef, libcsc_utils::ICSC_LoggerPtr); 

			virtual AccessorInstanceRefWrapper&							getAccessor();			

			virtual domMod::searchyiterator::SearchYIteratorPtr			getSearchYit();

			virtual void												findByPattern();

			virtual basar::Int32										getCountByPattern();

			virtual void												addOrderItemYit( const recordtypes::RecordTypeBasePtr, const basar::Int32, const basar::Int32 );

			virtual void												prepareRetrieveCriteria( const basar::Int32 orderno );

			virtual void												send();

			virtual CICSRecord											getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator );       
		
		// ----------------- p r i v a t e ---------------------------------------- //
		private:

																		CICSOrderAccessorEven(const CICSOrderAccessorEven& r);

			CICSOrderAccessorEven&										operator=(const CICSOrderAccessorEven& r);								
	}; 				
    
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSOREVEN_H
