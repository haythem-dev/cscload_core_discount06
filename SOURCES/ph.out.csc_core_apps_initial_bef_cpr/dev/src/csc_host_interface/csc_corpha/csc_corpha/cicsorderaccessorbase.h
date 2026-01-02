//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		base class for DKOTO/DKOTE accessor management
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORBASE_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORBASE_H

#include "accessorinstancerefwrapper.h"
#include <icsc_loggerptr.h>
#include <searchyiteratorptr.h>
#include <ibulkinserterptr.h>
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
	class CICSOrderAccessorBase
    {
        public:
																				CICSOrderAccessorBase( libcsc_utils::ICSC_LoggerPtr
																										, basar::VarString
																										, const basar::db::aspect::ConnectionRef ); 

		    virtual																~CICSOrderAccessorBase(); 

			virtual AccessorInstanceRefWrapper&									getAccessor() = 0;

			basar::db::aspect::AccessorPropertyTableRef							getPropTab();

			basar::db::aspect::AccessorPropertyTable_YIterator					addEmptyYit();

			virtual domMod::searchyiterator::SearchYIteratorPtr					getSearchYit() = 0;

			virtual void														findByPattern() = 0;

			virtual basar::Int32												getCountByPattern() = 0;

			virtual void														addOrderItemYit( const recordtypes::RecordTypeBasePtr, const basar::Int32, const basar::Int32 );

			virtual void														prepareRetrieveCriteria( const basar::Int32 orderno ) = 0;

			virtual void														send();

			virtual CICSRecord													getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator );

			void																setBulkInsert(bool bulkinsert) { m_BulkInsert = bulkinsert; }

        protected:		    

			void																doSend( const basar::VarString& AccMethodName );

			void																doSetTransferCompleted( const basar::VarString& AccMethodName );

			void																doFindByPattern( const basar::VarString& AccMethodName );

			basar::Int32														doGetCountByPattern( const basar::VarString& AccMethodName );

			void																shutdown();			

			libcsc_utils::ICSC_LoggerPtr										m_Logger;		

			domMod::searchyiterator::SearchYIteratorPtr							m_SearchYit;

			libcsc_utils::ICSC_LoggerPtr										getLogger() const;			

			AccessorInstanceRefWrapper											m_Accessor;			

			bool																m_BulkInsert;

			domMod::util::IBulkInserterPtr										m_BulkInserter;

	    private:	            
																				CICSOrderAccessorBase( const CICSOrderAccessorBase& r );

		    CICSOrderAccessorBase&												operator=( const CICSOrderAccessorBase& r );
    }; 
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORBASE_H

