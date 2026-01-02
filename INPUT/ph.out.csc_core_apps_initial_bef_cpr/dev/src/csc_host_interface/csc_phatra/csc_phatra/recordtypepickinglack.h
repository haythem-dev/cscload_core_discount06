//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypePickingLack
 *  \author Steffen Heinlein
 *  \date   09.01.2014
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEPICKINGLACK_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEPICKINGLACK_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h> 
#include "recordtypebase.h"
#include "recordtypefactory.h"
#include "recordprocesshelperptr.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

class RecordTypePickingLack : public core::RecordTypeBase
{
	friend class core::RecordTypeFactory;
    public:	
        RecordTypePickingLack();
        ~RecordTypePickingLack();           

		void					process( const core::TransactionRecordBasePtr record ) const;			

    private:
        RecordTypePickingLack( const RecordTypePickingLack& );
		RecordTypePickingLack& operator= ( const RecordTypePickingLack& );		

		void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;		

		void					injectRecordProcessHelper( RecordProcessHelperPtr );

		RecordProcessHelperPtr	m_RecordProcessHelperPtr;		
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEPICKINGLACK_H

