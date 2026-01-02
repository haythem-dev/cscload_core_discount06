//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		class for DKOTO accessor management
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORODD_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORODD_H

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
	class CICSOrderAccessorOdd : public CICSOrderAccessorBase
    {
		// ----------------- p u b l i c ------------------------------------------	//	
		public:
			virtual														~CICSOrderAccessorOdd();

																		CICSOrderAccessorOdd(const basar::db::aspect::ConnectionRef, libcsc_utils::ICSC_LoggerPtr); 

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

																		CICSOrderAccessorOdd(const CICSOrderAccessorOdd& r);

			CICSOrderAccessorOdd&										operator=(const CICSOrderAccessorOdd& r);								
	}; 				            
    
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORODD_H
